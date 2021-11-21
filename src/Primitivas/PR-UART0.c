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


//**************************************************************************
//*	Proposito: Recibe mensajes de la UART0
//*	Parametros: void
//*	Retorna: void.
//**************************************************************************

void Mensajes (void)
{
   	volatile int dato;
   	static uint8_t salida, cont;

   	dato = PopRx( );

	if( dato >= 0 )
	{
		switch ( (uint8_t) dato )
		{
			case '#':
				salida = cont = 0;
				break;
			case '$':
				BufferSalidas = salida;
				break;
			default:
					salida |= ( dato - '0') << cont;
					cont++;
					if (cont==8)
						break;
		}
	}
}




//**************************************************************************
//*	Proposito: Envia mensajes a la UART0
//*	Parametros: Un array
//*	Retorna: void.
//**************************************************************************

void Transmitir (char *p )
{
	volatile int i;

	for( i = 0 ; p[i] ; i++ ){
		PushTx( p[i] );
	}
}


