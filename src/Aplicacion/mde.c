
#include "EA_BaseBoard.h"

void MDE (void)			// Cada estado es una pestaña del OLED, y se cambia de estado con los dos pulsadores
{
	extern uint8_t Estado_actual;

	static uint8_t tecla_anterior;
	volatile uint8_t tecla_actual=NONE;

	tecla_actual=Teclas ();

	switch (Estado_actual)
	{
		case RESET:
			Modo_actual (TUNER);
			Estado_actual=TUNER;
			break;

		case TUNER:
			Modo_actual (TUNER);
			if (tecla_actual==LEFT && (tecla_anterior == NONE)) {
				Estado_actual=OPTIONS;
				tecla_anterior=LEFT;
			}
			if (tecla_actual==RIGHT && (tecla_anterior == NONE)) {
					Estado_actual=METRONOME;
					tecla_anterior=RIGHT;
			}

			break;

		case OPTIONS:
			Modo_actual (OPTIONS);
			if (tecla_actual==LEFT && (tecla_anterior == NONE)) {
				Estado_actual=METRONOME;
				tecla_anterior=LEFT;
			}
			if (tecla_actual==RIGHT && (tecla_anterior == NONE)) {
				Estado_actual=TUNER;
				tecla_anterior=RIGHT;
			}

			break;

		case METRONOME:
			Modo_actual (METRONOME);
			if (tecla_actual==LEFT && (tecla_anterior == NONE)) {
				Estado_actual=TUNER;
				tecla_anterior=LEFT;
			}
			if (tecla_actual==RIGHT && (tecla_anterior == NONE)) {
				Estado_actual=OPTIONS;
				tecla_anterior=RIGHT;
			}

			break;

		default:
			Estado_actual=RESET;
			break;
	}
	tecla_anterior=tecla_actual;
}




