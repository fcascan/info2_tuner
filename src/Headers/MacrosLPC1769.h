/*
 * MacrosLPC1769.h
 *
 *  Created on: 30/09/2014
 *      Author: Usuario
 */

#ifndef MACROSLPC1769_H_
#define MACROSLPC1769_H_

// PCLK
#define SYSTEMCORECLOCK		100000000UL	// 100 MHZ

// Macros para control de los GPIO (General Purpose Input/Output)
	#define		PORT0				0
	#define		PORT1				1
	#define		PORT2				2
	#define		PORT3				3
	#define		PORT4				4

	// Macros SetPINSEL
	#define		FUNCION_GPIO		0
	#define		FUNCION_1			1
	#define		FUNCION_2			2
	#define		FUNCION_3			3

	// Macros SetPINMODE
	#define		MODE_PULL_UP		0
	#define		MODE_REPEATER		1
	#define		MODE_NINGUNO		3
	#define		MODE_PULL_DOWN		4

	// Macros SetDIR
	#define		ENTRADA				0
	#define		SALIDA				1

	// Macros SetPIN
	#define		ON					1
	#define		OFF					0

	// Macros GetPIN
	#define		ACTIVO_ALTO			1
	#define		ACTIVO_BAJO			0

// Macros de la UART0
#define TOPE_BUFFER_TX				30
#define TOPE_BUFFER_RX				20
#define BAUDRATE_9600				9600            /* Velocidad del Puerto Serie    */


#endif /* MACROSLPC1769_H_ */
