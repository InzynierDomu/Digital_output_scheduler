#pragma once

#include <stdint.h>
#include "Time_range.h"

enum class Action
{
  start,
  stop,
  none
};

uint8_t convert_days(const bool days[7])
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
  Output(const uint8_t _pin, const bool _days[7], Time_range* _times, const uint8_t _times_count)
  : pin(_pin)
  , days(convert_days(_days))
  , times(_times)
  , times_count(_times_count)
  , state(Action::none)
  {}
  const uint8_t pin;
  const uint8_t days;
  Time_range* times;
  const uint8_t times_count;
  Action state;
};