void Modo_actual (uint8_t Estado_actual)		// Cada estado es un modo, y se interactua con el Joystick
{
	extern uint8_t cursor, BPM_indice, Instrumento, Norma, Presicion, Afinacion, Cuerda;
	extern float Frecuencia_actual;
	extern uint8_t BufferADCLleno;
	extern uint8_t Triang_Sup_Relleno;
	extern uint8_t Triang_Inf_Relleno;

	static uint8_t joy_anterior=0, Presicion_anterior;
	volatile uint8_t joy_actual=0;


	joy_actual=Joystick();

	switch (Estado_actual)
	{
		case TUNER:

			if (BufferADCLleno==1){
				Analizar ();						// Toma el Buffer del ADC y mediante una FFT (Fast Fourier Transform) la transforma a la frecuencia,
													// luego guarda el espectro obtenido en la variable global llamada spectrum
				Frecuencia_actual=Interpretar ();	// Analiza el espectro obtenido y retorna que frecuencia esta sonando (tipo float)
				Comparar ();						// Comparo esa frecuencia hallada con el listado de notas y determino cual es la mas cercana
				EnviarTrama(TUNER);					// Envio por la UART0 una trama correspondiente al estado actual de todas las variables importantes
			}

			if ((joy_actual & DOWN) && (joy_actual != joy_anterior))
			{
				Cuerda--;
				(Cuerda==0 && Instrumento==GUITAR)? Cuerda=SextaCuerda : Cuerda;
				(Cuerda==0 && Instrumento==BASS)? Cuerda=CuartaCuerda : Cuerda;
			}
			if ((joy_actual & UP) && (joy_actual != joy_anterior))
			{
				Cuerda++;
				(Cuerda==7 && Instrumento==GUITAR)? Cuerda=PrimerCuerda : Cuerda;
				(Cuerda==5 && Instrumento==BASS)? Cuerda=PrimerCuerda : Cuerda;
			}
			if ((joy_actual & RIGHT) && (joy_actual != joy_anterior))
			{
				Afinacion++;
				(Afinacion==6 && Instrumento==GUITAR)? Afinacion=0 : Afinacion;
				(Afinacion==4 && Instrumento==BASS)? Afinacion=0 : Afinacion;

				(Instrumento==GUITAR)? Cuerda=SextaCuerda : Cuerda;
				(Instrumento==BASS)? Cuerda=CuartaCuerda : Cuerda;
			}
			if ((joy_actual & LEFT) && (joy_actual != joy_anterior))
			{
				Afinacion--;
				(Afinacion==255 && Instrumento==GUITAR)? Afinacion=5 : Afinacion;
				(Afinacion==255 && Instrumento==BASS)? Afinacion=3 : Afinacion;

				(Instrumento==GUITAR)? Cuerda=SextaCuerda : Cuerda;
				(Instrumento==BASS)? Cuerda=CuartaCuerda : Cuerda;
			}

			if (Presicion != Presicion_anterior){
				(Presicion==1)? (ADC_CLKDIV_1 ()) : ( (Presicion==2)? (ADC_CLKDIV_2 ()) : (ADC_CLKDIV_3 ()) );
			}

			Presicion_anterior=Presicion;

			Actualizar_Nota_deseada ();	// Actualizo las variables de Nota_deseada y Frecuencia_deseada en funcion de la cuerda y afinacion elegidas
			OLED (TUNER);	// La funcion OLED se encarga de actualizar la interfaz grafica a TUNER

			break;


		case OPTIONS:

			if ((joy_actual & DOWN) && (joy_actual != joy_anterior))
			{
				cursor++;
				if (cursor == 5)	// Si dio la vuelta por abajo
					cursor=0;		// que vaya al primer item
			}
			if ((joy_actual & UP) && (joy_actual != joy_anterior))
			{
				cursor--;
				if (cursor == 255)	// Si dio la vuelta por arriba
					cursor=4;		// que vaya al ultimo item
			}
			if ((joy_actual & RIGHT) && (joy_actual != joy_anterior))
			{
				switch (cursor)
				{
					case 0: if(Instrumento==GUITAR){Instrumento=BASS; Cuerda=CuartaCuerda; Afinacion=Afinacion_FREE;}
							else{Instrumento=GUITAR; Cuerda=SextaCuerda; Afinacion=Afinacion_FREE;} break;
					case 1: if(Norma==Norma_A440){Norma=Norma_A432;} else{Norma=Norma_A440;} break;
					case 2: Presicion++; (Presicion==4)? Presicion=1 : Presicion; break;
					case 3: break;
					case 4: break;
				}
			}
			if ((joy_actual & LEFT) && (joy_actual != joy_anterior))
			{
				switch (cursor)
				{
					case 0: if(Instrumento==GUITAR) {Instrumento=BASS; Cuerda=CuartaCuerda; Afinacion=Afinacion_FREE;}
							else{Instrumento=GUITAR; Cuerda=SextaCuerda; Afinacion=Afinacion_FREE;} break;
					case 1: if(Norma==Norma_A440) {Norma=Norma_A432; } else{Norma=Norma_A440;} break;
					case 2: Presicion--; (Presicion==0)? Presicion=3 : Presicion; break;
					case 3: break;
					case 4: break;
				}
			}

			EnviarTrama(OPTIONS);
			OLED (OPTIONS);

			break;


		case METRONOME:

			//Metronomo (ON);    //Esto lo hago en Systicktimer

			if ((joy_actual & DOWN) && (joy_actual != joy_anterior)){
				BPM_indice -= 1;

				if (BPM_indice==255){	// Si el indice llego al principio
					BPM_indice=38;}		// entonces que vaya al final

				Triang_Inf_Relleno=ON;
			}
			if ((joy_actual & UP) && (joy_actual != joy_anterior)){
				BPM_indice +=1;

				if (BPM_indice==39){	// Si el indice llego al final
					BPM_indice=0;}		// entonces vuelve al principio

				Triang_Sup_Relleno=ON;
			}
			if ((joy_actual==NONE)){
				Triang_Inf_Relleno=OFF;
				Triang_Sup_Relleno=OFF;
			}

			EnviarTrama(METRONOME);
			OLED (METRONOME);

			break;
	}

	joy_anterior=joy_actual;
}
