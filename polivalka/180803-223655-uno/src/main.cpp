//----------------------------------------------------------------------------------------------------------------------------------------
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

//----------------------------------------------------------------------------------------------------------------------------------------
// подготовка к работе с дисплеем
//#include "U8glib.h"                                            // Подключаем библиотеку U8glib
//U8GLIB_ST7920_128X64_1X u8g(10);                               // Создаём объект u8g для работы с дисплеем, указывая номер вывода CS для аппаратной шины SPI
//uint32_t                timeStart;                             // Объявляем переменную для подсчёта количества секунд прошедших с момента старта скетча
//uint8_t                 timeHours;                             // Объявляем переменную для вывода часов  прошедших с момента старта скетча
//uint8_t                 timeMinutes;                           // Объявляем переменную для вывода минут  прошедших с момента старта скетча
//uint8_t                 timeSeconds;                           // Объявляем переменную для вывода секунд прошедших с момента старта скетча
//----------------------------------------------------------------------------------------------------------------------------------------
const boolean debbug = false;     //если нужны сообщения в терминал по коду check_hum, поставить TRUE
//const boolean subdebbug = false;  //если нужны сообщения в терминал по коду аварийной подпрограммы , поставить TRUE
//const boolean buzzer = false;     //если жужжание разрешено, поставить TRUE
const boolean testdebbug = false; //если нужны сообщения по коду check_sensor, поставить TRUE
//const boolean testpause = true;  //если нужны сообщения о паузе 1 сек, поставить TRUE
const boolean loopdebbug = true;  //если нужны сообщения по коду основной программы, поставить TRUE

const unsigned char    sensorNumb = 2;     //количество датчиков - не более 6 (потом надо переделать на отдельную АЦП)
const unsigned char    powerPin = 9;       //номер пина включения питания на датчиках
volatile unsigned short int  sensorHum;          //значение влажности в килопопугаях
//const unsigned char    redPin = 2;       //выход красного светодиода мало воды
//const unsigned char    yellowPin = 3;    //выход желтого светодиода много воды
//const unsigned char    greenPin = 4;     //выход зеленого светодиода норм воды
//const unsigned char    errorPin = 5;     //вход датчика пролива воды
const unsigned char    testPin = 7;        //вход кнопки принудительной проверки влажности
boolean testOn;
volatile unsigned int sec;
volatile unsigned short int BASEH[(sensorNumb)]; //база значений последнего измерения с датчиков

//boolean       buzzOn;           //нужно ли жужжать именно сейчас?
//const unsigned char    buzzPIN = 6;      //выход пищалки/жужжалки

unsigned char          sensN;            //переменная - номер текущего датчика

const short unsigned int     maxHum = 500;     //значение датчика, меньше которого - много воды
const short unsigned int     minHum = 1000;    //значение датчика, больше которого - мало воды
const short unsigned int     zaderSec = 3600;  //задержка в секундах, 3600 = 1 час

