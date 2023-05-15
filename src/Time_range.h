/**
 * @file Time_range.h
 * @brief Time range structure
 * @author by Szymon Markiewicz
 * @details http://www.inzynierdomu.pl/
 * @date 05-2023
 */

#pragma once

#include <stdint.h>
struct Time_range
{
  /*
  @brief Constructor Time_range.
  @param _hour_start: starting hour of the time range.
  @param _minute_start: starting minute of the time range.
  @param _hour_stop: ending hour of the time range.
  @param _minute_stop: ending minute of the time range.
  */
  Time_range(const uint8_t _hour_start, const uint8_t _minute_start, const uint8_t _hour_stop, const uint8_t _minute_stop)
  : hour_start(_hour_start)
  , minute_start(_minute_start)
  , hour_stop(_hour_stop)
  , minute_stop(_minute_stop)
  {}

  const uint8_t hour_start; ///< Starting hour of the time range
  const uint8_t minute_start; ///< Starting minute of the time range.
  const uint8_t hour_stop; ///< Ending hour of the time range.
  const uint8_t minute_stop; ///< Ending minute of the time range.
};
