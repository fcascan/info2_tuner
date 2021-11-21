/*
 * Comparar.c
 *
 *  Created on: 04/12/2014
 *      Author: Usuario
 */

#include "EA_BaseBoard.h"

void Comparar (void)
{
	extern uint8_t Norma, Presicion;
	extern char Nota_actual[];
	extern float Frecuencia_actual;
	extern float Listado_Notas_A440[];
	extern float Listado_Notas_A432[];


	volatile float comparacion_nueva=0, comparacion_mejor=0, aux=0;
	volatile uint8_t indice=0, i=0;

	if (Presicion==3){
			comparacion_mejor=10;}
	if (Presicion==2){
			comparacion_mejor=5;}
	if (Presicion==1){
			comparacion_mejor=1;}



	if (Norma == Norma_A440){
		for (i=0; i<TOTAL_NOTAS_A440; i++){																	// Recorro el listado de notas
			comparacion_nueva= (((float) Frecuencia_actual / Listado_Notas_A440[i]) - 1 );					// Divido la frecuencia actual por una de las notas del listado y resto 1 (entonces si son iguales me da resultado 0 en vez de 1)
			(comparacion_nueva<0)? (comparacion_nueva=(comparacion_nueva * (-1))) : comparacion_nueva;		// Si el resultado es negativo lo hago positivo (puede ocurrir si la nota del listado es mayor a la de la frecuencia actual)
			if (comparacion_nueva < comparacion_mejor){														// Si la comparacion actual es mejor que las anteriores
				comparacion_mejor=comparacion_nueva;															// guardo esa comparacion para seguir comparando con las otras
				indice=i;																						// guardo el indice del listado de notas donde se encuentra esa nota cercana
			}

		}
	}
	else {	// Norma == Norma_432
		for (i=0; i<TOTAL_NOTAS_A432; i++){
			comparacion_nueva= (((float) Frecuencia_actual / Listado_Notas_A432[i]) - 1 );		//
			(comparacion_nueva<0)? (comparacion_nueva*(-1)) : comparacion_nueva;
			if (comparacion_nueva < comparacion_mejor){
				comparacion_mejor=comparacion_nueva;
				indice=i;
			}

		}
	}

	memset (Nota_actual, ' ', 3);

	switch (indice){										// Ahora que se cual es la nota mas cercana lo guardo en la variable global Nota_actual
		case 0 : strcpy(Nota_actual, " C0"); return;
		case 1 : strcpy(Nota_actual, "Db0"); return;
		case 2 : strcpy(Nota_actual, " D0"); return;
		case 3 : strcpy(Nota_actual, "Eb0"); return;
		case 4 : strcpy(Nota_actual, " E0"); return;
		case 5 : strcpy(Nota_actual, " F0"); return;
		case 6 : strcpy(Nota_actual, "Gb0"); return;
		case 7 : strcpy(Nota_actual, " G0"); return;
		case 8 : strcpy(Nota_actual, "Ab0"); return;
		case 9 : strcpy(Nota_actual, " A0"); return;
		case 10: strcpy(Nota_actual, "Bb0"); return;
		case 11: strcpy(Nota_actual, " B0"); return;
		case 12: strcpy(Nota_actual, " C1"); return;
		case 13: strcpy(Nota_actual, "Db1"); return;
		case 14: strcpy(Nota_actual, " D1"); return;
		case 15: strcpy(Nota_actual, "Eb1"); return;
		case 16: strcpy(Nota_actual, " E1"); return;
		case 17: strcpy(Nota_actual, " F1"); return;
		case 18: strcpy(Nota_actual, "Gb1"); return;
		case 19: strcpy(Nota_actual, " G1"); return;
		case 20: strcpy(Nota_actual, "Ab1"); return;
		case 21: strcpy(Nota_actual, " A1"); return;
		case 22: strcpy(Nota_actual, "Bb1"); return;
		case 23: strcpy(Nota_actual, " B1"); return;
		case 24: strcpy(Nota_actual, " C2"); return;
		case 25: strcpy(Nota_actual, "Db2"); return;
		case 26: strcpy(Nota_actual, " D2"); return;
		case 27: strcpy(Nota_actual, "Eb2"); return;
		case 28: strcpy(Nota_actual, " E2"); return;
		case 29: strcpy(Nota_actual, " F2"); return;
		case 30: strcpy(Nota_actual, "Gb2"); return;
		case 31: strcpy(Nota_actual, " G2"); return;
		case 32: strcpy(Nota_actual, "Ab2"); return;
		case 33: strcpy(Nota_actual, " A2"); return;
		case 34: strcpy(Nota_actual, "Bb2"); return;
		case 35: strcpy(Nota_actual, " B2"); return;
		case 36: strcpy(Nota_actual, " C3"); return;
		case 37: strcpy(Nota_actual, "Db3"); return;
		case 38: strcpy(Nota_actual, " D3"); return;
		case 39: strcpy(Nota_actual, "Eb3"); return;
		case 40: strcpy(Nota_actual, " E3"); return;
		case 41: strcpy(Nota_actual, " F3"); return;
		case 42: strcpy(Nota_actual, "Gb3"); return;
		case 43: strcpy(Nota_actual, " G3"); return;
		case 44: strcpy(Nota_actual, "Ab3"); return;
		case 45: strcpy(Nota_actual, " A3"); return;
		case 46: strcpy(Nota_actual, "Bb3"); return;
		case 47: strcpy(Nota_actual, " B3"); return;
		case 48: strcpy(Nota_actual, " C4"); return;
		case 49: strcpy(Nota_actual, "Db4"); return;
		case 50: strcpy(Nota_actual, " D4"); return;
		case 51: strcpy(Nota_actual, "Eb4"); return;
		case 52: strcpy(Nota_actual, " E4"); return;
		case 53: strcpy(Nota_actual, " F4"); return;
		case 54: strcpy(Nota_actual, "Gb4"); return;
		case 55: strcpy(Nota_actual, " G4"); return;
		case 56: strcpy(Nota_actual, "Ab4"); return;
		case 57: strcpy(Nota_actual, " A4"); return;
		case 58: strcpy(Nota_actual, "Bb4"); return;
		case 59: strcpy(Nota_actual, " B4"); return;
		case 60: strcpy(Nota_actual, " C5"); return;
		case 61: strcpy(Nota_actual, "Db5"); return;
		case 62: strcpy(Nota_actual, " D5"); return;
		case 63: strcpy(Nota_actual, "Eb5"); return;
		case 64: strcpy(Nota_actual, " E5"); return;
		case 65: strcpy(Nota_actual, " F5"); return;
		case 66: strcpy(Nota_actual, "Gb5"); return;
		case 67: strcpy(Nota_actual, " G5"); return;
		case 68: strcpy(Nota_actual, "Ab5"); return;
		case 69: strcpy(Nota_actual, " A5"); return;
		case 70: strcpy(Nota_actual, "Bb5"); return;
		case 71: strcpy(Nota_actual, " B5"); return;
		default: strcpy(Nota_actual, "Err"); return;
	}
}
