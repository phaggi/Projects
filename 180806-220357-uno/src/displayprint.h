#include <U8glib.h>
#include <Arduino.h>
void displayprint(int8_t _sensorNumb,bool _sensor_present[], int16_t _baseH[], bool _testOn);
#define _DEBBUG 1
#define _STEP 9
#define _HUMSENSTEXT_COLUMN 3
#define _NUMSENS_COLUMN 65
#define _EQAL_COLUMN 73
#define _HUM_COLUMN 82
#define _PERCENT_COLUMN 100
#define _BUTTON_PRESSED_COLUMN 120
#define _BUTTON_PRESSED_ROW 3
#define _SEC 0