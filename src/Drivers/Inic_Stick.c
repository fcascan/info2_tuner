/*
 * Inic_Stick.c
 *
 *  Created on: 30/09/2014
 *      Author: Usuario
 */

#include "EA_BaseBoard.h"

void Inic_Stick (void)
{
	InitPLL ();
	inic_Systick ();
	inic_ADC ();
	inic_UART0 (BAUDRATE_9600);
}


void inic_Systick (void)
{
	//STRELOAD = ( STCALIB / 4) - 1;	// Recarga cada 2.5 ms
	STRELOAD = ( STCALIB / 2) - 1;		// Recarga cada 5 ms (OK!)
	//STRELOAD= 0xF423F;		// Recarga cada 10ms, fue calculada de fabrica (esta en hoja de datos)
	STCURR = 0;				// Cargando con cero limpio y provoco el disparo de una interrupcion
	STCTRL |= ( (1<<ENABLE) | (1<<TICKINT) | (1<<CLKSOURCE) );	// Habilito el conteo, la interrupcion, y utilizamos PCLK=CCLK (100Mhz)
}


void inic_UART0 (int baudrate)
{
	volatile int pclk,Fdiv;

		// Enciendo la UART0 (On por default)
		PCONP |=  (1<<PCUART0);

		// Turn on UART0 peripheral clock
		PCLKSEL0 &= ~(0x03 << PCLK_UART0);		// Borro
		PCLKSEL0 |=  (CCLK_4 << PCLK_UART0);	// PCLK = CCLK/4

		// Seleccion de los pines como Tx y Rx de la UART0
		SetPINSEL( PORT0,2, FUNCION_1 );	//TXD0
		SetPINSEL( PORT0,3, FUNCION_1 );	//RXD0

		U0LCR = (1<<DLAB);	// DLAB=1

		// Sin divisor Fraccional
		pclk = SYSTEMCORECLOCK / 4;
		Fdiv = ( pclk / 16 ) / baudrate ;	// FR = 1
	    U0DLM = Fdiv / 256;
	    U0DLL = Fdiv % 256;					// BR medida = 9642 con un Er = 0.44% - MUY BUENO !!!

	    U0LCR = ( (0x03<<Word_Length_sel) | (0<<Stop_Bit_sel) | (0<<Parity_en) | (0<<Break_Control) | (0<<DLAB) );// 8 bits, no Parity, 1 Stop bit, DLAB = 0
	    U0FCR = 0x00; 						// FIFO disabled

	    U0IER = IER_RBR | IER_THRE ;		// Habilito interrupciones UART0
	    ISER0 |= (1<<ISE_UART0);			// Habilito interrupcion de la UART0 en el Vector de interrupciones
}


void inic_ADC (void)
{
	//Pongo los otros canales como salidas GPIO con resistencias pull-down para reducir el ruido en el canal ADC0.4

	SetPINSEL (PORT0,23, FUNCION_GPIO);				// ADC0.0
	SetDIR(PORT0,23, SALIDA);
	SetPINMODE(PORT0,23, MODE_PULL_DOWN);

	SetPINSEL (PORT0,24, FUNCION_GPIO);				// ADC0.1
	SetDIR(PORT0,24, SALIDA);
	SetPINMODE(PORT0,24, MODE_PULL_DOWN);

	SetPINSEL (PORT0,25, FUNCION_GPIO);				// ADC0.2
	SetDIR(PORT0,25, SALIDA);
	SetPINMODE(PORT0,25, MODE_PULL_DOWN);

	SetPINSEL (PORT0,26, FUNCION_GPIO);				// ADC0.3
	SetDIR(PORT0,26, SALIDA);
	SetPINMODE(PORT0,26, MODE_PULL_DOWN);

	SetPINSEL (PORT1,31, FUNCION_GPIO);				// ADC0.5
	SetDIR(PORT1,31, SALIDA);
	SetPINMODE(PORT1,31, MODE_PULL_DOWN);

	SetPINSEL (PORT0,3, FUNCION_GPIO);				// ADC0.6
	SetDIR(PORT0,3, SALIDA);
	SetPINMODE(PORT0,3, MODE_PULL_DOWN);

	SetPINSEL (PORT0,2, FUNCION_GPIO);				// ADC0.7
	SetDIR(PORT0,2, SALIDA);
	SetPINMODE(PORT0,2, MODE_PULL_DOWN);


	//Ahora configuro el ADC0.4

	PCONP |= 1<<PCADC;						// Activo la alimentacion del dispositivo en el registro PCONP
											// (Es necesario hacerlo primero segun se exige en la hoja de datos)

	PCLKSEL0 &= ~(0x03<<PCLK_ADC);			// Mascara para limpiar el valor anterior
	PCLKSEL0 |= (CCLK_8<<PCLK_ADC);			// Selecciono el clock del ADC como 25MHz (PCLK=CCLK)

//	DIVISOR DEL PCLK				// Mientras mas alto este valor, mas lento toma las muestras y el resultado de la fft es mas preciso
//	AD0CR |= (0xFF<<CLKDIV);		// ZARPADO EN LENTO
//	AD0CR |= (0xE8<<CLKDIV);		// ULTRA LENTO
//	AD0CR |= (0xD8<<CLKDIV);		// MUY LENTO
//	AD0CR |= (0xB8<<CLKDIV);		// ?
	AD0CR |= (0xA8<<CLKDIV);		// Sobresaliente! (con BINRANGE=0.5689035) Presicion=1

//	AD0CR |= (0x84<<CLKDIV);		// OK!
//	AD0CR |= (0x60<<CLKDIV);		// OK!
//	AD0CR |= (0x48<<CLKDIV);		// OK!


	SetPINSEL (PORT1,30, FUNCION_3);		// Configuro el P1,30 como funcion de canal 4 del ADC (ADC0.4)
	SetDIR (PORT1,30, ENTRADA);				// Configuro el P1,30 como entrada
	SetPINMODE(PORT1,30, MODE_NINGUNO);		// Configuro el P1,30 para que no tenga PULL_DOWN ni PULL_UP

//	AD0INTEN &= ~(0x1FF);					// Limpio el registro (Se desactivan las interrupciones globales lo cual es necesario para modo BURST)
//	AD0INTEN |= ((1<<4) | (1<<8));			// Activo la interrupcion del canal ADC0.4 y las interrupciones globales
	AD0INTEN &= 0xFFFFFF10;

	ISER0 |= (1<<ISE_ADC);					// Habilito las interrupciones en el NVIC

//	AD0CR &= ~(0xFF);						// Limpio el registro
	AD0CR |= (0b00010000<<SEL);				// Selecciono que voy a tomar muestras del canal AD0.4

	AD0CR |= (1<<PDN);						// Activo el ADC (ADC is operational)

	AD0CR &= ~(0x0F<<START);				// START=000 (sin disparo, arranca directo desde por el BURST) y EDGE=0 (da igual)
	//AD0CR |= (0x01<<START);					// REVISAR: START=001 (ahora) y EDGE igual
	AD0CR |= (1<<BURST);					// ADC como modo BURST (Adquiere muestras de los canales en forma continua)
}
