/*
===============================================================================
 Name        : main.c
 Author      : 
 Version     :
 Copyright   : Copyright (C) 
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>
#include <NXP/crp.h>

// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
__CRP const unsigned int CRP_WORD = CRP_NO_CRP ;

#include "EA_BaseBoard.h"


// Variables globales del modo Opciones
volatile uint8_t Instrumento=GUITAR;
volatile uint8_t Norma=Norma_A440;
volatile uint8_t Presicion=1;

// Variables globales del modo Tuner
volatile uint8_t Afinacion=Afinacion_FREE;
volatile uint8_t Cuerda=SextaCuerda;
volatile float Frecuencia_actual=0, Frecuencia_deseada=0;
volatile char Nota_actual[4], Nota_deseada[4];
volatile float Listado_Notas_A440[TOTAL_NOTAS_A440]={C0,Db0,D0,Eb0,E0,F0,Gb0,G0,Ab0,A0,Bb0,B0,C1,Db1,D1,Eb1,E1,
		F1,Gb1,G1,Ab1,A1,Bb1,B1,C2,Db2,D2,Eb2,E2,F2,Gb2,G2,Ab2,A2,Bb2,B2,C3,Db3,D3,Eb3,E3,F3,Gb3,G3,Ab3,A3,Bb3,
		B3,C4,Db4,D4,Eb4,E4,F4,Gb4,G4,Ab4,A4,Bb4,B4,C5,Db5,D5,Eb5,E5,F5,Gb5,G5,Ab5,A5,Bb5,B5};
volatile float Listado_Notas_A432[TOTAL_NOTAS_A432]={C0_432,Db0_432,D0_432,Eb0_432,E0_432,F0_432,Gb0_432,G0_432,
		Ab0_432,A0_432,Bb0_432,B0_432,C1_432,Db1_432,D1_432,Eb1_432,E1_432,F1_432,Gb1_432,G1_432,Ab1_432,A1_432,
		Bb1_432,B1_432,C2_432,Db2_432,D2_432,Eb2_432,E2_432,F2_432,Gb2_432,G2_432,Ab2_432,A2_432,Bb2_432,B2_432,
		C3_432,Db3_432,D3_432,Eb3_432,E3_432,F3_432,Gb3_432,G3_432,Ab3_432,A3_432,Bb3_432,B3_432,C4_432,Db4_432,
		D4_432,Eb4_432,E4_432,F4_432,Gb4_432,G4_432,Ab4_432,A4_432,Bb4_432,B4_432,C5_432,Db5_432,D5_432,Eb5_432,
		E5_432,F5_432,Gb5_432,G5_432,Ab5_432,A5_432,Bb5_432,B5_432};

// Variables globales del modo Metronomo
volatile uint32_t Ticks=0;
volatile uint8_t BPM[40]={40,42,44,46,48,50,52,54,56,58,60,63,66,69,72,76,80,84,88,92,96,100,104,
					  108,112,116,120,126,132,138,144,152,160,168,176,184,192,200,208};
volatile uint8_t BPM_indice=17;
volatile uint8_t Triang_Sup_Relleno=OFF;
volatile uint8_t Triang_Inf_Relleno=OFF;

// Variables de la maquina de estados
volatile uint8_t Estado_actual=RESET;
volatile uint8_t cursor=0;

// Variables globales del ADC
volatile uint8_t  BufferADCLleno=0;
volatile uint16_t BufferADC[1024];

// Variables de la FFT
volatile uint16_t spectrum[1024];

// Variables de la UART0
volatile uint8_t BufferTx[TOPE_BUFFER_TX];		//!< Buffer de Transmision
volatile uint8_t BufferRx[TOPE_BUFFER_RX];		//!< Buffer de Recepcion
volatile uint8_t IndiceTxIn,IndiceTxOut;		//!< Indices de Transmision
volatile uint8_t IndiceRxIn,IndiceRxOut;		//!< Indices de Recepcion
volatile char TxStart;							//!< flag de fin de TX
volatile uint8_t BufferSalidas;


// Funcion Main
int main (void)
{
	Inic_Stick ();
	Inic_EABaseBoard ();

	while (1)	// Bucle Infinito
	{
		MDE ();
	}
	return 0;
}


