#include <Arduino.h>
#include <timer-api.h>
#define TIME_FROM_LAUNCH _timer_from_launch(0)

uint32_t _timer_from_launch(bool inout);
// void _timer_start();
#define TIMER_START() timer_init_ISR_1Hz(TIMER_DEFAULT)