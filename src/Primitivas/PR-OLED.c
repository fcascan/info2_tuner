/*
 * PR-OLED.c
 *
 *  Created on: 27/09/2014
 *      Author: Usuario
 */

#include "EA_BaseBoard.h"

void OLED (uint8_t Estado_actual)
{
	static uint8_t Estado_anterior, cursor_anterior=0, Instrumento_anterior=255, Norma_anterior=255, Presicion_anterior=255,
				   Afinacion_anterior=255, Cuerda_anterior=255, Frecuencia_anterior=0;
	extern uint8_t cursor, BPM[], BPM_indice, Instrumento, Norma, Presicion, Afinacion, Cuerda, Triang_Sup_Relleno,
				   Triang_Inf_Relleno;
	extern float Frecuencia_actual, Frecuencia_deseada;
	extern char Nota_actual[], Nota_deseada[];

	oled_putString (0, 1, (uint8_t*) "OPTION", OLED_COLOR_WHITE, OLED_COLOR_BLACK);
	oled_putString (38, 1, (uint8_t*) "TUNE", OLED_COLOR_WHITE, OLED_COLOR_BLACK);
	oled_putString (64, 1, (uint8_t*) "METRO", OLED_COLOR_WHITE, OLED_COLOR_BLACK);


	oled_line (0, 9, 96, 9, OLED_COLOR_WHITE);			// Linea horinzontal de punta a punta
	oled_line (36, 1, 36, 9, OLED_COLOR_WHITE);			// Linea separatoria entre "OPTION" y "TUNE"
	oled_line (62, 1, 62, 9, OLED_COLOR_WHITE);			// Linea separatoria entre "TUNE" y "METRO"

	// Borro lo anterior
	if (Estado_anterior != Estado_actual)
		oled_fillRect(0, 10, 96, 64, OLED_COLOR_BLACK);
	switch (Estado_actual)
	{
		case TUNER:													//actualizar la interfaz grafica al modo afinacion
			// Linea subrrallado de TUNE
			oled_line (37, 10, 61, 10, OLED_COLOR_WHITE);

			// Triangulito selector en TUNE
			oled_line (48, 11, 53, 15, OLED_COLOR_WHITE);				// Linea diagonal (\)
			oled_putPixel(47, 12, OLED_COLOR_WHITE);					// la otra diagonal (/)
			oled_putPixel(46, 13, OLED_COLOR_WHITE);					// 		.
			oled_putPixel(45, 14, OLED_COLOR_WHITE);					// 		.
			oled_putPixel(44, 15, OLED_COLOR_WHITE);					//		.
			oled_line (43, 16, 53, 16, OLED_COLOR_WHITE);				// Linea recta (_)

			// Barra Superior (Afinacion Seleccionada y Cuerda Actual)
			if (Afinacion != Afinacion_anterior){
				oled_fillRect(0, 17, 48, 24, OLED_COLOR_BLACK);
				if (Afinacion==Afinacion_E && Norma==Norma_A440) 	 {oled_putString(0, 17, (uint8_t*) "E440", OLED_COLOR_WHITE, OLED_COLOR_BLACK);}
				if (Afinacion==Afinacion_E && Norma==Norma_A432) 	 {oled_putString(0, 17, (uint8_t*) "E432", OLED_COLOR_WHITE, OLED_COLOR_BLACK);}
				if (Afinacion==Afinacion_D && Norma==Norma_A440) 	 {oled_putString(0, 17, (uint8_t*) "D440", OLED_COLOR_WHITE, OLED_COLOR_BLACK);}
				if (Afinacion==Afinacion_D && Norma==Norma_A432) 	 {oled_putString(0, 17, (uint8_t*) "D432", OLED_COLOR_WHITE, OLED_COLOR_BLACK);}
				if (Afinacion==Afinacion_DROP_D) {oled_putString(0, 17, (uint8_t*) "DROP-D", OLED_COLOR_WHITE, OLED_COLOR_BLACK);}
				if (Afinacion==Afinacion_DROP_C) {oled_putString(0, 17, (uint8_t*) "DROP-C", OLED_COLOR_WHITE, OLED_COLOR_BLACK);}
				if (Afinacion==Afinacion_Eb) 	 {oled_putString(0, 17, (uint8_t*) "Eb", OLED_COLOR_WHITE, OLED_COLOR_BLACK);}
				if (Afinacion==Afinacion_FREE) 	 {oled_putString(0, 17, (uint8_t*) "FREE", OLED_COLOR_WHITE, OLED_COLOR_BLACK);
												  oled_fillRect(80, 17, 96, 24, OLED_COLOR_BLACK);}
			}

			if (Afinacion != Afinacion_FREE){
				if (Cuerda!=Cuerda_anterior){
					oled_fillRect(80, 17, 96, 24, OLED_COLOR_BLACK);
				}
				if (Cuerda==SextaCuerda)	{oled_putString(88, 17, (uint8_t*) "6", OLED_COLOR_WHITE, OLED_COLOR_BLACK);}
				if (Cuerda==QuintaCuerda) 	{oled_putString(88, 17, (uint8_t*) "5", OLED_COLOR_WHITE, OLED_COLOR_BLACK);}
				if (Cuerda==CuartaCuerda) 	{oled_putString(88, 17, (uint8_t*) "4", OLED_COLOR_WHITE, OLED_COLOR_BLACK);}
				if (Cuerda==TercerCuerda) 	{oled_putString(88, 17, (uint8_t*) "3", OLED_COLOR_WHITE, OLED_COLOR_BLACK);}
				if (Cuerda==SegundaCuerda) 	{oled_putString(88, 17, (uint8_t*) "2", OLED_COLOR_WHITE, OLED_COLOR_BLACK);}
				if (Cuerda==PrimerCuerda) 	{oled_putString(88, 17, (uint8_t*) "1", OLED_COLOR_WHITE, OLED_COLOR_BLACK);}
			}

			// Afinacion de la cuerda seleccionada
			if (Afinacion != Afinacion_FREE){
				if (Cuerda != Cuerda_anterior || Afinacion != Afinacion_anterior){
					oled_fillRect(0, 30, 96, 40, OLED_COLOR_BLACK);
					oled_putString (24, 32, (uint8_t*) " : ", OLED_COLOR_WHITE, OLED_COLOR_BLACK);
				}
				oled_putString ( 6, 32, (uint8_t*) Nota_deseada, OLED_COLOR_WHITE, OLED_COLOR_BLACK);
				volatile char aux_string0[6];
				sprintf (aux_string0, "%6.2f", Frecuencia_deseada);
				oled_putString (40, 32, (uint8_t*) aux_string0, OLED_COLOR_WHITE, OLED_COLOR_BLACK);

			}
			if (Afinacion==Afinacion_FREE && Afinacion != Afinacion_anterior){
				oled_fillRect(0, 30, 96, 40, OLED_COLOR_BLACK);
			}

			// Frecuencia y nota actual
			oled_putString (6, 41, (uint8_t*) Nota_actual, OLED_COLOR_WHITE, OLED_COLOR_BLACK);
			oled_putString (24, 41, (uint8_t*) " : ", OLED_COLOR_WHITE, OLED_COLOR_BLACK);
			if (Frecuencia_actual != Frecuencia_anterior){
				volatile char aux_string1[6];
				sprintf (aux_string1, "%6.2f", Frecuencia_actual);
				oled_fillRect(40, 41, 60, 49, OLED_COLOR_BLACK);
				oled_putString (40, 41, (uint8_t*) aux_string1, OLED_COLOR_WHITE, OLED_COLOR_BLACK);
			}

			// Barra Inferior
			if (Instrumento==GUITAR) {oled_putString(0, 56, (uint8_t*) "Guitar", OLED_COLOR_WHITE, OLED_COLOR_BLACK);}
			if (Instrumento==BASS) {oled_putString(0, 56, (uint8_t*) "Bass", OLED_COLOR_WHITE, OLED_COLOR_BLACK);}
			if (Norma==Norma_A440) {oled_putString(70, 56, (uint8_t*) "A440", OLED_COLOR_WHITE, OLED_COLOR_BLACK);}
			if (Norma==Norma_A432) {oled_putString(70, 56, (uint8_t*) "A432", OLED_COLOR_WHITE, OLED_COLOR_BLACK);}

			// Guardo los valores actuales
			Afinacion_anterior=Afinacion;
			Cuerda_anterior=Cuerda;
			Frecuencia_anterior=Frecuencia_actual;

			// Limpio las variables de los otros modos
			Norma_anterior=255;
			Instrumento_anterior=255;
			Presicion_anterior=255;
			break;

		case OPTIONS:												//actualizar la interfaz grafica al modo de opciones
			// Linea subrrallado de OPTION
			oled_line (0, 10, 35, 10, OLED_COLOR_WHITE);

			// Triangulito selector en OPTIONS
			oled_line (18, 11, 23, 15, OLED_COLOR_WHITE);				// Linea diagonal (\)
			oled_putPixel(17, 12, OLED_COLOR_WHITE);					// la otra diagonal (/)
			oled_putPixel(16, 13, OLED_COLOR_WHITE);					// 		.
			oled_putPixel(15, 14, OLED_COLOR_WHITE);					// 		.
			oled_putPixel(14, 15, OLED_COLOR_WHITE);					//		.
			oled_line (13, 16, 23, 16, OLED_COLOR_WHITE);				// Linea recta (_)

			// Listado de Opciones
			oled_putString(9, 19, (uint8_t*) "INSTR: ", OLED_COLOR_WHITE, OLED_COLOR_BLACK);
			oled_putString(9, 28, (uint8_t*) "NORMA: ", OLED_COLOR_WHITE, OLED_COLOR_BLACK);
			oled_putString(9, 37, (uint8_t*) "PRECISION: ", OLED_COLOR_WHITE, OLED_COLOR_BLACK);
			oled_putString(9, 46, (uint8_t*) "OPCION4: ", OLED_COLOR_WHITE, OLED_COLOR_BLACK);
			oled_putString(9, 55, (uint8_t*) "OPCION5: ", OLED_COLOR_WHITE, OLED_COLOR_BLACK);

			// Selecciones
			if (Instrumento != Instrumento_anterior){
				oled_fillRect(50, 19, 96, 26, OLED_COLOR_BLACK);
				if (Instrumento==GUITAR) {oled_putString(52, 19, (uint8_t*) "GUITAR", OLED_COLOR_WHITE, OLED_COLOR_BLACK);}
				if (Instrumento==BASS) {oled_putString(52, 19, (uint8_t*) "BASS", OLED_COLOR_WHITE, OLED_COLOR_BLACK);}
			}
			if (Norma!=Norma_anterior){
				oled_fillRect(50, 28, 96, 35, OLED_COLOR_BLACK);
				if (Norma==Norma_A440) {oled_putString(52, 28, (uint8_t*) "A440", OLED_COLOR_WHITE, OLED_COLOR_BLACK);}
				if (Norma==Norma_A432) {oled_putString(52, 28, (uint8_t*) "A432", OLED_COLOR_WHITE, OLED_COLOR_BLACK);}
			}
			if (Presicion!=Presicion_anterior){
				oled_fillRect(74, 37, 96, 44, OLED_COLOR_BLACK);
				if (Presicion==1) {oled_putString(76, 37, (uint8_t*) "1", OLED_COLOR_WHITE, OLED_COLOR_BLACK);}
				if (Presicion==2) {oled_putString(76, 37, (uint8_t*) "2", OLED_COLOR_WHITE, OLED_COLOR_BLACK);}
				if (Presicion==3) {oled_putString(76, 37, (uint8_t*) "3", OLED_COLOR_WHITE, OLED_COLOR_BLACK);}
			}

			// Cursor
			if (cursor!=cursor_anterior) oled_fillRect(0, 15, 8, 64, OLED_COLOR_BLACK);
			if (cursor==0) oled_putChar(0, 19, '+', OLED_COLOR_WHITE, OLED_COLOR_BLACK);
			if (cursor==1) oled_putChar(0, 28, '+', OLED_COLOR_WHITE, OLED_COLOR_BLACK);
			if (cursor==2) oled_putChar(0, 37, '+', OLED_COLOR_WHITE, OLED_COLOR_BLACK);
			if (cursor==3) oled_putChar(0, 46, '+', OLED_COLOR_WHITE, OLED_COLOR_BLACK);
			if (cursor==4) oled_putChar(0, 55, '+', OLED_COLOR_WHITE, OLED_COLOR_BLACK);

			// Guardo los valores actuales
			Norma_anterior=Norma;
			Instrumento_anterior=Instrumento;
			Presicion_anterior=Presicion;
			cursor_anterior=cursor;

			// Limpio las variables de los otros modos
			Afinacion_anterior=255;
			Cuerda_anterior=255;
			break;

		case METRONOME:												//actualizar la interfaz grafica al modo metronomo
			// Linea subrrallado de METRO
			oled_line (63, 10, 96, 10, OLED_COLOR_WHITE);

			// Triangulito selector en METRO
			oled_line (80, 11, 85, 15, OLED_COLOR_WHITE);				// Linea diagonal (\)
			oled_putPixel(79, 12, OLED_COLOR_WHITE);					// la otra diagonal (/)
			oled_putPixel(78, 13, OLED_COLOR_WHITE);					// 		.
			oled_putPixel(77, 14, OLED_COLOR_WHITE);					// 		.
			oled_putPixel(76, 15, OLED_COLOR_WHITE);					//		.
			oled_line (75, 16, 85, 16, OLED_COLOR_WHITE);				// Linea recta (_)

			//Numero Gigante
			volatile char aux_string2[3];
			sprintf (aux_string2, "%3d", BPM[BPM_indice]);
			oled_putString(40, 37, (uint8_t*) aux_string2, OLED_COLOR_WHITE, OLED_COLOR_BLACK);
			oled_putString(62, 37, (uint8_t*) "BPM", OLED_COLOR_WHITE, OLED_COLOR_BLACK);

			//Triangulito sobre el numero
			oled_line (48, 28, 53, 33, OLED_COLOR_WHITE);				// Linea diagonal (\)
			oled_putPixel(47, 29, OLED_COLOR_WHITE);					// la otra diagonal (/)
			oled_putPixel(46, 30, OLED_COLOR_WHITE);					// 		.
			oled_putPixel(45, 31, OLED_COLOR_WHITE);					// 		.
			oled_putPixel(44, 32, OLED_COLOR_WHITE);					//		.
			oled_line (43, 33, 53, 33, OLED_COLOR_WHITE);				// Linea recta (_)
			if (Triang_Sup_Relleno==ON){								// Relleno "ON"
				oled_putPixel(48, 29, OLED_COLOR_WHITE);
				oled_line(47, 30, 49, 30, OLED_COLOR_WHITE);
				oled_line(46, 31, 50, 31, OLED_COLOR_WHITE);
				oled_line(45, 32, 51, 32, OLED_COLOR_WHITE);
			}
			if (Triang_Sup_Relleno==OFF){
				oled_putPixel(48, 29, OLED_COLOR_BLACK);
				oled_line(47, 30, 49, 30, OLED_COLOR_BLACK);
				oled_line(46, 31, 50, 31, OLED_COLOR_BLACK);
				oled_line(45, 32, 51, 32, OLED_COLOR_BLACK);
			}

			//Triangulito debajo del numero
			oled_line (43, 47, 48, 52, OLED_COLOR_WHITE);				// Linea diagonal (\)
			oled_putPixel(52, 48, OLED_COLOR_WHITE);					// la otra diagonal (/)
			oled_putPixel(51, 49, OLED_COLOR_WHITE);					// 		.
			oled_putPixel(50, 50, OLED_COLOR_WHITE);					// 		.
			oled_putPixel(49, 51, OLED_COLOR_WHITE);					//		.
			oled_line (43, 47, 53, 47, OLED_COLOR_WHITE);				// Linea recta (_)
			if (Triang_Inf_Relleno==ON){								// Relleno "ON"
				oled_line(44, 48, 52, 48, OLED_COLOR_WHITE);
				oled_line(46, 49, 50, 49, OLED_COLOR_WHITE);
				oled_line(47, 50, 49, 50, OLED_COLOR_WHITE);
				oled_putPixel(48, 51, OLED_COLOR_WHITE);
			}
			if (Triang_Inf_Relleno==OFF){
				oled_line(45, 48, 51, 48, OLED_COLOR_BLACK);
				oled_line(46, 49, 50, 49, OLED_COLOR_BLACK);
				oled_line(47, 50, 49, 50, OLED_COLOR_BLACK);
				oled_putPixel(48, 51, OLED_COLOR_BLACK);
			}

			// Limpio las variables de los otros modos
			Afinacion_anterior=255;
			Cuerda_anterior=255;
			Norma_anterior=255;
			Instrumento_anterior=255;
			Presicion_anterior=255;
			break;

		default:
			//si hay error
			break;
	}
	Estado_anterior=Estado_actual;
}
