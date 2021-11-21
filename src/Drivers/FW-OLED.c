/*
 * FW-OLED.c
 *
 *  Created on: 24/10/2014
 *      Author: Usuario
 */

#include "EA_BaseBoard.h"
#include "font5x7.h"


/******************************************************************************
 * Local variables
 *****************************************************************************/

/*
 * The SSD1305 doesn't support reading from the display memory when using
 * serial mode (only parallel mode). Since it isn't possible to write only
 * one pixel to the display (a minimum of one column, 8 pixels, is always
 * wriiten) a shadow framebuffer is needed to keep track of the display
 * data.
 */
uint8_t shadowFB[SHADOW_FB_SIZE];
static uint8_t const  font_mask[8] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
extern const unsigned char font5x7[][8];


/******************************************************************************
 * Local Functions
 *****************************************************************************/

void writeCommand (uint8_t command)
{
	//IOCLR = 0x000000ff;			// No se que es
	//IOSET = RD_IN;//RD=1			// Es el Enable para micros de interfaz 8080 o 6800, para nuestro caso esta conectado a masa
	SetPIN (Oled_dc, OFF);			// IOCLR = DC_IN;//RS=0 (Para que el driver sepa que recibe comandos)
	SetPIN (Oled_ssel, OFF);		// IOCLR = CS_IN;//CS=0 (Marco el comienzo de la transmicion)
	//IOCLR = WR_IN;//W_R=0			// Tambien es para micros 8080 o 6800, esta conectado a masa

	SSP_transfer_byte (command);	// Ahora transmito "command" por SPI via SSP1

	//IOSET = WR_IN;//W=1
	SetPIN (Oled_ssel, ON);			// IOSET = CS_IN;//CS=1 (Marco el fin de la transmicion)
	//IOCLR = RD_IN;//RD=0			//
 }


void writeData (uint8_t data)
{

	//IOCLR = 0x000000ff;
	SetPIN(Oled_dc, ON);			//IOSET = DC_IN;//RS=1 (Para que el driver sepa que recibe datos)
	SetPIN(Oled_ssel, OFF);			//IOCLR = CS_IN;//CS=0 (Marco el comienzo de la transmicion)
	//IOSET = RD_IN;//RD=1
	//IOCLR = WR_IN;//W_R=0

	SSP_transfer_byte (data);	// Ahora transmito "data" por SPI via SSP1

	//IOSET = WR_IN;//W_R=1
	SetPIN(Oled_ssel, ON);			//IOSET = CS_IN;//CS_1=1 (Marco el fin de la transmicion)
}


uint16_t SSP_recive_byte (void)
{
	return ((uint16_t) (SSP1DR & 0xFFFF));
}


void SSP_transfer_byte (uint8_t byte_out)
{
	volatile uint32_t aux=0;

	while ((SSP1SR & (uint32_t ) (1<<RNE)) == 1) 	// Leo Dataregister para vaciar el RX FIFO
	{
		aux = (uint32_t) SSP_recive_byte ();
	}

	SSP1ICR=(uint32_t) 0x11;							// Limpio los flags de interrupciones

	while ( (SSP1SR & ((uint32_t) (1<<TNF))) == 0 || (SSP1SR & ((uint32_t) (1<<BSY))) == 1);

	SSP1DR = ((uint16_t) byte_out & 0xFFFF);			// Escribo en Dataregister el dato a mandar al TX FIFO

	while ((SSP1SR & (uint32_t) (1<<BSY)) == 1);
}



///////////////////////////////////////////////////////////////////////////////
//							FUNCIONES DE EMBEDDED ARTISTS					 //
///////////////////////////////////////////////////////////////////////////////


/******************************************************************************
 *
 * Description:
 *    Draw one pixel on the display
 *
 * Params:
 *   [in] x - x position
 *   [in] y - y position
 *   [in] color - color of the pixel
 *
 *****************************************************************************/
