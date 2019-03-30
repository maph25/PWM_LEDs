/**
 * @file    RGB_PWM.c
 * @brief   Application entry point.
 */
#include "stdint.h"
#include "NVIC.h"
#include "LCD_nokia.h"
#include "LCD_Print.h"
#include "SPI.h"
#include "Manual.h"
#include "GPIO.h"
#include "MK64F12.h"
#include "PWM.h"


int main(void) {
	/*SPI configuration*/
	const spi_config_t g_spi_config = {
			SPI_DISABLE_FIFO,
			SPI_LOW_POLARITY,
			SPI_LOW_PHASE,
			SPI_MSB,
			SPI_0,
			SPI_MASTER,
			GPIO_MUX2,
			SPI_BAUD_RATE_2,
			SPI_FSIZE_8,
			{GPIO_D, bit_1, bit_2}
	};
	/*Initializations*/
	PWM_init();
	Buttons_init();
	NVIC_priorities();
	SPI_init(&g_spi_config);
//	LCD_nokia_init();

    while(1) {

    }
    return 0 ;
}
