#define SCREEN_SYNC				    13
#define SCREEN_PITCH			    12
#define SCREEN_DATA				    10

#define PORT_BUZZ				      9
#define PORT_NASOS				    8
#define PORT_BUTTON				    7
#define PRESS_BUTTON			    1

#define SENSOR0					      1
#define SENSOR1					      1
#define SENSOR2				    	  1
#define SENSOR3					      0

#define PORT_POWER_SENSOR0		2
#define PORT_POWER_SENSOR1		3
#define PORT_POWER_SENSOR2		4
#define PORT_POWER_SENSOR3		5

#define PORT_ANALOG_SENSOR0		0
#define PORT_ANALOG_SENSOR1		1
#define PORT_ANALOG_SENSOR2		2
#define PORT_ANALOG_SENSOR3		3

#define SENSOR_NUMB				    4
#define PORT_ANALOG_SENSOR		[PORT_ANALOG_SENSOR1, PORT_ANALOG_SENSOR2, PORT_ANALOG_SENSOR3, PORT_ANALOG_SENSOR4]

#define ERROR_DIGITAL_PORT		"ERROR1"
#define ERROR_WATER_ON_FLOOR	"ERROR2"

void port_nasos_init 			    (void);
void port_digital_init 			  (void);
void port_analog_init 		  	(void);

void port_digital_low 		  	(void);
void port_digital_high 		  	(void);
void port_digital_read		  	(void);
void port_digital_write 	  	(void);

void error_port 			      	(void);

void screen_init 			      	(void);
void screen_write			      	(void);

void power_sensor_on	    		(void);
void power_sensor_off	    		(void);

void wifi_init				      	(void);
void lan_init				        	(void);
void inet_test			      		(void);
void nasos_on				        	(void);
void nasos_off			      		(void);
void sensor_read			      	(void);
void get_state_button	     		(void);
void get_state_sensor	    		(void);

void timer_real_init	    		(void);
void timer_real_read		    	(void);

void buzz_init				      	(void);
void buzz_on			        		(void);
void buzz_off			        		(void);

#define BIT0					1
#define BIT1					2
#define BIT2					4
#define BIT3					8
#define BIT4					16
#define BIT5					32
#define BIT6					64
#define BIT7					128
#define BIT8					256
#define BIT9					512
#define BITA					1024
#define BITB					2048
#define BITC					4096
#define BITD					8192
#define BITE					16384
#define BITF					32768