void oled_putPixel (uint8_t x, uint8_t y, oled_color_t color)
{
    uint8_t page;
    uint16_t add;
    uint8_t lAddr;
    uint8_t hAddr;
    uint8_t mask;
    uint32_t shadowPos = 0;

    if (x > OLED_DISPLAY_WIDTH) {
        return;
    }
    if (y > OLED_DISPLAY_HEIGHT) {
        return;
    }

    /* page address */
         if(y < 8)  page = 0xB0;
    else if(y < 16) page = 0xB1;
    else if(y < 24) page = 0xB2;
    else if(y < 32) page = 0xB3;
    else if(y < 40) page = 0xB4;
    else if(y < 48) page = 0xB5;
    else if(y < 56) page = 0xB6;
    else            page = 0xB7;

    add = x + X_OFFSET;
    lAddr = 0x0F & add;             // Low address
    hAddr = 0x10 | (add >> 4);      // High address

    // Calculate mask from rows basically do a y%8 and remainder is bit position
    add = y>>3;                     // Divide by 8
    add <<= 3;                      // Multiply by 8
    add = y - add;                  // Calculate bit position
    mask = 1 << add;                // Left shift 1 by bit position

    setAddress(page, lAddr, hAddr); // Set the address (sets the page,
                                    // lower and higher column address pointers)

    shadowPos = (page-0xB0)*OLED_DISPLAY_WIDTH+x;

    if(color > 0)
        shadowFB[shadowPos] |= mask;
    else
        shadowFB[shadowPos] &= ~mask;


    writeData(shadowFB[shadowPos]);
}


/******************************************************************************
 *
 * Description:
 *    Draw a horizontal line
 *
 * Params:
 *   [in] x0 - start x position
 *   [in] y0 - y position
 *   [in] x1 - end y position
 *   [in] color - color of the pixel
 *
 *****************************************************************************/
static void hLine(uint8_t x0, uint8_t y0, uint8_t x1, oled_color_t color)
{
    // TODO: optimize

    uint8_t bak;

    if (x0 > x1)
    {
        bak = x1;
        x1 = x0;
        x0 = bak;
    }

    while(x1 >= x0)
    {
        oled_putPixel(x0, y0, color);
        x0++;
    }
}


/******************************************************************************
 *
 * Description:
 *    Draw a vertical line
 *
 * Params:
 *   [in] x0 - x position
 *   [in] y0 - start y position
 *   [in] y1 - end y position
 *   [in] color - color of the pixel
 *
 *****************************************************************************/
static void vLine(uint8_t x0, uint8_t y0, uint8_t y1, oled_color_t color)
{
    uint8_t bak;

    if(y0 > y1)
    {
        bak = y1;
        y1 = y0;
        y0 = bak;
    }

    while(y1 >= y0)
    {
        oled_putPixel(x0, y0, color);
        y0++;
    }
    return;
}


/******************************************************************************
 *
 * Description:
 *    Draw a line on the display starting at x0,y0 and ending at x1,y1
 *
 * Params:
 *   [in] x0 - start x position
 *   [in] y0 - start y position
 *   [in] x1 - end x position
 *   [in] y1 - end y position
 *   [in] color - color of the line
 *
 *****************************************************************************/
