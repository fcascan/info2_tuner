/*
 * fft.c
 *
 *  Created on: 14/11/2014
 *      Author: Usuario
 */
#include "EA_BaseBoard.h"


void Analizar (void)
{
	extern uint16_t BufferADC[];
	extern uint8_t BufferADCLleno;
	extern uint16_t spectrum[];

	short fft_in[2048];
	short fft_out[2048];

	volatile int i;
	volatile int32_t a=0, b=0;


	//memset (fft_in, 0, 2048);					// Copia el caracter '0' en todas las posiciones de fft_in

	for (i = 0; i < 1024; i++){					// Guardo en los indices par de fft_in los valores del BufferADC
		fft_in[2 * i] = BufferADC[i];
		fft_in[(2 * i) + 1] = 0;				// No es necesario
	}


	vF_dspl_fftR4b16N1024 (fft_out, fft_in);	// Realizo la fft a "fft_in" y el resultado obtenido se guarda en "ftt_out"

	// Convert the output data back into real numbers because I am not interested
	// in the phase component.
	// Also note that the second half of the FFT output mirrors the first half so it is
	// only necessary to process 512 data points.

	memset (spectrum, 0, 1024);

	for(i = 1; i < 512; i++)				// En spectrum guardo los valores de las amplitudes de cada franja de frecuencia leida
	{
		a = fft_out[2 * i];								// Parte Real (indices par)
		b = fft_out[(2 * i) + 1];						// Parte Imaginaria (indices impar)
		spectrum[i] = ( abs(a*a) + abs(b*b) );			// Hallo el Modulo del numero y lo guardo en spectrum[i] (no realizo la raiz cuadrada)
	}													// porque consume mucho tiempo y no es tan necesario)

	memset (BufferADC, 0, 1024);
	BufferADCLleno=0;
}



float Interpretar (void)
{
	extern uint16_t spectrum[];
	extern uint16_t BufferADC[];
	extern uint8_t Presicion;

	volatile uint16_t i=0, indice=0;
	volatile uint16_t aux=0;

	for (i=1; i < 512; i++)				// Analizo el espectro para ver en que parte esta sonando mas fuerte
	{										// Solo se analiza la primer mitad del espectro porque la otra mitad contiene la misma informacion
		if (aux < spectrum[i]){
			indice=i;					// Guardo la posicion de spectrum donde se encuentra el valor mas alto hallado hasta el momento
			aux = spectrum[i];			// Guardo ese valor hallado para seguir comparando con el resto
		}
	}

	// Entonces ahora ya tengo en indice la posicion de spectrum donde se presento la frecuencia que sono mas alto y donde
	// supongo que esta la nota que esta sonando actualmente

	if (Presicion==1){
		return (indice*BIN_RANGE_1);
	}
	if (Presicion==2){
		return (indice*BIN_RANGE_2);
	}
	if (Presicion==3){
		return (indice*BIN_RANGE_3);
	}
}
