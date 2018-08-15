#include "port_init.h"

// ----- цикл инициализации портов питания датчиков
powerPin=1;// начинаем с 1 порта
if (setdebbug) {
    Serial.println("nachalo powerport");
  };
while (powerPin <= sensorNumb){
  pinMode((powerPins[(powerPin)]), OUTPUT);//назначаем порт, соответствующий датчику, выходом
     delay(100 * (sec));//pausa(0.1);
  digitalWrite((powerPins[(powerPin)]), LOW);//делаем порт, соответствующий датчику, LOW
  if (digitalRead(powerPins[(powerPin)])){ //проверяем, стал ли порт LOW
    Serial.print("power port ");Serial.print(powerPin);Serial.println("not initialised");
         delay(100 * (sec));//pausa(0.1);
  } ;
  if (setdebbug) {
    Serial.print("powerport ");Serial.print(powerPin);Serial.println(" vypolnen");
  };
  powerPin++;//следующий порт
  };
powerPin=1;//сбрасываем счетчик портов
if (setdebbug) {
    Serial.println("konec powerport");
  };
  // ----- конец цикла инициализации портов питания датчиков