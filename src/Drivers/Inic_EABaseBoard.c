/*
 * Inic_EABaseBoard.c
 *
 *  Created on: 27/09/2014
 *      Author: Usuario
 */

#include "EA_BaseBoard.h"


void Inic_EABaseBoard (void)
{
	inic_Joystick ();
	inic_SW ();
	inic_Buzzer ();
	inic_SSP ();
	inic_Oled ();
	inic_PortExpander ();
}


void inic_Joystick (void)
{
	SetPINSEL (JOYSTICK_CENTER, FUNCION_GPIO);
	SetPINMODE (JOYSTICK_CENTER, MODE_PULL_UP);
	SetDIR (JOYSTICK_CENTER, ENTRADA);

	SetPINSEL (JOYSTICK_DOWN, FUNCION_GPIO);
	SetPINMODE (JOYSTICK_DOWN, MODE_PULL_UP);
	SetDIR (JOYSTICK_DOWN, ENTRADA);

	SetPINSEL (JOYSTICK_LEFT, FUNCION_GPIO);
	SetPINMODE (JOYSTICK_LEFT, MODE_PULL_UP);
	SetDIR (JOYSTICK_LEFT, ENTRADA);

	SetPINSEL (JOYSTICK_RIGHT, FUNCION_GPIO);
	SetPINMODE (JOYSTICK_RIGHT, MODE_PULL_UP);
	SetDIR (JOYSTICK_RIGHT, ENTRADA);

	SetPINSEL (JOYSTICK_UP, FUNCION_GPIO);
	SetPINMODE (JOYSTICK_UP, MODE_PULL_UP);
	SetDIR (JOYSTICK_UP, ENTRADA);
}


void inic_SW (void)
{
	SetPINSEL (SW_left, FUNCION_GPIO);
	SetPINMODE (SW_left, MODE_PULL_UP);
	SetDIR (SW_left, ENTRADA);

	SetPINSEL (SW_right, FUNCION_GPIO);
	SetPINMODE (SW_right, MODE_PULL_UP);
	SetDIR (SW_right, ENTRADA);

//	SetPINSEL (SW_reset, FUNCION_GPIO);
//	SetPINMODE (SW_reset, MODE_PULL_DOWN);
//	SetDIR (SW_reset, ENTRADA);
}


void inic_Buzzer (void)
{
	SetPINSEL (Buzzer, FUNCION_GPIO);
	SetPINMODE (Buzzer, MODE_REPEATER);
	SetDIR (Buzzer, SALIDA);
	SetPIN (Buzzer, OFF);
}


void inic_SSP (void)
{

	SetPINSEL (Oled_sck, FUNCION_2);				// Funcion de PIN "SCK1"
	SetPINMODE (Oled_sck, MODE_PULL_UP);
	SetDIR (Oled_sck, SALIDA);

	SetPINSEL (Oled_mosi, FUNCION_2);				// Funcion de PIN "MOSI1"
	SetPINMODE (Oled_mosi, MODE_PULL_UP);
	SetDIR (Oled_mosi, SALIDA);

	SetPINSEL (Oled_miso, FUNCION_2);				// Funcion de PIN "MISO1"
	SetPINMODE (Oled_miso, MODE_PULL_UP);
	SetDIR (Oled_miso, SALIDA);

	SetPINSEL (PORT2,2, FUNCION_GPIO);
	SetPINMODE (PORT2,2, MODE_PULL_UP);
	SetDIR (PORT2,1, SALIDA);


	// Configuracion del SSP
	PCONP |= (1<<PCSSP1);											// Habilito el periferico del SSP1 en el registro PCONP

	PCLKSEL0 |= (CCLK<<PCLK_SSP1); 									// Selecciono para que el SSP1 funcione como PCLK=CCLK

	SSP1CR0 |= ((0b0111<<DSS) | (00<<FRF) | (0<<CPOL) | (0<<CPHA) | (0b00001100<<SCR));	// SSP transfiere de a 8bits como SPI, la transmicion es por
																	// flanco ascendente del SCK y comienza con el primer flanco,

	SSP1CR1 |= ((0<<LBM) | (0<<SSE) | (0<<MS) | (0<<SOD));			// Modo sin Loopback, controlador SSP habilitado, Modo MASTER,
																	// SOD solo relevante para el caso de Slave

	SSP1CPSR |= (0b10<<CPSDVSR);									// Seteo la preescala del clock (solo pueden ser numeros pares
																	// y el minimo es 2)

	//SSP1IMSC |= ((0<<RORIM) | (0<<RTIM) | (0<<RXIM) | (0<<TXIM));	// Todas las interrupciones del SSP apagadas

	//SSP1DMACR |= ((0<<RXDMAE) | (0<<TXDMAE));						// Apago la opcion de manejar las lecturas y escrituras por DMA

	SSP1CR1 |= (1<<SSE);											// Ahora que se configuro el SSP, activo el Enable
}


