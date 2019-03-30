/**
	\file
	\brief
		This is the source file for the SPI device driver for Kinetis K64.
		It contains all the implementation for configuration functions and runtime functions.
	\author Andrea Perez Huizar, ie698276@iteso.mx & Alvaro A. Rocha Robles, ie703585@iteso.mx
	\date	19/03/2019
*/

#include "SPI.h"

static void SPI_enable(spi_channel_t channel)
{
	switch(channel)
		{
		case SPI_0:
			SPI0->MCR &= ~SPI_MCR_MDIS_MASK;
			break;
		default:
			SPI1->MCR &= ~SPI_MCR_MDIS_MASK;
		}

}

static void SPI_clk(spi_channel_t channel)
{
	switch (channel)
	{
	case SPI_0:
		SIM->SCGC6 |= SPI0_CLOCK_GATING;
		break;
	default:
		SIM->SCGC6 |= SPI1_CLOCK_GATING;
		break;
	}
}

static void SPI_set_master(spi_channel_t channel, spi_master_t masterOrSlave)
{
	switch(channel)
	{
	case SPI_0:
		if(SPI_MASTER)
			SPI0->MCR |= SPI_MCR_MSTR_MASK;
		else
			SPI0->MCR &= ~SPI_MCR_MSTR_MASK;
		break;
	default:
		if(SPI_MASTER)
			SPI1->MCR |= SPI_MCR_MSTR_MASK;
		else
			SPI1->MCR &= ~SPI_MCR_MSTR_MASK;
		break;
	}

}

static void SPI_fifo(spi_channel_t channel, spi_enable_fifo_t enableOrDisable)
{
	switch(channel)
		{
		case SPI_0:
			if(enableOrDisable)
				SPI0->MCR |= SPI_MCR_DIS_RXF_MASK | SPI_MCR_DIS_TXF_MASK |SPI_MCR_CLR_RXF_MASK | SPI_MCR_CLR_TXF_MASK;
			else
				SPI0->MCR &= ~(SPI_MCR_DIS_RXF_MASK | SPI_MCR_DIS_TXF_MASK);
			break;
		default:
			if(enableOrDisable)
				SPI1->MCR |= SPI_MCR_DIS_RXF_MASK | SPI_MCR_DIS_TXF_MASK | SPI_MCR_CLR_RXF_MASK | SPI_MCR_CLR_TXF_MASK;
			else
				SPI1->MCR &= ~(SPI_MCR_DIS_RXF_MASK | SPI_MCR_DIS_TXF_MASK);
			break;
		}
}

static void SPI_clock_polarity(spi_channel_t channel, spi_polarity_t cpol)
{
	switch (channel)
	{
	case SPI_0:
		if(cpol)
			SPI0->CTAR[0] |= SPI_CTAR_CPOL_MASK;
		else
			SPI0->CTAR[0] &= ~SPI_CTAR_CPOL_MASK;
		break;
	default:
		if(cpol)
			SPI1->CTAR[1] |= SPI_CTAR_CPOL_MASK;
		else
			SPI1->CTAR[1] &= ~SPI_CTAR_CPOL_MASK;
		break;
	}
}

static void SPI_frame_size(spi_channel_t channel, uint32_t frameSize)
{
	switch (channel)
		{
		case SPI_0:
			{
			SPI0->CTAR[0] &= ~SPI_CTAR_FMSZ_MASK;
			SPI0->CTAR[0] |= frameSize;
			}
			break;
		default:
			{
		    SPI1->CTAR[0] &= ~SPI_CTAR_FMSZ_MASK;
		    SPI1->CTAR[0] |= frameSize;
			}
			break;
		}
}

