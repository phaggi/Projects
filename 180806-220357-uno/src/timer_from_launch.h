#include <Arduino.h>
#include <timer-api.h>

#ifndef TIME_FROM_LAUNCH
  #define TIME_FROM_LAUNCH _timer_from_launch(0)
#endif

uint32_t _timer_from_launch(bool inout);
// void _timer_start();
#ifndef TIMER_START()
  #define TIMER_START() timer_init_ISR_1Hz(TIMER_DEFAULT)
#endif