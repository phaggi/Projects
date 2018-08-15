/*****************************************************
Project	: Control Driver Step Motor
Version	: 0.1
Date		: 01.04.2016	
Author	:	Kudinov M.YU.
Company	: KibIS
Comments:	CNC_0.1

Chipe type  							: AtMega8515 PDIP-40
Programe type							:	gcc
AVR core clock frequency	: 16MHz
Memory model							:
External RAM size					:
Data stack size						:
******************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>

//_____________________________
#define WindingA 0x01 // 0000 0001
#define WindingB 0x02 // 0000 0010
#define WindingC 0x04 // 0000 0100
#define WindingD 0x08 // 0000 1000

unsigned char cw_dir[4] = {WindingA,WindingB,WindingC,WindingD};
unsigned char ccw_dir[4] = {WindingD,WindingC,WindingB,WindingA};

volatile unsigned char cStep_index;
volatile unsigned int iTimes_ovf;
volatile unsigned char cStatus_move;
//=============================

//_____________________________
ISR(INT0_vect){
	cStatus_move = 0;
}
ISN(INT1_vect){
	cStatus_move = 1;
}
ISR(TIMER0_OVF_vect){
	static unsigned int iCount = 1;
	iCount++;
	if(iCount >= iTimes_ovf){
		cli();

		if (cStatus_move)
			PORTB = ccw_dir[cStep_index++];
		else
			PORTB = cw_dir[cStep_index++];

		if(cStep_index >= 4)
				cStep_index = 0;
		
		iCount = 0;
		TCNT0 = 0;
		sei();
	}
}
//=============================
//_____________________________
void Init_PIN(void){
	DDRB = 0x0F;
	PORTB = 0x00;
}
//=============================
//_____________________________
void Init_INTERRUPT(void){
GICR=0b11000000;  /*General Interrupt Control Register  
                  100x xxxx - по выводу int1;
                  010x xxxx - по выводу int0;
                  001x xxxx - по выводу int2 */ 

MCUCR=0b00001010; /*Micro Controller Unit Control Registr 
                  xxxx 10 00 - по спадающему фронту сигнала на выводе int1; 
                  xxxx 11 00 - по нарастающему фронту сигнала на выводе int1;
                  xxxx 00 00 - по низкому уровню на выводе int1;
                  xxxx 01 00 - по любому изменению уровня на выводе int1 ;
									
									xxxx 00 10 - по спадающему фронту сигнала на выводе int0; 
                  xxxx 00 11 - по нарастающему фронту сигнала на выводе int0;
                  xxxx 00 00 - по низкому уровню на выводе int0;
                  xxxx 00 01 - по любому изменению уровня на выводе int0 */
}
//=============================

void main(void)
{
	Init_PIN();
	Init_INTERRUPT();
	
	cStep_index = 0;
	iTimes_ovf = 10; // первоначальная задержка
	cStatus_move = 0;
	while(1){
		cStep_index = 1;
	}	
}





















