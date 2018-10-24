/*
 * Manual.h
 *
 *  Created on: 23/10/2018
 *      Author: Fer Muñoz
 */

#ifndef MANUAL_H_
#define MANUAL_H_


void delay(uint16_t delay);

int Manual(void);

uint32_t Manual_get_element(void);

uint32_t Manual_decode (uint32_t reading);

void Manual_comp_butt(void);

#endif /* MANUAL_H_ */
