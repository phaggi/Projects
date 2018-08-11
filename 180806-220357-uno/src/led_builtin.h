const int8_t _led_pin ();
#ifndef LED_PIN
  #define LED_PIN _led_pin()
#endif //LED_PIN