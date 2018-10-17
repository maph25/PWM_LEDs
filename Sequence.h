/*
 * Sequence.h
 *
 *  Created on: Oct 14, 2018
 *      Author: Andrea Perez
 */

#ifndef SEQUENCE_H_
#define SEQUENCE_H_

#include "DataTypeDefinitions.h"

#define SEQ_RED 0X80 /*Value for Red input B1*/
#define SEQ_GREEN 0x01 /*Value for Green input B2*/
#define SEQ_BLUE 0x100 /*Value for Blue input B3*/
#define B_MASK 0x281 /*Mask for reading buttons B1, B2, B3*/
#define MAX_SEQ (10u)

uint32 SEQ_decode (uint32 reading);
uint32 SEQ_get_element(void);
void SEQ_save_seq(void);


#endif /* SEQUENCE_H_ */