//----------------------------------------------------------------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  pinMode((powerPin), OUTPUT);
  //  pinMode((redPin), OUTPUT);
  //  pinMode((yellowPin), OUTPUT);
  //  pinMode((greenPin), OUTPUT);
  //  pinMode((buzzPIN), OUTPUT);
  //  pinMode((errorPin), INPUT);
  pinMode((testPin), INPUT);
  //  digitalWrite((yellowPin), LOW); digitalWrite((greenPin), LOW); digitalWrite((redPin), LOW);
  init_analog_ports (sensorNumb);
};
//----------------------------------------------------------------------------------------------------------------------------------------
// основной цикл
void loop() {
  testOn = false;
  //  buzzOn = false;                                                 //сбрасываем признак пищания
  Serial.println("++++++++++++");                                 //печатаем в терминал плюсики
  if (loopdebbug) {
    Serial.println("launch check sensor"); //печатаем в терминал
  };
  check_sensors(sensorNumb);
  if (loopdebbug) {
    Serial.println("end check sensor");  //печатаем в терминал
  };
  sensN = 1;                                                        //выбираем номер датчика - пока первый

  while (sensN <= (sensorNumb)) {
   
    sensorHum = BASEH[sensN];                                     //копируем в базу данных выводную переменную значение датчика
    if (loopdebbug) {
    Serial.print("Датчик "); Serial.print(sensN);  Serial.print(" из "); Serial.print(sensorNumb); //печатаем в терминал
    Serial.print(" влажность = "); Serial.println(sensorHum);       //печатаем в терминал значение влажности
  };
    sensN ++;
  };
  //  colorDiod (0);                                                  //диоды выключаем подпрограммой
  //  colorDiod (3);                                                  //включаем зеленый диод
  //
  //displayprint();

  //  //сверяем влажность с предельными значениями
  //  if (sensorHum < maxHum) {
  //    colorDiod (2); buzzOn = true;                                 //если мокро, включаем желтый и жужжим
  //  };
  //  if (sensorHum > minHum) {
  //    colorDiod (1); buzzOn = true;                                 //если сухо, включаем красный и жужжим
  //  };
  //  if (errorPin == HIGH) {                                         //если протечка, вызываем аварийную подпрограмму errorPinOut
  //    errorPinOut();
  //  };
  volatile unsigned int n;                                                          //инициализируем внутренний счетчик секунд задержки
  n = 0;
     if (loopdebbug) {
    Serial.print("n = "); Serial.print(n);  Serial.print(" условие = "); Serial.println((n) < (zaderSec)); //печатаем в терминал
  };
  while ((n) < (zaderSec)) {
    if (digitalRead(testPin) == 1) {
      testOn = true;
    }
    else {
      testOn = false;
    };
    if (testOn) {
      check_sensors(sensorNumb);
      //displayprint();
    };


    //    if ((buzzOn) == true) {
    //      buzz();
    //    };
    //    if (errorPin == HIGH) {
    //      errorPinOut();
    //    };
    sec = 1;
    delay(1000 * (sec));//pausa(1);

  };
  n ++;
};
//----------------------------------------------------------------------------------------------------------------------------------------
//void pausa(int sec) {
//  delay(1000 * (sec));
//  if (testpause)   {
//    Serial.print("pause 1 sec; "); //сообщение пауза 1 sec
//  };
//  ;
//};
//----------------------------------------------------------------------------------------------------------------------------------------
void check_sensors (unsigned char sensorsNumb) {
  volatile unsigned short int h;
  unsigned char n;
  n = 1;
  while (!(n > (sensorsNumb))) {
    if (testdebbug) {
      Serial.print("base n = ");
      Serial.println(n);
    };

    BASEH[n] = check_hum(n);

    if (testdebbug) {
      //      Serial.print("HUM = ");
      //      Serial.println(h);
      Serial.print("BASEH = ");
      Serial.println(BASEH[n]);
      Serial.println("---------------------------------------------------------------------");
    };
    n += 1;
  };
  n = 1;
  return;
};
//----------------------------------------------------------------------------------------------------------------------------------------
volatile unsigned short int check_hum (unsigned char sensorPin) {
  volatile unsigned short int h; //значение текущего датчика, в килопопугаях
  volatile unsigned short int hSredn; //среднее значение текущего датчика, в килопопугаях
  volatile unsigned short int hSumm; //сумма значений текущего датчика, в килопопугаях
  const unsigned char povtor = 3; //количество опросов датчика
  unsigned char n; //счетчик
  n = 0;
  if (debbug) {
    Serial.println("--------------------------");
    Serial.println("nachalo check_hum");
    Serial.println("--------------------------");
  };
  digitalWrite((powerPin), 1);
  if (debbug) {
    Serial.print("powerpin ");  //состояние питания датчика
    Serial.println(digitalRead (powerPin));
  };
  if (debbug) {
    Serial.print("sensor ");  //включаем порт питания датчика
    Serial.print(sensorPin);
    Serial.println  (" power on");
  };
  sec = 1;
  delay(1000 * (sec));
  //pausa(1); //пауза
  if (debbug) {
    Serial.println("--------------------------");
  };
  hSumm = 0;                              // обнуляем сумму значений
  if (debbug) {
    Serial.print("hSumm = ");  //сумма значений
    Serial.println(hSumm);
    Serial.print("n = ");  //сумма значений
    Serial.println(n);
    Serial.print("povtor = ");  //сумма значений
    Serial.println(povtor);
    Serial.print("uslovie = ");  //сумма значений
    Serial.println(((n) < (povtor)));
  }
  while ((n) < (povtor)) {                    // повторяем замер несколько раз
    if (debbug) {
      Serial.print("n = ");  //сумма значений
      Serial.println(n);
    };
    h = 1500;                             //значение текущей переменной ставим в "великая сушъ"
    if (debbug) {
      Serial.print("h = ");  //сумма значений
      Serial.println(h);
    };
    h = analogRead(A0 + sensorPin - 1);
    hSumm = +h;                           //накапливаем значения
    if (debbug) {
      Serial.print("zamer = ");               //печатаем номер замера
      Serial.println(n);
      Serial.print("h = ");               //печатаем текущее значение датчика
      Serial.print(h);
      Serial.println  (" kilopopugaev");
      Serial.println("--------------------------");
    };
    if (debbug) {
      Serial.print("hSumm = ");               //печатаем среднее значение датчика
      Serial.print(hSumm);
      Serial.println  (" kilopopugaev");
      Serial.println("--------------------------");
    };
    n++;                               //увеличиваем счетчик
    //pausa(1); //пауза
    sec = 1;
    delay(1000 * (sec));
  };
  n = 0;
//  digitalWrite((powerPin), 0);
    if (debbug) {
    Serial.print("powerpin ");  //состояние питания датчика
    Serial.println(digitalRead (powerPin));
  };
  if (debbug) {
    Serial.print("sensor ");               //выключаем порт питания датчика
    Serial.print(sensorPin);
    Serial.println  (" power off");
  };
  hSredn = hSumm / povtor;                //вычисляем среднее значение
    if (debbug) {
    Serial.print("hSredn = ");  //состояние питания датчика
    Serial.println(hSredn);
  };
  if (debbug) {
    Serial.println("----");
    Serial.println("konec check_hum");
    Serial.println("----");
  };
  hSumm = 0;
  return hSredn;                          // возвращаем среднее значение
};
//----------------------------------------------------------------------------------------------------------------------------------------
void init_analog_ports(unsigned char sensorNumbInit) {
  // начало инициализации аналоговых портов
  unsigned char n; //внутренний счетчик
  n = 0; //обнуляем счетчик
  while (!(n + 1) >= (sensorNumbInit)) {
    pinMode((A0 + n), INPUT); //инициализируем аналоговые входы, начиная с нулевого (порты данных датчиков)
    n += 1;
  };
  // конец инициализации аналоговых портов
  return;
};
//----------------------------------------------------------------------------------------------------------------------------------------
// Это аварийная подпрограмма.
// Если на нее попало управление, она работает (жужжит и мигает), пока ручками не перезагрузишь устройство.
// Она безусловно пищит/жужжит и мигает лампочками, вне зависимости от разрешения жужжать в начале программы.

