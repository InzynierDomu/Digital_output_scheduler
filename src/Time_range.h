#pragma once

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
