/*
 * EnviarTrama.c
 *
 *  Created on: 12/12/2014
 *      Author: Usuario
 */

#include "EA_BaseBoard.h"

void EnviarTrama (uint8_t estado)
{
	extern uint8_t BPM[], BPM_indice, Instrumento, Norma, Presicion, Afinacion, Cuerda, Instrumento;
	extern float Frecuencia_actual, Frecuencia_deseada;

	char trama[17], aux_str0[7], aux_str1[7], aux_str2[3];
	volatile uint8_t i=0;

	memset(trama, 0, 18);

	switch (estado){
		case OPTIONS: 			// "Oxxxxx" (Options, Instrumento, Norma, Presicion, Option4, Option5)
			trama[0]='O';											// Options
			(Instrumento==GUITAR)? (trama[1]='G') : (trama[1]='B');		// Instrumento
			(Norma==Norma_A440)? (trama[2]='1') : (trama[2]='2');		// Norma
			(Presicion==1)? (trama[3]='1') : ((Presicion==2)? (trama[3]='2') : (trama[3]='3'));		// Presicion
			trama[4]='0';											// Option4
			trama[5]='0';											// Option5
			break;

		case TUNER:				// "Txxxxxxxxxxxxxx" (Tuner, Afinacion, Cuerda, Instrumento, Norma, Frecuencia Deseada(5 digitos: 3 enteros, 2 decimales), Frecuencia actual (5digitos))
			trama[0]='T';											// Tuner
			switch (Afinacion){										// Afinacion
				case Afinacion_FREE:		trama[1]='0'; break;
				case Afinacion_E:			trama[1]='1'; break;
				case Afinacion_Eb:			trama[1]='2'; break;
				case Afinacion_DROP_D:		trama[1]='3'; break;
				case Afinacion_D:			trama[1]='4'; break;
				case Afinacion_DROP_C:		trama[1]='5'; break;
			}
			switch (Cuerda){										// Cuerda
				case SextaCuerda:			trama[2]='6'; break;
				case QuintaCuerda:			trama[2]='5'; break;
				case CuartaCuerda:			trama[2]='4'; break;
				case TercerCuerda:			trama[2]='3'; break;
				case SegundaCuerda:			trama[2]='2'; break;
				case PrimerCuerda:			trama[2]='1'; break;
			}
			(Instrumento==GUITAR)? (trama[3]='G') : (trama[3]='B');	// Instrumento
			(Norma==Norma_A440)? (trama[4]='1') : (trama[4]='2');	// Norma
			sprintf (aux_str0, "%06.2f", Frecuencia_deseada);		// Frecuencia Deseada (5digitos: xxx.xx)
			for (i=0; i<6; i++){
				trama[i+5]=aux_str0[i];
			}
			sprintf (aux_str1, "%06.2f", Frecuencia_actual);		// Frecuencia Actual (5digitos: xxx.xx)
			for (i=0; i<6; i++){
				trama[i+11]=aux_str1[i];
			}
			break;

		case METRONOME: 		// "Mxxx" (Metronome, BMP_actual)
			trama[0]='M';											// Metronome
			sprintf (aux_str2, "%3d", BPM[BPM_indice]);				// BMP_actual
			for (i=0; i<3; i++){
				trama[i+1]=aux_str2[i];
			}
			break;
	}

	Transmitir (trama);
}
