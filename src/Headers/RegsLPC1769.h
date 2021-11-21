/*
===============================================================================
RegsLPC1769.h
===============================================================================
*/
#ifndef REGS_H_
#define REGS_H_

// Tipos de Datos --------------------------------------------------------------------------------------------------------
#define		__RW				volatile
typedef 	unsigned int 		uint32_t;		// Rango: (0; +32767)
typedef 	unsigned short 		uint16_t;		// Rango: (0; +32767)
typedef 	unsigned char 		uint8_t;		// Rango: (0; +255)
typedef		signed int			int16_t;		// Rango: (−32767; +32767)
typedef		signed long			int32_t;		// Rango: (−2147483647; +2147483647)
typedef 	__RW uint32_t 		registro_t; 	 // Defino un tipo 'registro'.


// REGISTROS -------------------------------------------------------------------------------------------------------------
#define		PINSEL		( ( registro_t  * ) 0x4002C000UL )		// Direccion de inicio de los registros PINSEL
#define		PINMODE		( ( registro_t  * ) 0x4002C040UL )		// Direccion de inicio de los registros de modo de los pines del GPIO
#define		GPIO		( ( registro_t  * ) 0x2009C000UL )		// Direccion de inicio de los registros de GPIOs

//  NVIC (Nested Vectored Interrupt Controller)---------------------------------------------------------------------------
#define		ISER		( ( registro_t  * ) 0xE000E100UL )		// Interrupt Set-Enable Registers
#define		ICER		( ( registro_t  * ) 0xE000E180UL )		// Interrupt Clear-Enable Registers

// Registros ISER:
#define		ISER0		ISER[0]
	#define		ISE_ADC			22
	#define		ISE_UART0		5
#define		ISER1		ISER[1]

// Registros ICER:
#define		ICER0		ICER[0]
#define		ICER1		ICER[1]

//  Power Control ----------------------------------------------------------------------------------------------------------
#define 	PCONP	(* ( ( registro_t  * ) 0x400FC0C4UL ))
	//Macros
	#define		PCTIM0		1
	#define		PCSSP1		10
	#define		PCADC		12
	#define		PCI2C2		26
	#define		PCUART0		3

//  Peripheral Clock Selection ----------------------------------------------------------------------------------------------
#define		PCLKSEL		( ( registro_t  * ) 0x400FC1A8UL )

#define		PCLKSEL0	PCLKSEL[0]
	#define		PCLK_TIMER0		2
	#define		PCLK_UART0		6
	#define		PCLK_I2C0		14
	#define		PCLK_SSP1		20
	#define		PCLK_ADC		24
#define		PCLKSEL1	PCLKSEL[1]
	#define		PCLK_I2C2		20

#define		CCLK_4			00
#define		CCLK			01
#define		CCLK_2			10
#define		CCLK_8			11

//  Interrupciones Externas  ------------------------------------------------------------------------------------------------
#define		EXTINT 		( * ( ( registro_t  * ) 0x400FC140UL ) )
	#define		EINT0		0
	#define		EINT1		1
	#define		EINT2		2
	#define		EINT3		3

#define		EXTMODE 	( * ( ( registro_t  * ) 0x400FC148UL ) )
	#define		EXTMODE0	0
	#define		EXTMODE1	1
	#define		EXTMODE2	2
	#define		EXTMODE3	3
#define		EXTPOLAR 	( * ( ( registro_t  * ) 0x400FC14CUL ) )
	#define		EXTPOLAR0	0
	#define		EXTPOLAR1	1
	#define		EXTPOLAR2	2
	#define		EXTPOLAR3	3

// Registro de control del SysTick   ----------------------------------------------------------------------------------------
#define 	SYSTICK		( (registro_t *) 0xE000E010UL )

#define		STCTRL		SYSTICK[ 0 ]
	#define	ENABLE			0
	#define	TICKINT			1
	#define	CLKSOURCE		2
	#define	COUNTFLAG		16
#define		STRELOAD	SYSTICK[ 1 ]
#define		STCURR		SYSTICK[ 2 ]
#define		STCALIB		SYSTICK[ 3 ]

//  Registros del ADC  ------------------------------------------------------------------------------------------------------
#define		AD0CR 		(* ( registro_t  * ) 0x40034000UL )				// A/D Control Register
	#define		SEL				0
	#define		CLKDIV			8
	#define		BURST			16
	#define		PDN				21
	#define		START			24
	#define		EDGE			27

#define		AD0GDR		(* ( registro_t  * ) 0x40034004UL )				// A/D Global Data Register
	#define		RESULT		4
	#define		CHN			24
	#define		OVERRUN		30
	#define		DONE		31

#define		AD0INTEN 	(* ( registro_t  * ) 0x4003400CUL )				// A/D Interrupt Enable Register
	#define		ADINTEN0		0
	#define		ADINTEN1		1
	#define		ADINTEN2		2
	#define		ADINTEN3		3
	#define		ADINTEN4		4
	#define		ADINTEN5		5
	#define		ADINTEN6		6
	#define		ADINTEN7		7
	#define		ADGINTEN		8

