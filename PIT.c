/**
 * @file    PIT.c
 * @brief   Application entry point.
 *
 * Author: Andrea Perez Huizar ie698276@iteso.mx & Alvaro A. Rocha Robles, ie703585@iteso.mx
 * 28/02/2019. Zapopan, Jal.
 */

#include "PIT.h"
#include "bits.h"
#include "MK64F12.h"

static void (*pit_ch1_callback)(void) = 0;
static void (*pit_ch2_callback)(uint8_t) = ZERO;

static uint8_t pit0_intr_flag = FALSE;
static uint8_t pit1_intr_flag = FALSE;
static uint8_t pit_led_control = ONE;

static struct
{
	uint8_t channel_0 : 1;
	uint8_t channel_1 : 1;
	uint8_t channel_2 : 1;
}pit_intr_flag_t;

void PIT1_callback_update(void (*handler)(void))
{
	pit_ch1_callback = handler;
}

void PIT2_callback_update(void (*handler)(uint8_t))
{
	pit_ch2_callback = handler;
	pit_led_control = ONE;
}

void PIT0_IRQHandler()
{
	pit0_intr_flag = PIT->CHANNEL[0].TFLG;
	PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;

	PIT->CHANNEL[0].TCTRL;	//read control register for clear PIT flag, this is silicon bug
	PIT->CHANNEL[0].TCTRL &= ~(PIT_TCTRL_TIE_MASK);
	PIT->CHANNEL[0].TCTRL &= ~(PIT_TCTRL_TEN_MASK);
}

void PIT1_IRQHandler()
{
	volatile uint32_t dummyRead;
	PIT->CHANNEL[1].TFLG |= PIT_TFLG_TIF_MASK;
	dummyRead = PIT->CHANNEL[1].TCTRL;	//read control register for clear PIT flag, this is silicon bug
	pit1_intr_flag = TRUE;
	pit_ch1_callback(); //motor state change
}

void PIT2_IRQHandler()
{
	volatile uint32_t dummyRead;
	PIT->CHANNEL[2].TFLG |= PIT_TFLG_TIF_MASK;
	dummyRead = PIT->CHANNEL[2].TCTRL;	//read control register for clear PIT flag, this is silicon bug
	pit_intr_flag_t.channel_2 = TRUE;
	if(pit_led_control)
	{
		pit_led_control = ZERO;
	}
	else
	{
		pit_led_control = ONE;
	}
	pit_ch2_callback(pit_led_control); //LED control
}

void PIT_delay(PIT_timer_t pit_timer, PIT_float_t system_clock , PIT_float_t delay)
{
	uint32_t LDVAL = 0;
	PIT_float_t clock_period = 0.0F;
	system_clock = system_clock /2;
	clock_period = (1/system_clock);
	LDVAL = (uint32_t)(delay / clock_period);
	LDVAL = LDVAL - 1;

	switch(pit_timer)
	{
	case PIT_0:
		PIT->CHANNEL[0].LDVAL = LDVAL;
		PIT_enable_interrupt(PIT_0);
		break;
	case PIT_1:
		PIT->CHANNEL[1].LDVAL = LDVAL;
		PIT_enable_interrupt(PIT_1);
		break;
	case PIT_2:
		PIT->CHANNEL[2].LDVAL = LDVAL;
		PIT_enable_interrupt(PIT_2);
		break;
	default:
		PIT->CHANNEL[0].LDVAL = LDVAL;
		PIT_enable_interrupt(PIT_0);
		break;
	}
}

void PIT_stop(PIT_timer_t pit)
{
	switch(pit)
	{
		case PIT_0:
		{
			PIT->CHANNEL[0].TCTRL &= !PIT_TCTRL_TEN_MASK;//disables timer0
		}
		break;

		case PIT_1:
		{
			PIT->CHANNEL[1].TCTRL &= !PIT_TCTRL_TEN_MASK;//disables timer1
		}
		break;

		case PIT_2:
		{
			PIT->CHANNEL[2].TCTRL &= !PIT_TCTRL_TEN_MASK;//disables timer2
			pit_led_control = ONE;
		}
		break;

		default:
			break;
	}
}

void PIT_enable(void)
{
	PIT->MCR  |= PIT_MCR_FRZ_MASK;
	PIT->MCR &= ~PIT_MCR_MDIS_MASK; /* Enable PIT*/
}

void PIT_enable_interrupt(PIT_timer_t pit)
{
	switch(pit)
	{
		case PIT_0:
		{
			PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK;//enables PIT timer interrupt
			PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK;//enables timer0
		}
		break;
		case PIT_1:
		{
			PIT->CHANNEL[1].TCTRL |= PIT_TCTRL_TIE_MASK;//enables PIT timer interrupt
			PIT->CHANNEL[1].TCTRL |= PIT_TCTRL_TEN_MASK;//enables timer1
		}
		break;
		case PIT_2:
		{
			PIT->CHANNEL[2].TCTRL |= PIT_TCTRL_TIE_MASK;//enables PIT timer interrupt
			PIT->CHANNEL[2].TCTRL |= PIT_TCTRL_TEN_MASK;//enables timer1
		}
		break;
		default:
			break;
	}
}

void PIT_disable_interrupt(PIT_timer_t pit)
{
	PIT->CHANNEL[0].TCTRL |= !PIT_TCTRL_TIE_MASK;//enables PIT timer interrupt
	switch(pit)
	{
		case PIT_0:
		{
			PIT->CHANNEL[0].TCTRL |= !PIT_TCTRL_TIE_MASK;//disables PIT timer interrupt
		}
		break;

		case PIT_1:
		{
			PIT->CHANNEL[1].TCTRL |= !PIT_TCTRL_TIE_MASK;//disables PIT timer interrupt
		}
		break;

		case PIT_2:
		{
			PIT->CHANNEL[2].TCTRL |= !PIT_TCTRL_TIE_MASK;//disables PIT timer interrupt
		}
		break;

		default:
			break;
	}
}

void PIT_clock_gating(void)
{
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
	PIT->MCR = 0;
}

uint8_t PIT_get_interrupt_flag_status(PIT_timer_t pit)
{
	uint8_t pit_intr_flag;
	switch(pit)
	{
		case PIT_0:
			pit_intr_flag = pit0_intr_flag;
			break;
		case PIT_1:
			pit_intr_flag = pit1_intr_flag;
			break;
		default:
			break;
	}
	return pit_intr_flag;
}

void PIT_clear_interrupt_flag(PIT_timer_t pit)
{
	switch(pit)
	{
		case PIT_0:
			pit0_intr_flag = FALSE;
			break;
		case PIT_1:
			pit1_intr_flag = FALSE;
			break;
		default:
			break;
	}
}
