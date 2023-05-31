# Digital output scheduler

![GitHub Workflow Status](https://img.shields.io/github/actions/workflow/status/InzynierDomu/Digital_output_scheduler/main.yml?logo=github&style=flat-square)
![GitHub release (latest SemVer)](https://img.shields.io/github/v/release/InzynierDomu/Digital_output_scheduler?style=flat-square)
<a href="https://inzynierdomu.github.io/Digital_output_scheduler/">![GitHub docs deployments](https://img.shields.io/github/deployments/InzynierDomu/Digital_output_scheduler/github-pages?label=docs&logo=BookStack&logoColor=white&style=flat-square)</a>
<a href="https://discord.gg/KmW6mHdg">![Discord](https://img.shields.io/discord/815929748882587688?logo=discord&logoColor=green&style=flat-square)</a>
![GitHub](https://img.shields.io/github/license/InzynierDomu/Digital_output_scheduler?style=flat-square)
<a href="https://tipo.live/p/inzynierdomu">![support](https://img.shields.io/badge/support-tipo.live-yellow?style=flat-square)</a>

- [Digital output scheduler](#digital-output-scheduler)
  - [About](#about)
  - [Scheme](#scheme)
  - [IDE](#ide)

## About
This is an easily editable project for controlling time-related sequences of two-state output.<br>
In the //CONFIGURATION part, define the output and sequences as in the example below.
```cpp
const uint8_t m_light_pin = 9;
const uint8_t m_light_range_count = 2;
Time_range m_light[m_light_range_count]{Time_range(13, 26, 16, 40), Time_range(20, 10, 23, 40)};
```
This will turn on pin 9 from 13:26 to 16:40 and from 20:10 to 23:40. You should specify the number of these sequences, i.e. 2.<br>
Preparing a schedule of days when the output will be switched is needed as in the example below.
```cpp
// from 0 (Sunday) to 6 (Saturday)
bool week_holiday[7]{false, true, true, true, true, true, false};
```
Will work from Monday to Friday.<br>
Outputs should be associated with a given daily schedule.
```cpp
const uint8_t m_opoutputs_count = 3;
Output m_outputs[m_opoutputs_count]{{m_light_pin, week_holiday, m_light, m_light_range_count},
                                    {m_pump_pin, week, m_pump, m_pump_range_count},
                                    {m_relay_pin, week, m_relay, m_relay_range_count}};
```
There are three outputs, for example the first binds pin, and hourly and day schedules.<br>
Define the number of outputs, in this case 3.

## Scheme
Example using one relay. There doesn't have to be a relay on the output, it can be anything with two-state operation, e.g. LED. There may be more outputs, they are defined in the code.
<br>
You can use ready RTC module
![alt text](https://github.com/InzynierDomu/rtc_relay/blob/main/schem_2.PNG)
<br>
or use chip with other elements.
![alt text](https://github.com/InzynierDomu/rtc_relay/blob/main/schem_1.PNG)

Part list:
- Arduino nano
- RTC DS1307

## IDE

The project is prepared for the Platform IO environment. A video on how to install such an environment can be watched on this [video](https://youtu.be/Em9NuebT2Kc).
<br><br>
Formatting is done using clang-format. The description of the tool configuration is in the [video](https://youtu.be/xxuaOG0WjIE).
<br><br>
The code contains a comment prepared for doxygen, their use is described in the [video](https://youtu.be/1YKJtrCsPD4).`