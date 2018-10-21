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
#define SEQ_MAX (10u)
#define SEQ_NINE (9u)
#define SEQ_EIGHT (8u)
#define SEQ_SEVEN (7u)
#define SEQ_SIX (6u)
#define SEQ_FIVE (5u)
#define SEQ_FOUR (4u)
#define SEQ_THREE (3u)
#define SEQ_TWO (2u)
#define SEQ_INIT (1u)

uint32 SEQ_decode (uint32 reading);
uint32 SEQ_get_element(void);
void SEQ_save_seq(void);


#endif /* SEQUENCE_H_ */
