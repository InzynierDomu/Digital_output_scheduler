/**
 * @file Output.h
 * @brief binding the pin and the time schedule
 * @author by Szymon Markiewicz
 * @details http://www.inzynierdomu.pl/
 * @date 05-2023
 */

#pragma once

#include "Time_range.h"

#include <stdint.h>

/**
 * @brief An enum class representing possible actions for an output.
 */
enum class Action
{
  start,
  stop,
  none
};

/**
 * @brief Converts an array of boolean values representing days of the week to a uint8_t value.
 * @param days: An array of 7 boolean values representing days of the week.
 * @return Value representing the days of the week.
 */
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
  /**
   * @brief Constructor Output.
   * @param _pin The pin number of the output.
   * @param _days An array of 7 boolean values representing the days of the week when the output is active.
   * @param _times An array of Time_range structs representing the time ranges when the output is active.
   * @param _times_count The number of time ranges in the _times array.
   */
  Output(const uint8_t _pin, const bool _days[7], Time_range* _times, const uint8_t _times_count)
  : pin(_pin)
  , days(convert_days(_days))
  , times(_times)
  , times_count(_times_count)
  , state(Action::none)
  {}

  const uint8_t pin; ///< The pin number of the output.
  const uint8_t days; ///< value representing the days of the week when the output is active.
  Time_range* times; ///<  representing the time ranges when the output is active.
  const uint8_t times_count; ///< The number of time ranges in the times array.
  Action state; ///< The current state of the output.
};