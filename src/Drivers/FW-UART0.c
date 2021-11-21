/*
 * PR-UART0.c
 *
 *  Created on: 28/11/2014
 *      Author: Usuario
 */

#include "EA_BaseBoard.h"

extern volatile unsigned char BufferTx[TOPE_BUFFER_TX];		//!< Buffer de Transmision
extern volatile unsigned char BufferRx[TOPE_BUFFER_RX];		//!< Buffer de Recepcion
extern volatile unsigned char IndiceTxIn,IndiceTxOut;		//!< Indices de Transmision
extern volatile unsigned char IndiceRxIn,IndiceRxOut;		//!< Indices de Recepcion
extern volatile char TxStart;								//!< flag de fin de TX
extern volatile uint8_t	BufferSalidas;

// ***********************


void PushTx (uint8_t dato)
{

	if ( TxStart == 0 )
	{
		TxStart = 1;
		U0THR = dato;
		return;
	}

	BufferTx[IndiceTxIn] = dato;

	IndiceTxIn ++;
	IndiceTxIn %= TOPE_BUFFER_TX;

}


int PopTx ( void )
{
	int dato = -1;

	if ( IndiceTxIn != IndiceTxOut )
	{
		dato = (uint8_t) BufferTx[IndiceTxOut];
		IndiceTxOut ++;
		IndiceTxOut %= TOPE_BUFFER_TX;
	}
	return dato;
}


void PushRx (uint8_t dato)
{
	BufferRx[IndiceRxIn] = dato;
	IndiceRxIn ++;
	IndiceRxIn %= TOPE_BUFFER_RX;
}


int PopRx ( void )
{

	volatile int dato = -1;

	if ( IndiceRxIn != IndiceRxOut )
	{
		dato = (uint8_t) BufferRx[IndiceRxOut];
		IndiceRxOut ++;
		IndiceRxOut %= TOPE_BUFFER_RX;
	}
	return dato;
}
