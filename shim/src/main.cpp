#include <Arduino.h>
/*************************************************** 
  This is an example for our Adafruit 16-channel PWM & Servo driver
  GPIO test - this will set a pin high/low

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815

  These drivers use I2C to communicate, 2 pins are required to  
  interface.

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);
// you can also call it with a different address and I2C interface
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(&Wire, 0x40);

void setup() {
  Serial.begin(115200);
  Serial.println("GPIO test!");
  pwm.begin();
  pwm.setPWMFreq(1000);  // Set to whatever you like, we don't use it in this demo!

  // if you want to really speed stuff up, you can go into 'fast 400khz I2C' mode
  // some i2c devices dont like this so much so if you're sharing the bus, watch
  // out for this!
  Wire.setClock(400000);
    //pwm.setPWM(0, 0 , 4096);
}

void loop() {
  // Drive each pin in a 'wave'
      int16_t sec=1000;
for (int16_t _time =4000;_time >= 500;_time-=500)
{
     pwm.setPWM(0, _time, 1);       // turns pin fully on
    delay(sec);
};
 for (int16_t _time2 =1000;_time2 <= 3500;_time2+=500)
{
     pwm.setPWM(0, _time2, 1);       // turns pin fully on
    delay(sec);
};

}