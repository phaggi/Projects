#include <U8glib.h>
#include <Arduino.h>
#include "timer_from_launch.h"

void displayprint(int8_t _sensorNumb,bool _sensor_present[], int16_t _baseH[], bool _testOn);
#define _CS                     13, 12, 10
#define _DEBBUG                 true
#define _STEP                   9
#define _HUMSENSTEXT_COLUMN     3
#define _NUMSENS_COLUMN         65
#define _EQAL_COLUMN            73
#define _HUM_COLUMN             82
#define _PERCENT_COLUMN         100
#define _BUTTON_PRESSED_COLUMN  120
#define _BUTTON_PRESSED_ROW     7
#define _SEC                    0
#define _TIME_ROW               53
#define __TIME_COLUMN_STEP      21
#define __TIME_FONT_STEP        8
#define _TIME_COLUMN_H          42
#define _TIME_COLUMN_M          (_TIME_COLUMN_H+__TIME_COLUMN_STEP)
#define _TIME_COLUMN_S          (_TIME_COLUMN_M+__TIME_COLUMN_STEP)
#define _TIME_COLUMN_H2         (_TIME_COLUMN_H+__TIME_FONT_STEP)
#define _TIME_COLUMN_M2         (_TIME_COLUMN_M+__TIME_FONT_STEP)
#define _TIME_COLUMN_S2         (_TIME_COLUMN_S+__TIME_FONT_STEP)
#define _TIME_COLUMN_COLON1     (_TIME_COLUMN_H2+__TIME_FONT_STEP)
#define _TIME_COLUMN_COLON2     (_TIME_COLUMN_M2+__TIME_FONT_STEP)         