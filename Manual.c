/*
 * Manual.c
 *
 *  Created on: 23/10/2018
 *      Author: Fer Muñoz
 */



/**
	\file
	\brief
		This project shows how to configure FlexTimer in PWM mode.
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	7/09/2014
	    Add configuration structures.
 */


#include "MK64F12.h" /* include peripheral declarations */
#include "GPIO.h"
#include "Manual.h"
#include "NVIC.h"
#include "PWM.h"
#include "Delay.h"

uint8_t Button;
uint8_t member;
uint8_t StateButton;
uint8_t Data;
uint32_t statusFlagManual;
static uint8_t B0; /*port c pin 5*/
static uint8_t B1; /*port c pin 7*/
static uint8_t B2; /*port c pin 0*/
static uint8_t B3; /*port c pin 9*/
static uint8_t B4; /*port c pin 8*/
static uint8_t B5; /*port c pin 3*/
static uint8_t B6; /*port c pin 2*/
static uint8_t SW2;

/*inicialización de los botones en el manual*/
uint32_t Manual_get_element(void)
{
	return GPIO_read_port(GPIO_C);
}

/*recibe los botones en el manual*/
uint32_t Manual_decode (uint32_t reading){
	uint32_t port_value;
		port_value = GPIOC->PDIR;

		if(port_value == SW2_MASK)
		{
			SW2 = TRUE;
			return SW2;
		}
		else if(port_value == B0_MASK )
			{
				B0 = TRUE;
				return B0;
			}
		else if(port_value == B1_MASK )
			{
				B1 = TRUE;
				return B1;
			}
		else if(port_value == B2_MASK )
			{
				B2 = TRUE;
				return B2;
			}
		else if(port_value == B3_MASK )
			{
				B3 = TRUE;
				return B3;
			}
		else if(port_value == B4_MASK )
			{
				B4 = TRUE;
				return B4;
			}
		else if(port_value == B5_MASK )
			{
				B5 = TRUE;
				return B5;
			}
		else if(port_value == B6_MASK )
			{
				B6 = TRUE;
				return B6;
			}
		else
			return 0xFF; /*Change magic number, only for checking*/
}



void Manual_comp_butt(void){
	LCD_nokia_goto_xy(25,2);
	Data = GPIO_get_flag_c();
	StateButton = ONE;

	switch(StateButton)
	{
		case B0_MASK:
		{
			if(DataAvailable == TRUE)
			{
				member = Manual_get_element();
				Button = Manual_decode(member);

			}
		}
		case B1_MASK:
		{
			if(DataAvailable == TRUE)
			{
				member = Manual_get_element();
				Button = Manual_decode(member);
			}
		}
		case B2_MASK:
		{
			if(DataAvailable == TRUE)
			{
				member = Manual_get_element();
				Button = Manual_decode(member);
			}
		}
		case B3_MASK:
		{
			if(DataAvailable == TRUE)
			{
				member = Manual_get_element();
				Button = Manual_decode(member);
			}
		}
		case B4_MASK:
		{
			if(DataAvailable == TRUE)
			{
				member = Manual_get_element();
				Button = Manual_decode(member);
			}
		}
		case B5_MASK:
		{
			if(DataAvailable == TRUE)
			{
				member = Manual_get_element();
				Button = Manual_decode(member);
			}
		}
		case B6_MASK:
		{
			if(DataAvailable == TRUE)
			{
				member = Manual_get_element();
				Button = Manual_decode(member);
			}
		}
	}

}







int Manual(void)
{
	sint16 dutyCycle=0;
	uint8 inputValueA=0,inputPortC = 0;
	GPIO_pinControlRegisterType	pinControlRegisterPORTA = GPIO_MUX1|GPIO_PE|GPIO_PS;
	GPIO_pinControlRegisterType	pinControlRegisterPORTC6 = GPIO_MUX1|GPIO_PE|GPIO_PS;
	/**Clock gating for port A and C*/
    SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTA|GPIO_CLOCK_GATING_PORTC;
   	PORTC->PCR[1]   = PORT_PCR_MUX(0x4);
	/**Pin control register configuration for GPIO*/
	PORTA->PCR[BIT4] = pinControlRegisterPORTA;
	PORTC->PCR[BIT6] = pinControlRegisterPORTC6;
	/**Pin 4 and pin 6 of port A and C, respectively as inputs*/
	GPIOA->PDDR &= ~(BIT4);
	GPIOC->PDDR &= ~(BIT6);
	/**Configuration function for FlexTimer*/
	PWM_init();

	for(;;) {
		/**Reading the input values for port A and C*/
		inputPortC = GPIOC->PDIR;
		inputPortC &=(0x40);
		inputPortC = inputPortC >> 6;
		inputValueA = GPIOA->PDIR;
		inputValueA &=(0x10);
		inputValueA = inputValueA >> 4;

		if(inputValueA ==0)
		{

			FlexTimer_updateCHValue(dutyCycle);
			delay(20000);
		}
		if(inputPortC==0)
		{
			dutyCycle = dutyCycle-10;
			FlexTimer_updateCHValue(dutyCycle);
			delay(20000);
		}

	}

	return 0;
}
