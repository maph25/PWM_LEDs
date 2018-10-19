/*
 * Botones.c
 *
 *  Created on: 19/10/2018
 *      Author: Fer Muñoz
 */

#include "Botones.h"

//CONFIGURACIÓN DE TODOS LOS BOTONES DEL SISTEMA
void Button_init(void){

	/*estados para los botones*/
	uint8_t statePortA = 0; //SW3
	uint8_t statePortB0 = 0; //C5
	uint8_t statePortB1 = 0; //C7
	uint8_t statePortB2 = 0; //C0
	uint8_t statePortB3 = 0; //C9
	uint8_t statePortB4 = 0; //C8
	uint8_t statePortB5 = 0; //C3
	uint8_t statePortB6 = 0; //C2
	uint8_t statePortC = 0;  //SW2

	/*configuracion del pcr*/
	gpio_pin_control_register_t input_intr_config = GPIO_MUX1 | GPIO_PE | GPIO_PS | INTR_FALLING_EDGE;

	/*configuracion de los pines en el pcr*/
	GPIO_pin_control_register(GPIO_A, BIT4, &input_intr_config); //sw3

	GPIO_pin_control_register(GPIO_C, BIT5, &input_intr_config); //B0
	GPIO_pin_control_register(GPIO_C, BIT7, &input_intr_config); //B1
	GPIO_pin_control_register(GPIO_C, BIT0, &input_intr_config); //B2
	GPIO_pin_control_register(GPIO_C, BIT9, &input_intr_config); //B3
	GPIO_pin_control_register(GPIO_C, BIT8, &input_intr_config); //B4
	GPIO_pin_control_register(GPIO_C, BIT3, &input_intr_config); //B5
	GPIO_pin_control_register(GPIO_C, BIT2, &input_intr_config); //B6

	GPIO_pin_control_register(GPIO_C, BIT6, &input_intr_config); //SW2

	/*CONFIGURACIÓN DE LOS BOTONES COMO ENTRADA*/
	GPIO_data_direction_pin(GPIO_C, GPIO_INPUT, BIT5);
	GPIO_data_direction_pin(GPIO_C, GPIO_INPUT, BIT7);
	GPIO_data_direction_pin(GPIO_C, GPIO_INPUT, BIT0);
	GPIO_data_direction_pin(GPIO_C, GPIO_INPUT, BIT9);
	GPIO_data_direction_pin(GPIO_C, GPIO_INPUT, BIT8);
	GPIO_data_direction_pin(GPIO_C, GPIO_INPUT, BIT3);
	GPIO_data_direction_pin(GPIO_C, GPIO_INPUT, BIT2);

	/*DEFINIMOS PRIORIDAD DE INTERRUPCIÓN*/
	/**Sets the threshold for interrupts, if the interrupt has higher priority constant that the BASEPRI, the interrupt will not be attended*/
	NVIC_setBASEPRI_threshold(PRIORITY_5);

	/**Enables and sets a particular interrupt and its priority*/
	NVIC_enableInterruptAndPriotity(PORTA_IRQ, PRIORITY_3);

	/**Enables and sets a particular interrupt and its priority*/
	NVIC_enableInterruptAndPriotity(PORTC_IRQ, PRIORITY_3);

	/*HABILITACIÓN DE LA INTERRUPCIÓN*/
	EnableInterrupts;

}



/*
void Buttons_set()
{
	if (TRUE == GPIO_get_IRQ_status(GPIO_A)) {
		if (statePortA) {
			//*Sentencia a desactivar*
		} else {
			//*Sentencia a ejecutar*
		}
		statePortA = !statePortA;
		GPIO_clear_IRQ_status(GPIO_A);
	}
	if (TRUE == GPIO_get_IRQ_status(GPIO_C)) {
		if (statePortC) {
			/*Sentencia a desactivar*
		} else {
			/*Sentencia a ejecutar*
		}
		statePortC = !statePortC;
		GPIO_clear_IRQ_status(GPIO_C);
	}
	if (TRUE == GPIO_get_IRQ_statusB0()) {
		if (statePortB0) {
			/*Sentencia a desactivar*
		} else {
			/*Sentencia a ejecutar*
		}
		statePortB0 = !statePortB0;
		GPIO_clear_IRQ_statusB0();
	}
	if (TRUE == GPIO_get_IRQ_statusB1()) {
		if (statePortB1) {
			/*Sentencia a desactivar*
		} else {
			/*Sentencia a ejecutar*
		}
		statePortB1 = !statePortB1;
		GPIO_clear_IRQ_statusB1();
	}
	if (TRUE == GPIO_get_IRQ_statusB2()) {
		if (statePortB2) {
			/*Sentencia a desactivar*
		} else {
			/*Sentencia a ejecutar*
		}
		statePortB2 = !statePortB2;
		GPIO_clear_IRQ_statusB2();
	}
	if (TRUE == GPIO_get_IRQ_statusB3()) {
		if (statePortB3) {
			/*Sentencia a desactivar*
		} else {
			/*Sentencia a ejecutar*
		}
		statePortB3 = !statePortB3;
		GPIO_clear_IRQ_statusB3();
	}
	if (TRUE == GPIO_get_IRQ_statusB4()) {
		if (statePortB4) {
			/*Sentencia a desactivar*
		} else {
			/*Sentencia a ejecutar*
		}
		statePortB4 = !statePortB4;
		GPIO_clear_IRQ_statusB4();
	}
	if (TRUE == GPIO_get_IRQ_statusB5()) {
		if (statePortB5) {
			/*Sentencia a desactivar*
		} else {
			/*Sentencia a ejecutar*
		}
		statePortB5 = !statePortB5;
		GPIO_clear_IRQ_statusB5();
	}
	if (TRUE == GPIO_get_IRQ_statusB6()) {
		if (statePortB6) {
			/*Sentencia a desactivar*
		} else {
			//*Sentencia a ejecutar*
		}
		statePortB6 = !statePortB6;
		GPIO_clear_IRQ_statusB6();
	}
}*/