//void errorPinOut() {
//    if (subdebbug) {
//    Serial.print("------------------");  //
//    Serial.println  ("submodule errorPin");
//    };
//  const boolean errorBit = true; //внутренний признак
//  while ((errorBit) == true) {
////    tone (buzzPIN, 1000); //включаем на 1000 Гц
//    colorDiod (0);
//  sec=1;
//      delay(1000 * (sec));

//    Serial.println  ("error");
////    tone(buzzPIN, 500); //включаем на 500 Гц
//    colorDiod (4);
//      delay(1000 * (sec));
//  };
//};
//----------------------------------------------------------------------------------------------------------------------------------------

//void buzz() {
// unsigned char n;
//  n = 0;
//  if (buzzer == true) {
//    while ((n) < 10) {
//      n += 1;
//      tone (buzzPIN, 500); //включаем на 500 Гц
//
//      delay(100); //ждем 100 Мс
//
//      tone(buzzPIN, 1000); //включаем на 1000 Гц
//
//      delay(100); //ждем 100 Мс
//    };
//  };
//  noTone (buzzPIN);
//};

//----------------------------------------------------------------------------------------------------------------------------------------

//void colorDiod(unsigned char color) {
//  boolean greenDiod;
//  boolean yellowDiod;
//  boolean redDiod;
//  greenDiod = LOW;
//  yellowDiod = LOW;
//  redDiod = LOW;
//  changeDiod(greenDiod, yellowDiod, redDiod);
//  if ((color) == 0) {
//    greenDiod = LOW;
//    yellowDiod = LOW;
//    redDiod = LOW;
//  };
//  if ((color) == 1) {
//    greenDiod = LOW;
//    yellowDiod = LOW;
//    redDiod = HIGH;
//  };
//  if ((color) == 2) {
//    greenDiod = LOW;
//    yellowDiod = HIGH;
//    redDiod = LOW;
//  };
//  if ((color) == 3) {
//    greenDiod = HIGH;
//    yellowDiod = LOW;
//    redDiod = LOW;
//  };
//  if ((color) == 4) {
//    greenDiod = HIGH;
//    yellowDiod = HIGH;
//    redDiod = HIGH;
//  };
//  changeDiod(greenDiod, yellowDiod, redDiod);
//
//};

