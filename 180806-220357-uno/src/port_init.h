#include <Arduino.h>
#include <SoftwareSerial.h>

#ifndef DEBBUG
  #define DEBBUG 1
#endif //DEBBUG
bool port_digital_init (int8_t _sensorNumb, int8_t _powerPins[], bool _sensor_present[]);
void port_analog_init (int8_t _sensorNumb, int8_t _sensorPins[], bool _sensor_present[]);
