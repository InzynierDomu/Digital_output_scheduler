#include "RTClib.h"

#include <Arduino.h>

enum class Action
{
  start,
  stop,
  none
};

struct Time_range
{
  Time_range(uint8_t _hour_start, uint8_t _minute_start, uint8_t _hour_stop, uint8_t _minute_stop)
  : hour_start(_hour_start)
  , minute_start(_minute_start)
  , hour_stop(_hour_stop)
  , minute_stop(_minute_stop)
  {}

  uint8_t hour_start;
  uint8_t minute_start;
  uint8_t hour_stop;
  uint8_t minute_stop;
};

uint8_t convert_days(bool days[7])
{
  uint8_t retval = 0;
  for (int i = 0; i < 7; i++)
  {
    if (days[i])
    {
      retval |= 1 << i;
    }
  }
  return retval;
}

struct Output
{
  Output(uint8_t _pin, bool _days[7], Time_range* _times, uint8_t _times_count)
  : pin(_pin)
  , days(convert_days(_days))
  , times(_times)
  , times_count(_times_count)
  {}
  uint8_t pin;
  uint8_t days;
  Time_range* times;
  uint8_t times_count;
};

bool chceck_day(const uint8_t days, const DateTime& now)
{
  return (days & (1 << now.dayOfTheWeek()));
}

bool compare_time(const uint8_t h, const uint8_t m, const DateTime& now)
{
  return ((h == now.hour()) && (m == now.minute()));
}

Action is_action(const Time_range* times, const uint8_t times_count, const DateTime& now)
{
  for (uint8_t i = 0; i < times_count; i++)
  {
    if (compare_time(times[i].hour_start, times[i].minute_start, now))
    {
      return Action::start;
    }
    else if (compare_time(times[i].hour_stop, times[i].minute_stop, now))
    {
      return Action::stop;
    }
  }
  return Action::none;
}

void check_action(const Output& output, const DateTime& now)
{
  if (chceck_day(output.days, now))
  {
    auto action = is_action(output.times, output.times_count, now);
    switch (action)
    {
      case Action::start:
        digitalWrite(output.pin, HIGH);
        break;
      case Action::stop:
        digitalWrite(output.pin, LOW);
        break;
      default:
        break;
    }
  }
}

RTC_DS1307 m_rtc;

const uint32_t m_refresh_time_ms = 60000;

// CONFIGURATION

const uint8_t m_button_pin = 7;

const uint8_t m_light_pin = 1;
const uint8_t m_light_range_count = 2;
Time_range m_light[m_light_range_count]{Time_range(8, 20, 9, 40), Time_range(20, 10, 23, 40)};

const uint8_t m_pump_pin = 5;
const uint8_t m_pump_range_count = 1;
Time_range m_pump[m_pump_range_count]{Time_range(10, 0, 10, 10)};

// from 0 (Sunday) to 6 (Saturday)
bool week[7]{false, true, false, true, false, true, false};

const uint8_t m_opoutputs_count = 2;
Output m_outputs[m_opoutputs_count]{{m_light_pin, week, m_light, m_light_range_count}, {m_pump_pin, week, m_pump, m_pump_range_count}};

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

  pinMode(m_button_pin, INPUT_PULLUP);
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

  if (digitalRead(m_button_pin) == LOW)
  {
    auto state = digitalRead(m_light_pin);
    digitalWrite(m_light_pin, ~state);
  }
}