static void SPI_clock_phase(spi_channel_t channel, spi_phase_t cpha)
{
	switch (channel)
	{
	case SPI_0:
		if(cpha)
			SPI0->CTAR[0] |= SPI_CTAR_CPHA_MASK;
		else
			SPI0->CTAR[0] &= ~SPI_CTAR_CPHA_MASK;
		break;
		if(cpha)
			SPI1->CTAR[1] |= SPI_CTAR_CPHA_MASK;
		else
			SPI1->CTAR[1] &= ~SPI_CTAR_CPHA_MASK;
	default:
		break;
	}
}

static void SPI_baud_rate(spi_channel_t channel, uint32_t baudRate)
{
	switch (channel)
		{
		case SPI_0:
			SPI0->CTAR[0] |= baudRate;
			break;
		default:
			SPI0->CTAR[1] |= baudRate;
			break;
		}
}

static void SPI_msb_first(spi_channel_t channel, spi_lsb_or_msb_t msb)
{
	switch (channel)
		{
		case SPI_0:
			if(msb)
				SPI0->CTAR[0] |= SPI_CTAR_LSBFE_MASK;
			else
				SPI0->CTAR[0] &= ~SPI_CTAR_LSBFE_MASK;
			break;
		default:
			if(msb)
				SPI1->CTAR[1] |= SPI_CTAR_LSBFE_MASK;
			else
				SPI1->CTAR[1] &= ~SPI_CTAR_LSBFE_MASK;
			break;
		}
}

void SPI_start_tranference(spi_channel_t channel)
{
	switch (channel)
		{
		case SPI_0:
			SPI0->MCR &= ~SPI_MCR_HALT_MASK;
			break;

		default:
			SPI1->MCR &= ~SPI_MCR_HALT_MASK;
			break;
		}
}

void SPI_stop_tranference(spi_channel_t channel)
{
	switch (channel)
		{
		case SPI_0:
			SPI0->MCR |= SPI_MCR_HALT_MASK;
			break;
		default:
			SPI1->MCR |= SPI_MCR_HALT_MASK;
			break;
		}
}

void SPI_send_one_byte(uint8_t Data)
{
	GPIO_clear_pin(GPIO_D, bit_4);
	SPI0->PUSHR = (Data);
	/*Blocking code, this kind of code should be avoided. In this case is used to simplify the lab*/
	while(FALSE == (SPI0->SR & SPI_SR_TCF_MASK));
		SPI0->SR |= SPI_SR_TCF_MASK;
		GPIO_set_pin(GPIO_D, bit_4);
}

void SPI_init(const spi_config_t* spi_config)
{
	gpio_pin_control_register_t enable_bit = GPIO_MUX1;

	SPI_clk(spi_config->spi_channel);
	GPIO_clock_gating(spi_config->spi_gpio_port.gpio_port_name);
	GPIO_pin_control_register(spi_config->spi_gpio_port.gpio_port_name, spi_config->spi_gpio_port.spi_clk, &(spi_config->pin_config));
	GPIO_pin_control_register(spi_config->spi_gpio_port.gpio_port_name ,spi_config->spi_gpio_port.spi_sout ,&(spi_config->pin_config));
	SPI_set_master(spi_config->spi_channel,spi_config->spi_master);
	SPI_fifo(spi_config->spi_channel, spi_config->spi_enable_fifo);
	SPI_enable(spi_config->spi_channel);
	SPI_clock_polarity(spi_config->spi_channel, spi_config->spi_polarity);
	SPI_frame_size(spi_config->spi_channel,spi_config->spi_frame_size);
	SPI_clock_phase(spi_config->spi_channel, spi_config->spi_phase);
	SPI_baud_rate(spi_config->spi_channel, spi_config->spi_baudrate);
	SPI_msb_first(spi_config->spi_channel, spi_config->spi_lsb_or_msb);

	GPIO_pin_control_register(GPIO_D, bit_4, &enable_bit);
	GPIO_set_pin(GPIO_D, bit_4);
	GPIO_data_direction_pin(GPIO_D, GPIO_OUTPUT, bit_4);
}
