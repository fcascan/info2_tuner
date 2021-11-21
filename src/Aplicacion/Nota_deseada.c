/*
 * Nota_deseada.c
 *
 *  Created on: 12/12/2014
 *      Author: Usuario
 */

#include "EA_BaseBoard.h"

void Actualizar_Nota_deseada (void)
{
	extern uint8_t Instrumento, Norma, Afinacion, Cuerda;
	extern float Frecuencia_deseada;
	extern char Nota_deseada[];

	// Para Norma A440
	if (Norma==Norma_A440){
		if (Cuerda==SextaCuerda) {
			if (Afinacion==Afinacion_E) {
				strcpy (Nota_deseada, " E2");
				Frecuencia_deseada=E2;
			}
			if (Afinacion==Afinacion_DROP_D || Afinacion==Afinacion_D) {
				strcpy (Nota_deseada, " D2");
				Frecuencia_deseada=D2;
			}
			if (Afinacion==Afinacion_Eb) {
				strcpy (Nota_deseada, "Eb2");
				Frecuencia_deseada=Eb2;
			}
			if (Afinacion==Afinacion_DROP_C) {
				strcpy (Nota_deseada, " C2");
				Frecuencia_deseada=C2;
			}
		}
		if (Cuerda==QuintaCuerda) {
			if (Afinacion==Afinacion_E || Afinacion==Afinacion_DROP_D) {
				strcpy (Nota_deseada, " A2");
				Frecuencia_deseada=A2;
			}
			if (Afinacion==Afinacion_Eb) {
				strcpy (Nota_deseada, "Ab2");
				Frecuencia_deseada=Ab2;
			}
			if (Afinacion==Afinacion_D || Afinacion==Afinacion_DROP_C) {
				strcpy (Nota_deseada, " G2");
				Frecuencia_deseada=G2;
			}
		}
		if (Cuerda==CuartaCuerda) {
			if (Afinacion==Afinacion_E || Afinacion==Afinacion_DROP_D) {
				if (Instrumento==GUITAR){
					strcpy (Nota_deseada, " D3");
					Frecuencia_deseada=D3;
				}
				if (Instrumento==BASS && Afinacion==Afinacion_DROP_D){
					strcpy (Nota_deseada, " D1");
					Frecuencia_deseada=D1;
				}
				if (Instrumento==BASS && Afinacion==Afinacion_E){
					strcpy (Nota_deseada, " E1");
					Frecuencia_deseada=E1;
				}
			}
			if (Afinacion==Afinacion_Eb) {
				if (Instrumento==GUITAR){
					strcpy (Nota_deseada, "Db3");
					Frecuencia_deseada=Db3;
				}
				if (Instrumento==BASS){
					strcpy (Nota_deseada, "Eb1");
					Frecuencia_deseada=Eb1;
				}
			}
			if (Afinacion==Afinacion_D || Afinacion==Afinacion_DROP_C) {
				strcpy (Nota_deseada, " C3");
				Frecuencia_deseada=C3;
			}
		}
		if (Cuerda==TercerCuerda) {
			if (Afinacion==Afinacion_E || Afinacion==Afinacion_DROP_D) {
				if (Instrumento==GUITAR){
					strcpy (Nota_deseada, " G3");
					Frecuencia_deseada=G3;
				}
				if (Instrumento==BASS){
					strcpy (Nota_deseada, " A1");
					Frecuencia_deseada=A1;
				}
			}
			if (Afinacion==Afinacion_Eb) {
				if (Instrumento==GUITAR){
					strcpy (Nota_deseada, "Gb3");
					Frecuencia_deseada=Gb3;
				}
				if (Instrumento==BASS){
					strcpy (Nota_deseada, "Ab1");
					Frecuencia_deseada=Ab1;
				}
			}
			if (Afinacion==Afinacion_D || Afinacion==Afinacion_DROP_C) {
				strcpy (Nota_deseada, " F3");
				Frecuencia_deseada=F3;
			}
		}
		if (Cuerda==SegundaCuerda) {
			if (Afinacion==Afinacion_E || Afinacion==Afinacion_DROP_D) {
				if (Instrumento==GUITAR){
					strcpy (Nota_deseada, " B3");
					Frecuencia_deseada=B3;
				}
				if (Instrumento==BASS){
					strcpy (Nota_deseada, " D2");
					Frecuencia_deseada=D2;
				}
			}
			if (Afinacion==Afinacion_Eb) {
				if (Instrumento==GUITAR){
					strcpy (Nota_deseada, "Bb3");
					Frecuencia_deseada=Bb3;
				}
				if (Instrumento==BASS){
					strcpy (Nota_deseada, "Db2");
					Frecuencia_deseada=Db2;
				}
			}
			if (Afinacion==Afinacion_D || Afinacion==Afinacion_DROP_C) {
				strcpy (Nota_deseada, " A3");
				Frecuencia_deseada=A3;
			}
		}
		if (Cuerda==PrimerCuerda) {
			if (Afinacion==Afinacion_E || Afinacion==Afinacion_DROP_D) {
				if (Instrumento==GUITAR){
					strcpy (Nota_deseada, " E4");
					Frecuencia_deseada=E4;
				}
				if (Instrumento==BASS){
					strcpy (Nota_deseada, " G2");
					Frecuencia_deseada=G2;
				}
			}
			if (Afinacion==Afinacion_Eb) {
				if (Instrumento==GUITAR){
					strcpy (Nota_deseada, "Eb4");
					Frecuencia_deseada=Eb4;
				}
				if (Instrumento==BASS){
					strcpy (Nota_deseada, "Gb2");
					Frecuencia_deseada=Gb2;
				}
			}
			if (Afinacion==Afinacion_D || Afinacion==Afinacion_DROP_C) {
				strcpy (Nota_deseada, "D4");
				Frecuencia_deseada=D4;
			}
		}
	}

	// Para norma A432

	if (Norma==Norma_A432){
		if (Cuerda==SextaCuerda) {
			if (Afinacion==Afinacion_E) {
				strcpy (Nota_deseada, " E2");
				Frecuencia_deseada=E2_432;
			}
			if (Afinacion==Afinacion_DROP_D || Afinacion==Afinacion_D) {
				strcpy (Nota_deseada, " D2");
				Frecuencia_deseada=D2_432;
			}
			if (Afinacion==Afinacion_Eb) {
				strcpy (Nota_deseada, "Eb2");
				Frecuencia_deseada=Eb2_432;
			}
			if (Afinacion==Afinacion_DROP_C) {
				strcpy (Nota_deseada, " C2");
				Frecuencia_deseada=C2_432;
			}
		}
		if (Cuerda==QuintaCuerda) {
			if (Afinacion==Afinacion_E || Afinacion==Afinacion_DROP_D) {
				strcpy (Nota_deseada, " A2");
				Frecuencia_deseada=A2_432;
			}
			if (Afinacion==Afinacion_Eb) {
				strcpy (Nota_deseada, "Ab2");
				Frecuencia_deseada=Ab2_432;
			}
			if (Afinacion==Afinacion_D || Afinacion==Afinacion_DROP_C) {
				strcpy (Nota_deseada, " G2");
				Frecuencia_deseada=G2_432;
			}
		}
		if (Cuerda==CuartaCuerda) {
			if (Afinacion==Afinacion_E || Afinacion==Afinacion_DROP_D) {
				if (Instrumento==GUITAR){
					strcpy (Nota_deseada, " D3");
					Frecuencia_deseada=D3_432;
				}
				if (Instrumento==BASS && Afinacion==Afinacion_DROP_D){
					strcpy (Nota_deseada, " D1");
					Frecuencia_deseada=D1_432;
				}
				if (Instrumento==BASS && Afinacion==Afinacion_E){
					strcpy (Nota_deseada, " E1");
					Frecuencia_deseada=E1_432;
				}
			}
			if (Afinacion==Afinacion_Eb) {
				if (Instrumento==GUITAR){
					strcpy (Nota_deseada, "Db3");
					Frecuencia_deseada=Db3_432;
				}
				if (Instrumento==BASS){
					strcpy (Nota_deseada, "Eb1");
					Frecuencia_deseada=Eb1_432;
				}
			}
			if (Afinacion==Afinacion_D || Afinacion==Afinacion_DROP_C) {
				strcpy (Nota_deseada, " C3");
				Frecuencia_deseada=C3_432;
			}
		}
		if (Cuerda==TercerCuerda) {
			if (Afinacion==Afinacion_E || Afinacion==Afinacion_DROP_D) {
				if (Instrumento==GUITAR){
					strcpy (Nota_deseada, " G3");
					Frecuencia_deseada=G3_432;
				}
				if (Instrumento==BASS){
					strcpy (Nota_deseada, " A1");
					Frecuencia_deseada=A1_432;
				}
			}
			if (Afinacion==Afinacion_Eb) {
				if (Instrumento==GUITAR){
					strcpy (Nota_deseada, "Gb3");
					Frecuencia_deseada=Gb3_432;
				}
				if (Instrumento==BASS){
					strcpy (Nota_deseada, "Ab1");
					Frecuencia_deseada=Ab1_432;
				}
			}
			if (Afinacion==Afinacion_D || Afinacion==Afinacion_DROP_C) {
				strcpy (Nota_deseada, " F3");
				Frecuencia_deseada=F3_432;
			}
		}
		if (Cuerda==SegundaCuerda) {
			if (Afinacion==Afinacion_E || Afinacion==Afinacion_DROP_D) {
				if (Instrumento==GUITAR){
					strcpy (Nota_deseada, " B3");
					Frecuencia_deseada=B3_432;
				}
				if (Instrumento==BASS){
					strcpy (Nota_deseada, " D2");
					Frecuencia_deseada=D2_432;
				}
			}
			if (Afinacion==Afinacion_Eb) {
				if (Instrumento==GUITAR){
					strcpy (Nota_deseada, "Bb3");
					Frecuencia_deseada=Bb3_432;
				}
				if (Instrumento==BASS){
					strcpy (Nota_deseada, "Db2");
					Frecuencia_deseada=Db2_432;
				}
			}
			if (Afinacion==Afinacion_D || Afinacion==Afinacion_DROP_C) {
				strcpy (Nota_deseada, " A3");
				Frecuencia_deseada=A3_432;
			}
		}
		if (Cuerda==PrimerCuerda) {
			if (Afinacion==Afinacion_E || Afinacion==Afinacion_DROP_D) {
				if (Instrumento==GUITAR){
					strcpy (Nota_deseada, " E4");
					Frecuencia_deseada=E4_432;
				}
				if (Instrumento==BASS){
					strcpy (Nota_deseada, " G2");
					Frecuencia_deseada=G2_432;
				}
			}
			if (Afinacion==Afinacion_Eb) {
				if (Instrumento==GUITAR){
					strcpy (Nota_deseada, "Eb4");
					Frecuencia_deseada=Eb4_432;
				}
				if (Instrumento==BASS){
					strcpy (Nota_deseada, "Gb2");
					Frecuencia_deseada=Gb2_432;
				}
			}
			if (Afinacion==Afinacion_D || Afinacion==Afinacion_DROP_C) {
				strcpy (Nota_deseada, " D4");
				Frecuencia_deseada=D4_432;
			}
		}
	}
}
