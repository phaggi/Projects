#include"main.h"
void setup()
{
    TIMER_START();
    Serial.begin (115200);
    Serial.println(LED_PIN);
};
void loop()
{
    delay (1000);
    Serial.print(TIME_FROM_LAUNCH/36000);Serial.print((TIME_FROM_LAUNCH/3600)%10);Serial.print(":");Serial.print((TIME_FROM_LAUNCH/60%60)/10);Serial.print((TIME_FROM_LAUNCH/60%60)%10);Serial.print(":");Serial.print((TIME_FROM_LAUNCH%60)/10);Serial.println((TIME_FROM_LAUNCH%60)%10);
};