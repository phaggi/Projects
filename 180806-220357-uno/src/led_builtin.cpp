#include <Arduino.h>

const int8_t _led_pin ()
        {
        //блок для встроенного светодиода
        #if ARDUINO >= 100
                return LED_BUILTIN;	// 1.0 built in LED pin var
        #else
                return 13;			// default to pin 13
        #endif
        //конец блока для встроенного светодиода                
        };