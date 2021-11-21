/*
 * EA_BaseBoard.h
 *
 *  Created on: 27/09/2014
 *      Author: Usuario
 */

#ifndef EA_BASEBOARD_H_
#define EA_BASEBOARD_H_

///////////////////////
// Librerias
///////////////////////

// Archivos Cabezera propios del programa
#include "Oscilador.h"
#include "RegsLPC1769.h"
#include "MacrosLPC1769.h"
#include "Mde.h"
#include "Notas.h"
#include "MacrosAplicacion.h"

// Libreria DSP de NXP
#include "cr_dsplib.h"

// Biblioteca Estandar de C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


//Puertos Baseboard
#define		RGB_RED   	PORT2,0
#define		RGB_BLUE  	PORT0,26
#define		RGB_GREEN 	PORT2,1

#define 	JOYSTICK_CENTER 	PORT0,17
#define 	JOYSTICK_UP     	PORT2,3
#define 	JOYSTICK_DOWN  		PORT0,15
#define 	JOYSTICK_LEFT  		PORT2,4
#define 	JOYSTICK_RIGHT		PORT0,16

#define		SW_left		PORT0,4
#define		SW_right	PORT1,31

//#define		Speaker				PORT0,26	//LM4811: VIN1 y VIN2 (filtrados)
//#define		Speaker_clk			PORT0,27	//LM4811: clk
//#define		Speaker_updn		PORT0,28	//LM4811: up/dn
//#define		Speaker_shutdn		PORT2,13	//LM4811: shutdn

#define		Buzzer		PORT0,22

//Macros Rotary_SW
#define 	ROTARY_WAIT  	0
#define 	ROTARY_RIGHT 	1
#define 	ROTARY_LEFT  	2

//Macros Joystick
#define		NONE		0x00	// 0000 0000
#define 	CENTER 		0x01	// 0000 0001
#define 	UP   		0x02	// 0000 0010
#define 	DOWN		0x04	// 0000 0100
#define 	LEFT		0x08	// 0000 1000
#define 	RIGHT		0x10	// 0001 0000

//Macros 16bit Port-Expander (PCA9532) o RS232
#define		I2C_scl			PORT0,11	// I2C: Clock Line (SCL)
#define		I2C_sda			PORT0,10	// I2C: Data Line (SDA)

//Macros OLED
#define 	OLED_DISPLAY_WIDTH  	96
#define 	OLED_DISPLAY_HEIGHT 	64

#define		Oled_Voled_en		PORT2,1		// Enable del Oled
#define		Oled_sck			PORT0,7		// SPI: Serial-Clock
#define		Oled_mosi			PORT0,9		// SPI: Master-Out, Slave-In (LPC1769 es el Master, el OLED es el Slave)
#define		Oled_ssel			PORT0,6		// SPI: Slave Select
#define		Oled_miso			PORT0,8		// SPI: Master-In, Slave-Out (No se va a usar porque no voy a leer el OLED)
#define		Oled_dc				PORT2,7		// Data/Command selection PIN (1: Data, 0: Command)


//The display controller can handle a resolution of 132x64. The OLED
//on the base board is 96x64.
#define X_OFFSET 18
#define SHADOW_FB_SIZE (OLED_DISPLAY_WIDTH*OLED_DISPLAY_HEIGHT >> 3)

#define setAddress(page,lowerAddr,higherAddr)\
    writeCommand(page);\
    writeCommand(lowerAddr);\
    writeCommand(higherAddr);

#define SSP_DR_BITMASK(n)   ((n)&0xFFFF)

typedef enum
{
    OLED_COLOR_BLACK,
    OLED_COLOR_WHITE
} oled_color_t;


///////////////////////
// Prototipos
///////////////////////

/* Drivers/Inic_EABaseBoard.c */
void Inic_EABaseBoard (void);
void inic_Joystick (void);
void inic_Oled (void);
void inic_SW (void);
void inic_Buzzer (void);
void inic_SSP (void);
void inic_PortExpander (void);

/* Drivers/Inic_Stick.c */
void Inic_Stick (void);
void inic_Systick (void);
void inic_ADC (void);
void inic_UART0 (int);

/* Drivers/Inic_Oscilador.c */
void InitPLL ( void );

/* Drivers/FW-GPIO.c */
void SetDIR (uint8_t, uint8_t, uint8_t);
void SetPIN (uint8_t, uint8_t, uint8_t);
uint8_t GetPIN (uint8_t, uint8_t, uint8_t);

/* Drivers/FW-CONFIG.c */
void SetPINSEL (uint8_t, uint8_t, uint8_t);
void SetPINMODE (uint8_t, uint8_t, uint8_t);

/* Drivers/FW-UART0.c */
void PushTx (uint8_t);
int PopTx (void);
void PushRx (uint8_t);
int PopRx (void);

/* Drivers/FW-OLED.c */
void oled_putPixel (uint8_t x, uint8_t y, oled_color_t color);
//void hLine(uint8_t x0, uint8_t y0, uint8_t x1, oled_color_t color);
//void vLine(uint8_t x0, uint8_t y0, uint8_t y1, oled_color_t color);
void oled_line (uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, oled_color_t color);
void oled_circle (uint8_t x0, uint8_t y0, uint8_t r, oled_color_t color);
void oled_rect (uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, oled_color_t color);
void oled_fillRect (uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, oled_color_t color);
void oled_clearScreen (oled_color_t color);
void oled_putString (uint8_t x, uint8_t y, uint8_t *pStr, oled_color_t fb, oled_color_t bg);
uint8_t oled_putChar (uint8_t x, uint8_t y, uint8_t ch, oled_color_t fb, oled_color_t bg);
void oled_putBIGChar(uint8_t x, uint8_t y, uint8_t *ch, oled_color_t fb, oled_color_t bg);
void writeCommand (uint8_t);
void writeData (uint8_t);
void SSP_transfer_byte (uint8_t);
void oled_putPixel (uint8_t, uint8_t, oled_color_t);

/* Primtivas/PR-Joystick.c */
uint8_t Joystick (void);

/* primitivas/PR-SW.c */
uint8_t Teclas (void);

/* Primitivas/PR-OLED.c */
void OLED (uint8_t);

/* Primitivas/PR-UART0.c */
void Mensajes (void);
void Transmitir (char *);

/* Primitivas/PR-ADC.c */
void ADC_CLKDIV_1 (void);
void ADC_CLKDIV_2 (void);
void ADC_CLKDIV_3 (void);

/* Primitivas/Beep.c */
void Buzz_Beep (void);

/* Aplicacion/mde.c */
void MDE (void);
void Modo_actual (uint8_t);

/* Aplicacion/Metronomo.c */
void Metronomo (void);

/* Aplicacion/fft.c */
void Analizar (void);
float Interpretar (void);

/* Aplicacion/Comparar.c */
void Comparar (void);

/* Aplicacion/EnviarTrama.c */
void EnviarTrama (uint8_t);

/* Aplicacion/Nota_deseada.c */
void Actualizar_Nota_deseada (void);

#endif /* EA_BASEBOARD_H_ */
