#include "timer_from_launch.h"
//-----------------------------------------------------------
void _timer_start()                   //Стартуем таймер (библиотека timer-api.h)
{
    timer_init_ISR_1Hz(TIMER_DEFAULT);
};

//функция таймера сколько секунд прошло (на основе библиотеки  timer-api.h)
uint32_t _timer_from_launch(bool inout)
{
    static uint32_t _time_from_launch =0;
if (inout==1)
    {
        _time_from_launch++;
        return 0;
    }
    else
    {
        return  _time_from_launch;
    }
};
// void setup() {
//     Serial.begin(115200);
//     // freq=1Hz, period=1s
//     // частота=1Гц, период=1с
//     timer_real_init();
// };

// void loop() {
//     Serial.println(_timer_from_launch(0));
//     delay(6000);

//     // any code here: blocking or non-blocking
//     // здесь любой код: блокирующий или неблокирующий
// };
/**
 * Timer interrupt service routine, called with chosen period
 * @param timer - timer id
 */
/**
 * Процедура, вызываемая прерыванием по событию таймера с заданным периодом
 * @param timer - идентификатор таймера
 */
void timer_handle_interrupts(int timer) 
{
    // static uint32_t prev_time = 0;
    
    // uint32_t _time = micros();
    // uint32_t _period = _time - prev_time;
    // prev_time = _time;

    _timer_from_launch(1);//тут поместить код, который надо раз в секунду выполнять
};