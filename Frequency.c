/*
 * Freq.c
 *
 *  Created on: 29/10/2018
 *      Author: Fer Muñoz
 */
#include "DataTypeDefinitions.h"
#include "Frequency.h"
#include "MK64F12.h"
#include "GPIO.h"

static FTM_Type FTM_t;

float tempPrev = 0;
float  temp = 0;
float diff = 0;
float var0 = 0;
uint8_t DataC;
uint8_t DataA;

void FTM0_IRQ(void) {

		if (FTM_t.STATUS & 0x01) {
			tempPrev = temp;
			temp = FTM0->CONTROLS[0].CnV; //CONTROLS[0].CnV; //read FTM0 counter register
			diff = temp - tempPrev;
			FTM_t.STATUS &= 0xFE;
			//read Hall sensor logic
			//The FTM0_CH0 channel is multiplexed with GPIOC1, read GPIOC1 logic
			var0 = GPIOC->PDIR;
			GPIOC->PTOR = 0x80;
			asm("nop"); //set a break point here
		}

}

void singleCapture(void)
{
//enable FTM0 clock
SIM -> SCGC6 |= 0x03000000; //enable FTM0 and FTM0 module clock
SIM -> SCGC5 = SIM -> SCGC5|0x3E00; //enable port A/B/C/D/E clock
FTM0 -> SC = 0x00;
FTM0 -> CONTROLS[0].CnSC |= 0x04; //Capture on Rising Edge Only
FTM0 -> COMBINE = 0x00; //clear
//enable capture interrupt
FTM0 -> CONTROLS[0].CnSC |= 0x40; //enable CH0 interrupt
FTM0 -> SC |= 0x08;
//in ISR of capture interrupt, read the FTM_c0V register to get the capture value
}

void Freq()
{
	DataC = GPIO_get_flag_c();
	DataA = GPIO_get_flag_a();
	if(DataA == TRUE){
		singleCapture();
	}
	if(DataC == TRUE){
		GPIO_clear_pin(GPIO_C , SW2_MASK);
	}
}
