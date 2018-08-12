#include "main.h"
//подготовка к работе с дисплеем
                                          // Подключаем библиотеку U8glib
U8GLIB_ST7920_128X64_1X u8g(10);                               // Создаём объект u8g для работы с дисплеем, указывая номер вывода CS для аппаратной шины SPI
uint32_t                timeStart;                             // Объявляем переменную для подсчёта количества секунд прошедших с момента старта скетча
uint8_t                 timeHours;                             // Объявляем переменную для вывода часов  прошедших с момента старта скетча
uint8_t                 timeMinutes;                           // Объявляем переменную для вывода минут  прошедших с момента старта скетча
uint8_t                 timeSeconds;                           // Объявляем переменную для вывода секунд прошедших с момента старта скетча

void displayprint() {
  // работа с дисплеем

  u8g.firstPage();                                           // Всё что выводится на дисплей указывается в цикле: u8g.firstPage(); do{ ... команды ... };while(u8g.nextPage());
  do {
    //u8g.setColorIndex(1);                                 // Выбираем белый цвет
    //u8g.drawBox(0, 0, 128, 11);                           // Выводим прямоугольник с координатами левого верхнего угла 0,0 и размерами 128x11 пикселей
    //u8g.setColorIndex(0);                                 // Выбираем цвет фона

    u8g.setRot180();

    u8g.setFont(u8g_font_6x10);                           // Выбираем шрифт u8g_font_6x10
    const unsigned char l = 9;
    sensN = 1;
    while (sensN <= (sensorNumb)) {
      if (testdebbug) {
        Serial.print("nachalo pechati sens ");
        Serial.println(sensN);
      };
      u8g.drawStr(100, (l * sensN), "%");
      u8g.drawStr(3, (l * sensN), "Hum sensor");                // Выводим текст
      u8g.setPrintPos(65, l * sensN); u8g.print(sensN);         // Выводим номер сенсора
      u8g.drawStr(73, l * sensN, "=");                          // Выводим текст "="
      u8g.setPrintPos(82, l * sensN); u8g.print((1023 - BASEH[sensN]) * 100 / 1023); // Выводим влажность
      //u8g.drawStr(100, l * sensN, "t");
      if (testdebbug) {
        Serial.print("konec pechati sens ");
        Serial.println(sensN);
      };
      sec = 1;
      //  delay(1000 * (sec)); //пауза
      sensN += 1;

    };

    if (testOn == 1) {
      u8g.drawStr(3, 50, "O");                       // Выводим текст O внизу, если нажата кнопка
    };

    //u8g.drawStr(60, 9, "Humidity");                       // Выводим текст "iarduino"        в позиции  39х9
    //u8g.setColorIndex(1);                                 // Выбираем белый цвет
    //u8g.drawStr(20, 62, "www.iarduino.ru");               // Выводим текст "www.iarduino.ru" в позиции  20х62
    //
    //      u8g.setFont(u8g_font_courB24n);                         // Выбираем шрифт u8g_font_courB24n
    //      u8g.setPrintPos(  3, 43); u8g.print(timeHours / 10);    // Выводим старший разряд часов    в позиции   3х43
    //      u8g.setPrintPos( 20, 43); u8g.print(timeHours % 10);    // Выводим младший разряд часов    в позиции  20х43
    //      u8g.drawStr    ( 33, 43, ":");                          // Выводим двоеточие               в позиции  33х43
    //      u8g.setPrintPos( 46, 43); u8g.print(timeMinutes / 10);  // Выводим старший разряд минут    в позиции  46х43
    //      u8g.setPrintPos( 63, 43); u8g.print(timeMinutes % 10);  // Выводим младший разряд минут    в позиции  63х43
    //      u8g.drawStr    ( 76, 43, ":");                          // Выводим двоеточие               в позиции  76х43
    //      u8g.setPrintPos( 89, 43); u8g.print(timeSeconds / 10);  // Выводим старший разряд секунд   в позиции  89х43
    //      u8g.setPrintPos(106, 43); u8g.print(timeSeconds % 10);  // Выводим младший разряд секунд   в позиции 106х43

  }
  while (u8g.nextPage());
  return;
};