//----------------------------------------------------------------------------------------------------------------------------------------

//void changeDiod(boolean greenDiod, boolean yellowDiod, boolean redDiod) {
//  digitalWrite((yellowPin), (yellowDiod)); digitalWrite((greenPin), (greenDiod)); digitalWrite((redPin), (redDiod));
//};

//----------------------------------------------------------------------------------------------------------------------------------------

//void displayprint() {
//  // работа с дисплеем
//
//  u8g.firstPage();                                           // Всё что выводится на дисплей указывается в цикле: u8g.firstPage(); do{ ... команды ... };while(u8g.nextPage());
//  do {
//    //u8g.setColorIndex(1);                                 // Выбираем белый цвет
//    //u8g.drawBox(0, 0, 128, 11);                           // Выводим прямоугольник с координатами левого верхнего угла 0,0 и размерами 128x11 пикселей
//    //u8g.setColorIndex(0);                                 // Выбираем цвет фона
//
//    u8g.setRot180();
//
//    u8g.setFont(u8g_font_6x10);                           // Выбираем шрифт u8g_font_6x10
//    const unsigned char l = 9;
//    sensN = 1;
//    while (sensN <= (sensorNumb)) {
//      if (testdebbug) {
//        Serial.print("nachalo pechati sens ");
//        Serial.println(sensN);
//      };
//      u8g.drawStr(100, (l * sensN), "%");
//      u8g.drawStr(3, (l * sensN), "Hum sensor");                // Выводим текст
//      u8g.setPrintPos(65, l * sensN); u8g.print(sensN);         // Выводим номер сенсора
//      u8g.drawStr(73, l * sensN, "=");                          // Выводим текст "="
//      u8g.setPrintPos(82, l * sensN); u8g.print((1023 - BASEH[sensN]) * 100 / 1023); // Выводим влажность
//      //u8g.drawStr(100, l * sensN, "t");
//      if (testdebbug) {
//        Serial.print("konec pechati sens ");
//        Serial.println(sensN);
//      };
//      sec = 1;
//      //  delay(1000 * (sec)); //пауза
//      sensN += 1;
//
//    };
//
//    if (testOn == 1) {
//      u8g.drawStr(3, 50, "O");                       // Выводим текст O внизу, если нажата кнопка
//    };
//
//    //u8g.drawStr(60, 9, "Humidity");                       // Выводим текст "iarduino"        в позиции  39х9
//    //u8g.setColorIndex(1);                                 // Выбираем белый цвет
//    //u8g.drawStr(20, 62, "www.iarduino.ru");               // Выводим текст "www.iarduino.ru" в позиции  20х62
//    //
//    //      u8g.setFont(u8g_font_courB24n);                         // Выбираем шрифт u8g_font_courB24n
//    //      u8g.setPrintPos(  3, 43); u8g.print(timeHours / 10);    // Выводим старший разряд часов    в позиции   3х43
//    //      u8g.setPrintPos( 20, 43); u8g.print(timeHours % 10);    // Выводим младший разряд часов    в позиции  20х43
//    //      u8g.drawStr    ( 33, 43, ":");                          // Выводим двоеточие               в позиции  33х43
//    //      u8g.setPrintPos( 46, 43); u8g.print(timeMinutes / 10);  // Выводим старший разряд минут    в позиции  46х43
//    //      u8g.setPrintPos( 63, 43); u8g.print(timeMinutes % 10);  // Выводим младший разряд минут    в позиции  63х43
//    //      u8g.drawStr    ( 76, 43, ":");                          // Выводим двоеточие               в позиции  76х43
//    //      u8g.setPrintPos( 89, 43); u8g.print(timeSeconds / 10);  // Выводим старший разряд секунд   в позиции  89х43
//    //      u8g.setPrintPos(106, 43); u8g.print(timeSeconds % 10);  // Выводим младший разряд секунд   в позиции 106х43
//
//  }
//  while (u8g.nextPage());
//  return;
//};
