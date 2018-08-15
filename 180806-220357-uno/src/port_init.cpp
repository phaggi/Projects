#include "port_init.h"
bool port_digital_init (int8_t _sensorNumb, int8_t _powerPins[], bool _sensor_present[])
{
bool _error = false;
                          if (DEBBUG)
                          {
                            Serial.println("nachalo port_init");
                          };
  for (int8_t _powerPin=0;_powerPin<_sensorNumb;_powerPin++) //перебираем порты
  {
                          if (DEBBUG)
                          {
                            Serial.print(_powerPin);Serial.println(" port_init output");
                          };
    if (_sensor_present[_powerPin])
    {
      pinMode(_powerPins[(_powerPin)], OUTPUT);    //назначаем порт, соответствующий датчику, выходом
        delay(100);//pausa(0.1);
      digitalWrite((_powerPins[(_powerPin)]), LOW); //делаем порт, соответствующий датчику, LOW
      if (digitalRead(_powerPins[(_powerPin)]))        //проверяем, стал ли порт LOW
      { 
        _error=true;
        Serial.print("ERROR! power port ");Serial.print(_powerPin);Serial.println("not LOW!");
            delay(100);//pausa(0.1);
      }
    }
  }
  return (!_error);
}
  // ----- конец цикла инициализации портов питания датчиков