void oled_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, oled_color_t color)
{
    uint16_t   dx = 0, dy = 0;
    uint8_t    dx_sym = 0, dy_sym = 0;
    uint16_t   dx_x2 = 0, dy_x2 = 0;
    uint16_t   di = 0;

    dx = x1-x0;
    dy = y1-y0;


    if(dx == 0)           /* vertical line */
    {
        vLine(x0, y0, y1, color);
        return;
    }

    if(dx > 0)
    {
        dx_sym = 1;
    }
    else
    {
        dx_sym = -1;
    }


    if(dy == 0)           /* horizontal line */
    {
        hLine(x0, y0, x1, color);
        return;
    }


    if(dy > 0)
    {
        dy_sym = 1;
    }
    else
    {
        dy_sym = -1;
    }

    dx = dx_sym*dx;
    dy = dy_sym*dy;

    dx_x2 = dx*2;
    dy_x2 = dy*2;

    if(dx >= dy)
    {
        di = dy_x2 - dx;
        while(x0 != x1)
        {

            oled_putPixel(x0, y0, color);
            x0 += dx_sym;
            if(di<0)
            {
                di += dy_x2;
            }
            else
            {
                di += dy_x2 - dx_x2;
                y0 += dy_sym;
            }
        }
        oled_putPixel(x0, y0, color);
    }
    else
    {
        di = dx_x2 - dy;
        while(y0 != y1)
        {
            oled_putPixel(x0, y0, color);
            y0 += dy_sym;
            if(di < 0)
            {
                di += dx_x2;
            }
            else
            {
                di += dx_x2 - dy_x2;
                x0 += dx_sym;
            }
        }
        oled_putPixel(x0, y0, color);
    }
    return;
}


/******************************************************************************
 *
 * Description:
 *    Draw a char on the display at x,y with selectable color and background
 *
 * Params:
 *   [in] x - x position
 *   [in] y - y position
 *   [in] ch - char to draw
 *   [in] fb - font color
 *   [in] bg - background color
 *
 *****************************************************************************/
uint8_t oled_putChar(uint8_t x, uint8_t y, uint8_t ch, oled_color_t fb, oled_color_t bg)
{
    unsigned char data = 0;
    unsigned char i = 0, j = 0;

    oled_color_t color = OLED_COLOR_BLACK;

    if((x >= (OLED_DISPLAY_WIDTH - 7)) || (y >= (OLED_DISPLAY_HEIGHT - 7)) )
    {
        return 0;
    }

    if( (ch < 0x20) || (ch > 0x7f) )
    {
        ch = 0x20;      /* unknown character will be set to blank */
    }

    ch -= 0x20;
    for(i=0; i<8; i++)
    {
        data = font5x7[ch][i];
        for(j=0; j<6; j++)
        {
            if( (data&font_mask[j])==0 )
            {
                color = bg;
            }
            else
            {
                color = fb;
            }
            oled_putPixel(x, y, color);
            x++;
        }
        y++;
        x -= 6;
    }
    return( 1 );
}


/******************************************************************************
 *
 * Description:
 *    Draw a BIG char on the display at x,y with selectable color and background
 *
 * Params:
 *   [in] x - x position
 *   [in] y - y position
 *   [in] ch - char to draw
 *   [in] fb - font color
 *   [in] bg - background color
 *
 *****************************************************************************/
