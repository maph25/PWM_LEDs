/**
 * @file    Practica_dos.c
 * @brief   Application entry point.
 */
#include "ADC.h"
#include "DataTypeDefinitions.h"
#include "Sequence.h"
#include "Manual.h"
#include "GPIO.h"
#include "Botones.h"
#include "PWM.h"
#include "SPI.h"
#include "LCD_nokia.h"
#include "Delay.h"
#include "Frequency.h"

/*General definitions*/
#define RGB_ON (255u)
#define RGB_OFF (0u)
/*Variable declaration*/
uint8_t string1[]="1) Manual"; /*! String to be printed in the LCD*/
uint8_t string2[]="2) ADC"; /*! String to be printed in the LCD*/
uint8_t string3[]="3) Sequence"; /*! String to be printed in the LCD*/
uint8_t string4[]="4) Frequency"; /*! String to be printed in the LCD*/
uint16_t menuOption;
uint16_t MainButton;
uint8_t MainDataAvailable;
static uint8_t B0; /*port c pin 5*/
static uint8_t B1; /*port c pin 7*/
static uint8_t B2; /*port c pin 0*/
static uint16_t B3; /*port c pin 9*/
static uint16_t B4; /*port c pin 8*/
static uint8_t SW2;

uint32 Menu_get_element(void)
{
	return GPIO_read_port(GPIO_C);
}

uint32 Menu_decode (uint32 reading){
	uint32_t port_value;
		port_value = GPIOC->PDIR;
		/*Value decoded was SW2*/
		if(port_value == SW2_MASK)
		{
			SW2 = SW2_MASK;
			return SW2;
		}
		/*Value decoded was B0*/
		else if(port_value == B0_MASK)
			{
				B0 = B0_MASK;
				return B0;
			}
		/*Value decoded was B1*/
		else if(port_value == B1_MASK)
			{
				B1 = B1_MASK;
				return B1;
			}
		/*Value decoded was B2*/
		else if(port_value == B2_MASK)
			{
				B2 = B2_MASK;
				return B2;
			}
		/*Value decoded was B3*/
		else if(port_value == B3_MASK)
			{
				B3 = B3_MASK;
				return B3;
			}
		/*Value decoded was B4*/
		else if(port_value == B4_MASK )
			{
				B4 = B4_MASK;
				return B4;
			}
		/*None of the above was selected*/
		else
			return 0xFF; /*Change magic number, only for checking*/
}

int main(void) {

    while(1) {
    	/*General initializations*/
    	Button_init();
    	LCD_nokia_init();
		ADC_init();
		PWM_init();
		singleCapture();
    	/*Show initial message*/
    	LCD_screen();
    	LCD_nokia_clear();
    	/*Turn on every color RGB LED*/
    	/*Red*/
    	PWM_channel_value(RGB_ON, RGB_OFF, RGB_OFF );
    	delay(2000);
    	/*Green*/
    	PWM_channel_value(RGB_OFF, RGB_ON, RGB_OFF );
    	delay(2000);
    	/*Blue*/
		PWM_channel_value( RGB_OFF, RGB_OFF, RGB_ON );
		delay(2000);
		/*Print menu*/
		LCD_nokia_goto_xy(10,1);
		LCD_nokia_send_string(string1); /*! It print a string stored in an array*/
		LCD_nokia_goto_xy(20,1);
		LCD_nokia_send_string(string2); /*! It print a string stored in an array*/
		LCD_nokia_goto_xy(30,1);
		LCD_nokia_send_string(string3); /*! It print a string stored in an array*/
		LCD_nokia_goto_xy(40,1);
		LCD_nokia_send_string(string4); /*! It print a string stored in an array*/
    	MainDataAvailable = GPIO_get_flag_c();
    	if(MainDataAvailable == TRUE){
    		MainButton = Menu_get_element(); /*Saves lecture of interruption*/
    		menuOption = Menu_decode(MainButton); /*Decodes interruptin being made*/
    		switch(menuOption){
    		/*Enter to manual module*/
    			case B1_MASK:
    				Manual();
    				break;
    		/*Enter to ADC module*/
    			case B2_MASK:
    				ADC_execute();
    				break;
    		/*Enter to sequence module*/
    			case B3_MASK:
    				SEQ_execute();
    				break;
    		/*Enter to frequence module*/
    			case B4_MASK:
    				break;
    		/*None of the above was selected*/
    			default:
    				break;
    		}/*Switch*/
    	}
    	return 0 ;
    } /*While*/


} /*Main*/
