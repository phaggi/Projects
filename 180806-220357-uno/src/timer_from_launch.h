#include <Arduino.h>
#include <timer-api.h>
#define time_from_launch _timer_from_launch(0)

uint32_t _timer_from_launch(bool inout);
// void _timer_start();
#define timer_start() timer_init_ISR_1Hz(TIMER_DEFAULT);