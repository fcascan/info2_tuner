/*
 * IRQhandler.c
 *
 *  Created on: 28/11/2014
 *      Author: Usuario
 */

#include "EA_BaseBoard.h"


void SysTick_Handler(void)
{
//	extern uint32_t Ticks;
	extern uint8_t Estado_actual;

	if (Estado_actual == METRONOME){
		Metronomo ();
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void ADC_IRQHandler(void)
{
	extern uint16_t BufferADC[];
	extern uint8_t BufferADCLleno;

	static uint16_t indice_BufferADC=0;

	volatile uint16_t resultado = 0;
	volatile uint32_t lectura=0, lecturaaux=0;

	lectura = AD0DR4;									// Leo el valor convertido en el ADC0.4 desde el Data Register (VER ERRATA DATASHEET)
	lecturaaux = AD0GDR;								// Leo el Global Data Register porque sino no se limpian los flags del ADC (REVISAR!)

	resultado = ((lectura>>RESULT) & (0xFFF));			// Leo el valor convertido por el ADC en el registro Global Status Register
														// al leer se limpian solos los flags del ADC

	if (BufferADCLleno==0){								// Si el Buffer aun no se llena
		BufferADC[indice_BufferADC] = resultado;		// Guardo el valor leido en el Buffer

		indice_BufferADC++;								// Incremento el indice del Buffer

		if (indice_BufferADC == 1024){					// Si el indice llego a 1024 se reinicia a 0 porque solo me interesa tomar 1024 muestras
			indice_BufferADC=0;							// Reseteo el indice
			BufferADCLleno=1;							// Con este flag aviso que ya se lleno el Buffer
		}
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void UART0_IRQHandler (void)
{
	extern volatile char TxStart;								//!< flag de fin de TX

	volatile uint8_t iir,lsr;
	volatile uint8_t IntEnCurso , IntPendiente ;
	volatile int dato ;

	do
	{  //IIR es reset por HW, una vez que lo lei se resetea.

		iir = U0IIR;

		IntPendiente = iir & 0x01;
		IntEnCurso = ( iir >> 1 ) & 0x07;

		switch( IntEnCurso )
		{
			case IIR_RLS:
				lsr = U0LSR;						// con la lectura se borra la int
				if ( lsr & ( LSR_OE | LSR_PE | LSR_FE | LSR_RXFE|LSR_BI ) )
				{
					dato = U0RBR;					// Leo para borrar el buffer
					return;
				}
				break;
			case IIR_RDA:	/* Receive Data Available */
				U0LSR &=~ LSR_RDR;					// Borrar flag de Rx
				dato = U0RBR;						// Lectura del dato
				PushRx( (uint8_t) dato );			// Guardo el dato
				break;

			case IIR_THRE:	/* THRE, transmit holding register empty */
				U0LSR &= ~LSR_THRE;						// Borrar flag de Tx
				dato = PopTx( );						// Tomo el dato a Transmitir
				if ( dato >= 0 )
					U0THR = (uint8_t) dato;	// si hay dato en la cola lo Transmito
				else
					TxStart = 0;
				break;
		}
	}

	while( ! ( IntPendiente & 0x01 ) ); /* me fijo si cuando entr‚ a la ISR habia otra
						     			int. pendiente de atenci¢n: b0=1 (ocurre unicamente si dentro del mismo
										espacio temporal lleguan dos interrupciones a la vez) */
}

