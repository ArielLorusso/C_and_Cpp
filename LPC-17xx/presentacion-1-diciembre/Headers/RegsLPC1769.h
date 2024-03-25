#ifndef REGS_H_
#define REGS_H_

#define		__RW				volatile
typedef 	unsigned int 		uint32_t;
typedef 	unsigned short 		uint16_t;
typedef 	unsigned char 		uint8_t;
typedef 	__RW uint32_t 		registro_t;  //!< defino un tipo 'registro'.

///////////////////////////   MACROS PORTS   /////////////////////////////
#define		PORT0		0
#define		PORT1		1
#define		PORT2		2
#define		PORT3		3
#define		PORT4		4

#define		FUNCION_GPIO	0
#define		FUNCION_1		1
#define		FUNCION_2		2
#define		FUNCION_3		3

#define		MODO_0		0
#define		MODO_1		1
#define		MODO_2		2
#define		MODO_3		3

#define		ENTRADA		0
#define		SALIDA		1


//!< GPIO - PORT0
	/*	*						*
		*************************
		*		FIODIR			*	0x2009C000
		*************************
		*		RESERVED		*	0x2009C004
		*************************
		*		RESERVED		*	0x2009C008
		*************************
		*		RESERVED		*	0x2009C00C
		*************************
		*		FIOMASK			*	0x2009C010
		*************************
		*		FIOPIN			*	0x2009C014
		*************************
		*		FIOSET			*	0x2009C018
		*************************
		*		FIOCLR			*	0x2009C01C
		*************************
		*						*
		*						*
	*/



// REGISTROS ------------------------------------------------------------------------------------------------------------------------
#define		PINSEL		( ( registro_t  * ) 0x4002C000UL )		//!< Direccion de inicio de los registros PINSEL
#define		PINMODE		( ( registro_t  * ) 0x4002C040UL )		//!< Direccion de inicio de los registros de modo de los pines del GPIO
//#define		GPIO		( ( registro_t  * ) 0x2009C000UL )		//!< Direccion de inicio de los registros de GPIOs
//Ajustado al archivo RegsLPC17xx.h
#define		GPIOs		( ( registro_t  * ) 0x2009C000UL )		//!< Direccion de inicio de los registros de GPIOs

// 0xE000E010UL: Registro de control del SysTick:
#define 	SYSTICK		( (registro_t *) 0xE000E010UL )

#define		STCTRL		SYSTICK[ 0 ]
	#define	ENABLE			0
	#define	TICKINT			1
	#define	CLKSOURCE		2
	#define	COUNTFLAG		16
#define		STRELOAD	SYSTICK[ 1 ]
#define		STCURR		SYSTICK[ 2 ]
#define		STCALIB		SYSTICK[ 3 ]

#define TICKINT_ON    STCTRL |= 0x00000002 // pongo en 1  el bit 1 del STCTRL Hablito   interr del Systick
#define TICKINT_OFF   STCTRL &= 0xFFFFFFFD // pongo en 0  el bit 1 del STCTRL Deshablito interr del Systick

//  Power Control for Peripherals register (PCONP - 0x400F C0C4) [pag. 62 user manual LPC1769]
// 0x400FC0C4UL : Direccion de inicio del registro de habilitación de dispositivos:
#define 	PCONP	(* ( ( registro_t  * ) 0x400FC0C4UL ))

// Peripheral Clock Selection registers 0 and 1 (PCLKSEL0 -0x400F C1A8 and PCLKSEL1 - 0x400F C1AC) [pag. 56 user manual]
// 0x400FC1A8UL : Direccion de inicio de los registros de seleccion de los CLKs de los dispositivos:
#define		PCLKSEL		( ( registro_t  * ) 0x400FC1A8UL )
//!< Registros PCLKSEL
#define		PCLKSEL0	PCLKSEL[0]
#define		PCLKSEL1	PCLKSEL[1]



/*
 * AJUSTES PARA USO DE UARTs
 *
 * La version original de este archivo no tenia los recursaos necesarios para utilizar las UARTS
 * Tuvimos que agregar los recursos que sí estaban en el archivo "RegsLPC17xx.h" y ajustar para compatibilizar la informacion
 *
 * Lo siguiente es lo agregado para usar las UARTS
 *
 */

//!< ///////////////////   UART0   //////////////////////////
//!< 0x4000C000UL : Registro de control de la UART0:
#define		UART0	( (__RW uint32_t *) 0x4000C000UL )

//!< Registros de la UART0:
#define		U0THR		UART0[0]
#define		U0RBR		UART0[0]
#define		U0DLL		UART0[0]

#define		U0DLM		UART0[1]
#define		U0IER		UART0[1]

#define		U0IIR		((__R uint32_t *)UART0)[2]
#define		U0FCR		((__W uint32_t *)UART0)[2]

#define		U0LCR		UART0[3]
//!< posición 4 no definida [consultar pag. 300 user manual LPC1769]
#define		U0LSR		UART0[5]
//!< posición 6 no definida [consultar pag. 300 user manual LPC1769]
#define		U0SCR		UART0[7]

//!< ///////////////////   UART1   //////////////////////////
//!< 0x40010000UL : Registro de control de la UART1:
#define		UART1	( (__RW uint32_t *) 0x40010000UL )

//!< Registros de la UART1:
#define		U1THR		UART1[0]
#define		U1RBR		UART1[0]
#define		U1DLL		UART1[0]

#define		U1DLM		UART1[1]
#define		U1IER		UART1[1]

