#include"main.h"
void setup()
{
    TIMER_START();
    Serial.begin (115200);
    Serial.println(LED_PIN);
    bool SENSOR_PRESENT [SENSOR_NUMB]={SENSOR1, SENSOR2, SENSOR3, SENSOR4}; //инициализируется база наличия сенсоров
    int16_t BASEH[SENSOR_NUMB]={111,222,333,444};                           //инициализируется тестовая база состояния сенсоров 
    bool TESTON=0;                                                          //1 - кнопка нажата, 0 - не нажата
    displayprint(SENSOR_NUMB, SENSOR_PRESENT, BASEH, TESTON);

}
void loop()
{
//     delay (1000);
//     Serial.print(TIME_FROM_LAUNCH/36000);Serial.print((TIME_FROM_LAUNCH/3600)%10);Serial.print(":");Serial.print((TIME_FROM_LAUNCH/60%60)/10);Serial.print((TIME_FROM_LAUNCH/60%60)%10);Serial.print(":");Serial.print((TIME_FROM_LAUNCH%60)/10);Serial.println((TIME_FROM_LAUNCH%60)%10);
}