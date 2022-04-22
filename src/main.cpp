#include "Output.h"
#include "RTClib.h"
#include "Time_range.h"

#include <Arduino.h>

bool chceck_day(const uint8_t days, const DateTime& now)
{
  return (days & (1 << now.dayOfTheWeek()));
}

bool compare_time(const uint8_t h, const uint8_t m, const DateTime& now)
{
  return ((h == now.hour()) && (m == now.minute()));
}

Action is_action(const Time_range* times, const uint8_t times_count, const DateTime& now, const Action state)
{
  if (state != Action::start)
  {
    for (uint8_t i = 0; i < times_count; i++)
    {
      if (compare_time(times[i].hour_start, times[i].minute_start, now))
      {
        return Action::start;
      }
    }
  }

  if (state != Action::stop)
  {
    for (uint8_t i = 0; i < times_count; i++)
    {
      if (compare_time(times[i].hour_stop, times[i].minute_stop, now))
      {
        return Action::stop;
      }
    }
  }

  return Action::none;
}

void check_action(Output& output, const DateTime& now)
{
  if (chceck_day(output.days, now))
  {
    auto action = is_action(output.times, output.times_count, now, output.state);
    switch (action)
    {
      case Action::start:
        digitalWrite(output.pin, HIGH);
        Serial.print("start");
        Serial.println(output.pin);
        output.state = Action::start;
        break;
      case Action::stop:
        digitalWrite(output.pin, LOW);
        Serial.print("stop");
        Serial.println(output.pin);
        output.state = Action::stop;
        break;
      default:
        break;
    }
  }
}

RTC_DS1307 m_rtc;

const uint32_t m_refresh_time_ms = 60000;

// CONFIGURATION

const uint8_t m_button_pin_light = 7;
const uint8_t m_button_pin_pump = 8;

const uint8_t m_light_pin = 9;
const uint8_t m_light_range_count = 2;
Time_range m_light[m_light_range_count]{Time_range(13, 26, 16, 40), Time_range(20, 10, 23, 40)};

const uint8_t m_pump_pin = 10;
const uint8_t m_pump_range_count = 1;
Time_range m_pump[m_pump_range_count]{Time_range(13, 27, 16, 10)};

const uint8_t m_relay_pin = 11;
const uint8_t m_relay_range_count = 1;
Time_range m_relay[m_relay_range_count]{Time_range(13, 28, 16, 10)};

// from 0 (Sunday) to 6 (Saturday)
bool week[7]{true, true, true, true, true, true, true};

// from 0 (Sunday) to 6 (Saturday)
bool week_holiday[7]{false, true, true, true, true, true, true};

const uint8_t m_opoutputs_count = 3;
Output m_outputs[m_opoutputs_count]{{m_light_pin, week, m_light, m_light_range_count},
                                    {m_pump_pin, week, m_pump, m_pump_range_count},
                                    {m_relay_pin, week, m_relay, m_relay_range_count}};

//

void setup()
{
  Wire.begin();
  Serial.begin(9600);

  if (!m_rtc.begin())
  {
    Serial.println("Couldn't find RTC");
  }

  m_rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  for (uint8_t i = 0; i < m_opoutputs_count; i++)
  {
    pinMode(m_outputs[i].pin, OUTPUT);
  }

  DateTime now = m_rtc.now();
  for (uint8_t i = 0; i < m_opoutputs_count; i++)
  {
    check_action(m_outputs[i], now);
  }

  pinMode(m_button_pin_light, INPUT_PULLUP);
  pinMode(m_button_pin_pump, INPUT_PULLUP);
}

void loop()
{
  static unsigned long last_loop_time;
  unsigned long loop_time = millis();
  if (loop_time - last_loop_time > m_refresh_time_ms)
  {
    DateTime now = m_rtc.now();
    Serial.print(now.hour(), DEC);
    Serial.print(":");
    Serial.print(now.minute(), DEC);
    Serial.print(":");
    Serial.println(now.second(), DEC);
    last_loop_time = millis();

    for (uint8_t i = 0; i < m_opoutputs_count; i++)
    {
      check_action(m_outputs[i], now);
    }
  }

  if (digitalRead(m_button_pin_light) == LOW)
  {
    digitalWrite(m_light_pin, LOW);
    Serial.println("button pin light press");
    delay(100);
  }

  if (digitalRead(m_button_pin_pump) == LOW)
  {
    digitalWrite(m_pump_pin, LOW);
    delay(100);
  }
}
