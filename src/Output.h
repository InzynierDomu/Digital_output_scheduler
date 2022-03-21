#pragma once

#include "Time_range.h"

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