void oled_putBIGChar(uint8_t x, uint8_t y, uint8_t *ch, oled_color_t fb, oled_color_t bg)
{
//	oled_fillRect(x+15, y+10, 25, 29, bg);
//
//	if(strcmp(ch, "A") == 0)
//	{
//		oled_putChar(x+15, y+10, 'A', fb, bg);
////		oled_line (x+15, y+1,  x+18, y+1,  fb);
////		//oled_line (x+14, y+2,  x+21, y+2,  fb);
////		oled_line (x+14, y+2,  x+18, y+2,  fb);
////		//oled_line (x+13, y+4,  x+21, y+4,  fb);
////		oled_line (x+13, y+3,  x+15, y+3,  fb); oled_line(x+19, y+3, x+22, y+3, fb);
////		oled_line (x+12, y+4,  x+15, y+4,  fb); oled_line(x+19, y+4, x+22, y+4, fb);
////		//oled_line (x+12, y+7,  x+16, y+7,  fb);
////		oled_line (x+11, y+5,  x+14, y+5,  fb);
////		//oled_line (x+10, y+9,  x+16, y+9,  fb);
////		oled_line (x+10, y+6, x+14, y+6, fb);
////		//oled_line (x+9,  y+11, x+15, y+11, fb);
////		oled_line (x+8,  y+7, x+13, y+7, fb);
////		//oled_line (x+8,  y+13, x+14, y+13, fb);
////		oled_line (x+7,  y+8, x+12, y+8, fb);
////		//oled_line (x+7,  y+15, x+13, y+15, fb);
////		oled_line (x+6,  y+9, x+11, y+9, fb);
////		//oled_line (x+6,  y+17, x+12, y+17, fb);
////		oled_line (x+5,  y+10, x+10, y+10, fb);
////		//oled_line (x+5,  y+19, x+25, y+19, fb);
////		oled_line (x+4,  y+11, x+18, y+11, fb);
////		//oled_line (x+4,  y+21, x+25, y+21, fb);
////		oled_line (x+3,  y+12, x+18, y+12, fb);
////		//oled_line (x+3,  y+23, x+25, y+23, fb);
////		oled_line (x+2,  y+13, x+18, y+13, fb);
////		//oled_line (x+2,  y+25, x+25, y+25, fb);
//////		oled_line (x+1,  y+26, x+25, y+25, fb);
//////		oled_line (x+1,  y+27, x+25, y+26, fb);
//////		oled_line (x,    y+28, x+25, y+27, fb);
//	}
}


/******************************************************************************
 *
 * Description:
 *    Draw a line on the display starting at x0,y0 and ending at x1,y1
 *
 * Params:
 *   [in] x - x position
 *   [in] y - y position
 *   [in] pStr - String to draw
 *   [in] fb - Font color
 *   [in] bg - Font background
 *
 *****************************************************************************/
void oled_putString(uint8_t x, uint8_t y, uint8_t *pStr, oled_color_t fb, oled_color_t bg)
{
  while(1)
  {
      if( (*pStr)=='\0' )
      {
          break;
      }
      if( oled_putChar(x, y, *pStr++, fb, bg) == 0 )
      {
        break;
    }
    x += 6;
  }
  return;
}


/******************************************************************************
 *
 * Description:
 *    Fill a rectangle on the display starting at x0,y0 and ending at x1,y1
 *
 * Params:
 *   [in] x0 - start x position
 *   [in] y0 - start y position
 *   [in] x1 - end x position
 *   [in] y1 - end y position
 *   [in] color - color of the rectangle
 *
 *****************************************************************************/
void oled_fillRect(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, oled_color_t color)
{
    uint8_t i = 0;

    if(x0 > x1)
    {
        i  = x0;
        x0 = x1;
        x1 = i;
    }

    if(y0 > y1)
    {
        i  = y0;
        y0 = y1;
        y1 = i;
    }

    if(y0 == y1)
    {
        hLine(x0, y0, x1, color);
        return;
    }

    if(x0 == x1)
    {
        vLine(x0, y0, y1, color);
        return;
    }

    while(y0 <= y1)
    {
        hLine(x0, y0, x1, color);
        y0++;
    }
    return;
}


/******************************************************************************
 *
 * Description:
 *    Clear the entire screen
 *
 * Params:
 *   [in] color - color to fill the screen with
 *
 *****************************************************************************/
void oled_clearScreen(oled_color_t color)
{
	uint8_t i;

	for (i=0; i<97; i++)				// Metodo mas sencillo pero mas lento en el que no es necesario WriteDataLen();
	{
		oled_line(i,0,i,64, color);
	}

//    uint8_t i, j;
//    uint8_t c = 0;
//
//    if (color == OLED_COLOR_WHITE)
//        c = 0xff;
//
//
//    for(i=0xB0;i<0xB8;i++) {            // Go through all 8 pages
//        setAddress(i,0x00,0x10);
//        for (j=0; j<133; j++)			// WriteDataLen(c, 132)/;
//        {
//        	writeData(c);
//        }
//    }
//
//    memset(shadowFB, c, SHADOW_FB_SIZE);
}
