#include "displayprint.h"
//подготовка к работе с дисплеем
                                          // Подключаем библиотеку U8glib

void displayprint(int8_t _sensorNumb,bool _sensor_present[], int16_t _baseH[], bool _testOn) 
{
  // работа с дисплеем
  U8GLIB_ST7920_128X64_1X u8g(10);                         // Создаём объект u8g для работы с дисплеем, указывая номер вывода CS для аппаратной шины SPI
                       // Создаём объект u8g для работы с дисплеем, указывая номер вывода CS для аппаратной шины SPI

  u8g.firstPage();                                         // Всё что выводится на дисплей указывается в цикле: u8g.firstPage(); do{ ... команды ... };while(u8g.nextPage());
  do 
  {
    //u8g.setColorIndex(1);                                 // Выбираем белый цвет
    //u8g.drawBox(0, 0, 128, 11);                           // Выводим прямоугольник с координатами левого верхнего угла 0,0 и размерами 128x11 пикселей
    //u8g.setColorIndex(0);                                 // Выбираем цвет фона

    u8g.setRot180();                                        //повернул экран, т.к. он у меня кверхногами был; можно убрать, если не нужно

    u8g.setFont(u8g_font_6x10);                             // Выбираем шрифт u8g_font_6x10
    // const uint8_t _STEP = 9; //
    for (int8_t _sensN = 0;_sensN < (_sensorNumb);_sensN++) //перебираем датчики
    {
                          if (_DEBBUG)                      // дебаг
                          {
                            Serial.print("nachalo pechati sens ");
                            Serial.println(_sensN);
                          };                                // /дебаг
      int8_t _stepline=(_STEP * _sensN);                    //задаем шаг строк на экране 
      if ((_stepline)<64)                                   //если не вышли за границу экрана, пишем следующую строку про датчики 
      {
        if(_sensor_present[_sensN])                         //проверяем наличие сенсора по базе
        {                                                   //если сенсор есть, печатаем показания
            u8g.drawStr(_HUMSENSTEXT_COLUMN, (_stepline), "Hum sensor");                // Выводим текст
            u8g.setPrintPos(_NUMSENS_COLUMN, _stepline); u8g.print(_sensN);             // Выводим номер сенсора
            u8g.drawStr(_EQAL_COLUMN, _stepline, "=");                                  // Выводим текст "="
            u8g.setPrintPos(_HUM_COLUMN, _stepline); u8g.print((1023 - _baseH[_sensN]) * 100 / 1023); // Выводим влажность
            u8g.drawStr(_PERCENT_COLUMN, (_stepline), "%");                             // значок процента после значения влажности
                          if (_DEBBUG)                      // дебаг
                          {
                            Serial.print("sens ");Serial.print(_sensN);Serial.print(" hum ");
                            Serial.println(_baseH[_sensN]);
                            Serial.println(u8g.nextPage());
                          };                                // /дебаг

        }
        else                                                //если сенсора нет, печатаем об этом сообщение
        {
            u8g.drawStr(_HUMSENSTEXT_COLUMN, (_stepline), "Hum sensor");                // Выводим текст
            u8g.setPrintPos(_NUMSENS_COLUMN, _stepline); u8g.print(_sensN);             // Выводим номер сенсора
            u8g.drawStr(_EQAL_COLUMN, _stepline, "is off");                             // Выводим текст
                          if (_DEBBUG)                      // дебаг
                          {
                            Serial.print("sens ");Serial.print(_sensN); Serial.println(" is off ");
                            Serial.println(u8g.nextPage());
                          };                                // /дебаг
        }

      }
      else                                                  //если вышли за границу экрана, пишем об этом в дебаг и завершаем печать сообщений про датчики
      {
                          if (_DEBBUG)                      // дебаг
                          {
                            Serial.print("ERROR! End of screen.");
                            Serial.println(_sensN);
                          };                                // /дебаг
      }
                          if (_DEBBUG)                      // дебаг
                          {
                            Serial.print("konec pechati sens ");
                            Serial.println(_sensN);
                          };                                // /дебаг

     // delay(1000 * (_SEC));                                 //пауза

    };

    if (_testOn == 1)                                       //проверяем, нажата ли кнопка
    {                                                         
      u8g.drawStr(_BUTTON_PRESSED_COLUMN, _BUTTON_PRESSED_ROW, "O");            // Выводим текст O справа, если нажата кнопка
                          if (_DEBBUG)                      // дебаг
                          {
                            Serial.println("knopka nazhata");
                          };                                // /дебаг
    };
    
    // закомментированный код ниже остался от примера, и пока пусть болтается
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
  while (u8g.nextPage());                                   //команда отрисовки экрана
  return;
};