#define		U1IIR		UART1[2]
#define		U1FCR		UART1[2]

#define		U1LCR		UART1[3]
#define		U1MCR		UART1[4]
#define		U1LSR		UART1[5]
#define		U1MSR		UART1[6]
#define		U1SCR		UART1[7]

//!< //////////BITS DE ANALISIS para todas las UARTs   ////////////////////
#define 	IER_RBR		0x01
#define 	IER_THRE	0x02
#define 	IER_RLS		0x04

#define 	IIR_PEND	0x01
#define 	IIR_RLS		0x06
#define 	IIR_RDA		0x04
#define 	IIR_CTI		0x0C
#define 	IIR_THRE	0x02

#define 	LSR_RDR		0x01
#define 	LSR_OE		0x02
#define 	LSR_PE		0x04
#define 	LSR_FE		0x08
#define 	LSR_BI		0x10
#define 	LSR_THRE	0x20
#define 	LSR_TEMT	0x40
#define 	LSR_RXFE	0x80

//!< macros útiles para UARTs
#define		U0RDR		(U0LSR & LSR_RDR)
#define		U0THRE		((U0LSR & LSR_THRE) >>5)
#define		U1RDR		(U1LSR & LSR_RDR)
#define		U1THRE		((U1LSR & LSR_THRE) >>5)


/*
 * AJUSTES PARA USO DE LOS TIMERS
 * Traido de "RegsLPC17xx.h"
 *
 */

//!< ///////////////////   TIMERS   /////////////////////////////
//!< 0x40004000UL : Direccion de inicio de los registros del Timer0
#define		TIMER0		( (__RW uint32_t *) 0x40004000UL )
//!< 0x40008000UL : Direccion de inicio de los registros del Timer1
#define		TIMER1		( (__RW uint32_t *) 0x40008000UL )
//!< 0x40090000UL : Direccion de inicio de los registros del Timer2
#define		TIMER2		( (__RW uint32_t *) 0x40090000UL )
//!< 0x40094000UL : Direccion de inicio de los registros del Timer3
#define		TIMER3		( (__RW uint32_t *) 0x40094000UL )

#define		T0IR		TIMER0[0]
#define		T0TCR		TIMER0[1]
#define		T0TC		TIMER0[2]
#define		T0PR		TIMER0[3]
#define		T0PC		TIMER0[4]
#define		T0MCR		TIMER0[5]
#define		T0MR0		TIMER0[6]
#define		T0MR1		TIMER0[7]
#define		T0MR2		TIMER0[8]
#define		T0MR3		TIMER0[9]
#define		T0CCR		TIMER0[10]
#define		T0CR0		TIMER0[11]
#define		T0CR1		TIMER0[12]
#define		T0EMR		TIMER0[15]
#define		T0CTCR		TIMER0[28]

#define		T1IR		TIMER1[0]
#define		T1TCR		TIMER1[1]
#define		T1TC		TIMER1[2]
#define		T1PR		TIMER1[3]
#define		T1PC		TIMER1[4]
#define		T1MCR		TIMER1[5]
#define		T1MR0		TIMER1[6]
#define		T1MR1		TIMER1[7]
#define		T1MR2		TIMER1[8]
#define		T1MR3		TIMER1[9]
#define		T1CCR		TIMER1[10]
#define		T1CR0		TIMER1[11]
#define		T1CR1		TIMER1[12]
#define		T1EMR		TIMER1[15]
#define		T1CTCR		TIMER1[28]

#define		T2IR		TIMER2[0]
#define		T2TCR		TIMER2[1]
#define		T2TC		TIMER2[2]
#define		T2PR		TIMER2[3]
#define		T2PC		TIMER2[4]
#define		T2MCR		TIMER2[5]
#define		T2MR0		TIMER2[6]
#define		T2MR1		TIMER2[7]
#define		T2MR2		TIMER2[8]
#define		T2MR3		TIMER2[9]
#define		T2CCR		TIMER2[10]
#define		T2CR0		TIMER2[11]
#define		T2CR1		TIMER2[12]
#define		T2EMR		TIMER2[15]
#define		T2CTCR		TIMER2[28]

#define		T3IR		TIMER3[0]
#define		T3TCR		TIMER3[1]
#define		T3TC		TIMER3[2]
#define		T3PR		TIMER3[3]
#define		T3PC		TIMER3[4]
#define		T3MCR		TIMER3[5]
#define		T3MR0		TIMER3[6]
#define		T3MR1		TIMER3[7]
#define		T3MR2		TIMER3[8]
#define		T3MR3		TIMER3[9]
#define		T3CCR		TIMER3[10]
#define		T3CR0		TIMER3[11]
#define		T3CR1		TIMER3[12]
#define		T3EMR		TIMER3[15]
#define		T3CTCR		TIMER3[28]


//!< ///////////////////   NVIC   //////////////////////////
//!< Nested Vectored Interrupt Controller (NVIC)
//!< 0xE000E100UL : Direccion de inicio de los registros de habilitación (set) de interrupciones en el NVIC:
#define		ISER		( (__RW uint32_t *) 0xE000E100UL )
//!< 0xE000E180UL : Direccion de inicio de los registros de deshabilitacion (clear) de interrupciones en el NVIC:
#define		ICER		( (__RW uint32_t *) 0xE000E180UL )

//!< Registros ISER:
#define		ISER0		ISER[0]
#define		ISER1		ISER[1]

//!< Registros ICER:
#define		ICER0		ICER[0]
#define		ICER1		ICER[1]


#endif
