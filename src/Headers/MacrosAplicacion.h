/*
 * MacrosAplicacion.h
 *
 *  Created on: 15/12/2014
 *      Author: Usuario
 */

#ifndef MACROSAPLICACION_H_
#define MACROSAPLICACION_H_

///////////////////////
// Macros
///////////////////////

//Macros Modo Opciones
#define		GUITAR			0
#define		BASS			1

#define		Norma_A440		0
#define		Norma_A432		1

//Macros Modo Afinacion
#define		BIN_RANGE_1			0.5689035	// 0.5689035: Impecable! NO TOCAR MAS!			// SOLO LEE HASTA 291,28Hz! con AD0CR |= (0xA8<<CLKDIV);
#define		BIN_RANGE_2			0.6567483	//
#define		BIN_RANGE_3			0.8176734	//

#define		Afinacion_FREE		0
#define		Afinacion_E			1
#define		Afinacion_Eb		2
#define		Afinacion_DROP_D	3
#define		Afinacion_D			4
#define		Afinacion_DROP_C	5

#define		SextaCuerda			6
#define		QuintaCuerda		5
#define		CuartaCuerda		4
#define		TercerCuerda		3
#define		SegundaCuerda		2
#define		PrimerCuerda		1

#endif /* MACROSAPLICACION_H_ */