void inic_Oled (void)
{
	// El Display OLED se puede manejar por la interfaz I2C (Inter Integrated Circuit Communications)
	// o SPI (Serial-Peripheral interface), en este caso se eligio por SPI porque se puede mover mayor
	// volumen de datos aunque requiere de mas señales y porque por I2C esta conectado un PCA9532 que
	// maneja unos 16 leds que tambien se van a utilizar

	SetPINSEL (Oled_Voled_en, FUNCION_GPIO);		// Alimentacion del OLED
	SetPINMODE (Oled_Voled_en, MODE_PULL_UP);
	SetDIR (Oled_Voled_en, SALIDA);

	SetPINSEL (Oled_dc, FUNCION_GPIO);				// Selector d/c
	SetPINMODE (Oled_dc, MODE_PULL_UP);
	SetDIR (Oled_dc, SALIDA);

	SetPINSEL (Oled_ssel, FUNCION_2);				// Funcion de PIN "SSEL1"
	SetPINMODE (Oled_ssel, MODE_PULL_UP);
	SetDIR (Oled_ssel, SALIDA);

	/*------------------------------------------------------------------------------------------*/
	/*						INICIALIZACION   RECOMENDADA  POR  EL  FABRICANTE					*/
	/*--------------------------------------------//-------------------------------------------*/
	/* 			Secuencia de encendido			  //  				Inicializacion				*/
	/*--------------------------------------------//--------------------------------------------*/
	/*	1. Power up VDD							  //	1. RES=0;	(Reset es activo en bajo)	*/
	/*	2. Send Display offcommand				  //	2. delay 100ms (espero 100milisegs)		*/
	/*	3. Driver IC Initial Setting			  //	3. RES=1;	(Salgo del estado de Reset) */
	/*	4. Clear Screen							  //	4. Initial Code							*/
	/*	5. Power up VDDH						  //	5. Display ON (Enciendo el display)		*/
	/*	6. Delay 100ms (when VDD is stable)		  //	6. Clear RAM (Vacio la RAM)				*/
	/*	7. Send Display on command 				  //  	7. Start Display (Habilito el display)	*/
	/*--------------------------------------------//--------------------------------------------*/

	SetPIN (Oled_Voled_en, OFF);		// me aseguro que el display este apagado
	SetPIN (Oled_ssel, ON);				// selecciono que lo que se va a enviar son comandos

	writeCommand(0x02);		//set low column address
	writeCommand(0x12);		//set high column address
	writeCommand(0x40);		//(display start set)
	writeCommand(0x2e);		//(stop horzontal scroll)
	writeCommand(0x81);		//(set contrast control register)
	writeCommand(0x32);
	writeCommand(0x82);		//(brightness for color banks)
	writeCommand(0x80);		//(display on)
	writeCommand(0xa1);		//(set segment re-map)
	writeCommand(0xa6);		//(set normal/inverse display)
	//writeCommand(0xa7);	//(set inverse display)
	writeCommand(0xa8);		//(set multiplex ratio)
	writeCommand(0x3F);
	writeCommand(0xd3);		//(set display offset)
	writeCommand(0x40);
	writeCommand(0xad);		//(set dc-dc on/off)
	writeCommand(0x8E);		//
	writeCommand(0xc8);		//(set com output scan direction)
	writeCommand(0xd5);		//(set display clock divide ratio/oscillator/frequency)
	writeCommand(0xf0);		//
	writeCommand(0xd8);		//(set area color mode on/off & low power display mode )
	writeCommand(0x05);		//
	writeCommand(0xd9);		//(set pre-charge period)
	writeCommand(0xF1);
	writeCommand(0xda);		//(set com pins hardware configuration)
	writeCommand(0x12);
	writeCommand(0xdb);		//(set vcom deselect level)
	writeCommand(0x34);
	writeCommand(0x91);		//(set look up table for area color)
	writeCommand(0x3f);
	writeCommand(0x3f);
	writeCommand(0x3f);
	writeCommand(0x3f);
	writeCommand(0xaf);		//(display on)
	writeCommand(0xa4);		//(display on)

	extern uint8_t shadowFB[SHADOW_FB_SIZE];

	memset (shadowFB, 0, SHADOW_FB_SIZE); 		// The C library function void *memset(void *str, int c, size_t n) copies the
												// character c (an unsigned char) to the first n characters of the string pointed
												// to by the argument str.

	volatile int i=0;
    for (i=0; i<0xffff; i++);					// Pequeño delay antes de encender el Display
	SetPIN (Oled_Voled_en, ON);					// Enciendo el Display

	oled_clearScreen (OLED_COLOR_BLACK);
}


void inic_PortExpander (void)
{
	SetPINSEL (I2C_sda, FUNCION_2);				// Funcion de PIN "SDA2"
	SetPINMODE (I2C_sda, MODE_PULL_UP);
	SetDIR (I2C_sda, SALIDA);

	SetPINSEL (I2C_scl, FUNCION_2);				// Funcion de PIN "SCL2"
	SetPINMODE (I2C_scl, MODE_PULL_UP);
	SetDIR (I2C_scl, SALIDA);


	PCONP |= (1<<PCI2C2);							// Habilito el periferico I2C2
	PCLKSEL1 |= (CCLK_4<<PCLK_I2C2); 				// Selecciono para que el I2C2 funcione como PCLK=CCLK/4
}

