//#include "main.h"
/*
  FlexiTimer2:
  Arduino library to use timer 2 with a configurable resolution.
  Based on MsTimer2 by Javier Valencia. It is called FlexiTimer2 because it
  is based on MsTimer2, but offers more flexibility,
  since it has a configurable timer resolution.
  MsTimer2 library: http://www.arduino.cc/playground/Main/MsTimer2

For more details on FlexiTimer2 see: 
 http://www.arduino.cc/playground/Main/FlexiTimer2
 https://github.com/wimleers/flexitimer2

*/
#include"main.h"

//#include <FlexiTimer2.h>
#define TIME_FLASH 100
#define TIME_PAUSE 1000
// Switch on LED on and off each half second

#if ARDUINO >= 100
const int led_pin = LED_BUILTIN;	// 1.0 built in LED pin var
#else
const int led_pin = 13;			// default to pin 13
#endif


void setup() {
    Serial.begin(115200);
    // freq=1Hz, period=1s
    // частота=1Гц, период=1с
    timer_init_ISR_1Hz(TIMER_DEFAULT);

    // freq=2Hz, period=500ms
    // частота=2Гц, период=500мс
    //timer_init_ISR_2Hz(TIMER_DEFAULT);
    
    // freq=5Hz, period=200ms
    // частота=5Гц, период=200мс
    //timer_init_ISR_5Hz(TIMER_DEFAULT);

    //timer_init_ISR_500KHz(TIMER_DEFAULT);
    //timer_init_ISR_200KHz(TIMER_DEFAULT);
    //timer_init_ISR_100KHz(TIMER_DEFAULT);
    //timer_init_ISR_50KHz(TIMER_DEFAULT);
    //timer_init_ISR_20KHz(TIMER_DEFAULT);
    //timer_init_ISR_10KHz(TIMER_DEFAULT);
    //timer_init_ISR_5KHz(TIMER_DEFAULT);
    //timer_init_ISR_2KHz(TIMER_DEFAULT);
    //timer_init_ISR_1KHz(TIMER_DEFAULT);
    //timer_init_ISR_500Hz(TIMER_DEFAULT);
    //timer_init_ISR_200Hz(TIMER_DEFAULT);
    //timer_init_ISR_100Hz(TIMER_DEFAULT);
    //timer_init_ISR_50Hz(TIMER_DEFAULT);
    //timer_init_ISR_20Hz(TIMER_DEFAULT);
    //timer_init_ISR_10Hz(TIMER_DEFAULT);
    //timer_init_ISR_5Hz(TIMER_DEFAULT);
    //timer_init_ISR_2Hz(TIMER_DEFAULT);
    //timer_init_ISR_1Hz(TIMER_DEFAULT);

    pinMode(led_pin, OUTPUT);
}

void loop() {
    Serial.println("Hello from loop!");
    delay(5000);

    // any code here: blocking or non-blocking
    // здесь любой код: блокирующий или неблокирующий
}
/**
 * Timer interrupt service routine, called with chosen period
 * @param timer - timer id
 */
/**
 * Процедура, вызываемая прерыванием по событию таймера с заданным периодом
 * @param timer - идентификатор таймера
 */
void timer_handle_interrupts(int timer) {
    static unsigned long prev_time = 0;
    
    unsigned long _time = micros();
    unsigned long _period = _time - prev_time;
    prev_time = _time;
    
    Serial.print("goodbye from timer: ");
    Serial.println(_period, DEC);

    // blink led
    // мигаем лампочкой
    digitalWrite(led_pin, !digitalRead(led_pin));
};