/*
 * PR-ADC.c
 *
 *  Created on: 02/12/2014
 *      Author: Usuario
 */

#include "EA_BaseBoard.h"


void ADC_CLKDIV_1 (void)
{
	AD0CR &= ~(0xFF<<CLKDIV);
	AD0CR |= (0xA8<<CLKDIV);
}


void ADC_CLKDIV_2 (void)
{
	AD0CR &= ~(0xFF<<CLKDIV);
	AD0CR |= (0x60<<CLKDIV);
}


void ADC_CLKDIV_3 (void)
{
	AD0CR &= ~(0xFF<<CLKDIV);
	AD0CR |= (0x4D<<CLKDIV);
}

