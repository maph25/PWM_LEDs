/*
 * Sequence.h
 *
 *  Created on: Mar 29, 2019
 *      Author: Andrea Perez Huizar, ie698276@iteso.mx
 */

#ifndef SEQUENCE_H_
#define SEQUENCE_H_

#include "PWM.h"

/*RGB off value*/
#define SEQUENCE_START_VALUE 0x00
/*RGB blue values*/
#define SEQUENCE_BLUE_R 0x00
#define SEQUENCE_BLUE_G 0x00
#define SEQUENCE_BLUE_B 0xFF
/*RGB red values*/
#define SEQUENCE_RED_R 0xFF
#define SEQUENCE_RED_G 0x00
#define SEQUENCE_RED_B 0x00
/*RGB green values*/
#define SEQUENCE_GREEN_R 0x00
#define SEQUENCE_GREEN_G 0xFF
#define SEQUENCE_GREEN_B 0x00
/*RGB yellow values*/
#define SEQUENCE_YELLOW_R 0xFF
#define SEQUENCE_YELLOW_G 0xFF
#define SEQUENCE_YELLOW_B 0x00
/*RGB purple values*/
#define SEQUENCE_PURPLE_R 0x96
#define SEQUENCE_PURPLE_G 0x00
#define SEQUENCE_PURPLE_B 0xFF
/*RGB white values*/
#define SEQUENCE_WHITE_R 0xFF
#define SEQUENCE_WHITE_G 0xFF
#define SEQUENCE_WHITE_B 0xFF

/*RGB color configuration functions*/
void Sequence_RGB_off(void);
void Sequence_RGB_blue(void);
void Sequence_RGB_red(void);
void Sequence_RGB_green(void);
void Sequence_RGB_yellow(void);
void Sequence_RGB_purple(void);
void Sequence_RGB_white(void);


#endif /* SEQUENCE_H_ */