#define		AD0DR 		( ( registro_t  * ) 0x40034010UL )				// A/D Data Registers
	#define		AD0DR0		AD0DR[0]
	#define		AD0DR1		AD0DR[1]
	#define		AD0DR2		AD0DR[2]
	#define		AD0DR3		AD0DR[3]
	#define		AD0DR4		AD0DR[4]
	#define		AD0DR5		AD0DR[5]
	#define		AD0DR6		AD0DR[6]
	#define		AD0DR7		AD0DR[7]

	#define		ADSTAT		AD0DR[8]
		#define		DONE4		4
		#define		OVERRUN4	12
	#define		ADTRM		AD0DR[9]


//  Registros del SSP1  -----------------------------------------------------------------------------------------------------
#define		SSP1CR0		(* ( ( registro_t  * ) 0x40030000UL ))			// SSP1 Control Register 0
	#define		DSS				0		//Data Size Select
	#define		FRF				4		//Frame Format
	#define		CPOL			6		//Clock-Out Polarity
	#define		CPHA			7		//Clock-Out Phase
	#define		SCR				8		//Serial Clock Rate

#define		SSP1CR1		(* ( ( registro_t  * ) 0x40030004UL ))			// SSP1 Control Register 1
	#define		LBM				0		//Loop Back Mode
	#define		SSE				1		//SSP Enable
	#define		MS				2		//Master/Slave Mode
	#define		SOD				3		//Slave Output Disable

#define		SSP1DR		(* ( ( registro_t  * ) 0x40030008UL ))			// SSP1 Data Register
	#define		DR_Data			0
#define		SSP1SR		(* ( registro_t  * ) 0x4003000CUL )				// SSP1 Status Register
	#define		TFE				0		//Transmit FIFO Empty
	#define		TNF				1		//Transmit FIFO Not Full
	#define		RNE				2		//Recive FIFO Not Empty
	#define		RFF				3		//Recive DIDO Full
	#define		BSY				4		//Busy
#define		SSP1CPSR	(* ( ( registro_t  * ) 0x40030010UL ))			// SSP1 Clock Prescale Register
	#define		CPSDVSR			0
#define		SSP1IMSC	(* ( ( registro_t  * ) 0x40030014CUL ))			// SSP1 Interrupt Mask Set/Clear Register
	#define		RORIM			0		//Recive Overrun
	#define		RTIM			1		//Recive Timeout
	#define		RXIM			2		//RX half-full
	#define		TXIM			3		//TX half-full
#define		SSP1RIS		(* ( registro_t  * ) 0x40030018UL )				// SSP1 RAW Interrupt Status Register
	#define		RORRIS			0
	#define		RTRIS			1
	#define		RXRIS			2
	#define		TXRIS			3
#define		SSP1MIS		(* ( registro_t  * ) 0x4003001CUL )				// SSP1 Masked Interrupt Status Register
	#define		RORMIS			0
	#define		RTMIS			1
	#define		RXMIS			2
	#define		TXMIS			3
#define		SSP1ICR		(* ( ( registro_t  * ) 0x40030020UL ))			// SSP1 Interrupt Clear Register
	#define		RORIC			0
	#define		RTIC			1
#define		SSP1DMACR	(* ( ( registro_t  * ) 0x40030024UL ))			// SSP1 DMA Control Register
	#define		RXDMAE			0		//Receive DMA Enable
	#define		TXDMAE			1		//Transmit DMA Enable

//  Registros de la UART0  ------------------------------------------------------------------------------------------------------
#define		U0RBR		(* ( ( registro_t  * ) 0x4000C000UL ))		// Si DLAB=0
#define		U0THR		(* ( ( registro_t  * ) 0x4000C000UL ))		// Si DLAB=0
#define		U0DLL		(* ( ( registro_t  * ) 0x4000C000UL ))		// Si DLAB=1
#define		U0DLM		(* ( ( registro_t  * ) 0x4000C004UL ))		// Si DLAB=1
#define		U0IER		(* ( ( registro_t  * ) 0x4000C004UL ))		// Si DLAB=0
	#define		IER_RBR			0x01
	#define		IER_THRE		0x02
	#define 	IER_RLS			0x04
#define		U0IIR		(* ( ( registro_t  * ) 0x4000C008UL ))
	#define 	IIR_PEND		0x01
	#define 	IIR_RLS			0x03
	#define 	IIR_RDA			0x02
	#define		IIR_CTI			0x06
	#define 	IIR_THRE		0x01
#define		U0FCR		(* ( ( registro_t  * ) 0x4000C008UL ))
#define		U0LCR		(* ( ( registro_t  * ) 0x4000C00CUL ))
	#define		Word_Length_sel		0
	#define		Stop_Bit_sel		2
	#define		Parity_en			3
	#define		Parity_sel			4
	#define		Break_Control		6
	#define		DLAB				7
#define		U0LSR		(* ( ( registro_t  * ) 0x4000C014UL ))		// Si DLAB=0
	#define 	LSR_RDR			0x01
	#define 	LSR_OE			0x02
	#define 	LSR_PE			0x04
	#define 	LSR_FE			0x08
	#define 	LSR_BI			0x10
	#define 	LSR_THRE		0x20
	#define 	LSR_TEMT		0x40
	#define 	LSR_RXFE		0x80

#endif /* REGS_H_ */
