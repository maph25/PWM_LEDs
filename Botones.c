/*
 * Botones.c
 *
 *  Created on: 19/10/2018
 *      Author: Fer Muñoz
 */

#include "Botones.h"

//CONFIGURACIÓN DE TODOS LOS BOTONES DEL SISTEMA
void Button_init(void){
	/*configuracion del pcr*/
	gpio_pin_control_register_t input_intr_config = GPIO_MUX1 | GPIO_PE | GPIO_PS | INTR_FALLING_EDGE;

	/*Clock gating*/
	GPIO_clock_gating(GPIO_C);
	GPIO_clock_gating(GPIO_A);
	GPIO_clock_gating(GPIO_D);

	/*configuracion de los pines en el pcr*/
	GPIO_pin_control_register(GPIO_A, BIT4, &input_intr_config); //SW3

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
	GPIO_data_direction_pin(GPIO_C, GPIO_INPUT, BIT6);
	GPIO_data_direction_pin(GPIO_A, GPIO_INPUT, BIT4);

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

