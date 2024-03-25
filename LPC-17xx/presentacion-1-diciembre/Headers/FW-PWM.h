#ifndef PWM_H_
#define PWM_H_

#include "RegsLPC1769.h"

void InitPWM (void);
void DutyCiclePWM(void);
#define registro_t __RW uint32_t

#define PWM_FREQ			1000								// en Hz
//#define PWM_FREQ			1000								// en Hz
#define PWM_MAX_DUTY_STEP	255
#define PWM_PRESCALE_NS		(1000000000/(PWM_FREQ*PWM_MAX_DUTY_STEP))	//en ns

//*******************************************************************
//Pines de PWM1 (PINSEL3 - 0x4002 C00C)
#define 	PWM1_1	2,0										//MotorA
#define 	PWM1_2	2,1										//MotorB
#define 	PWM1_3	2,2										//MotorC
#define 	PWM1_4	2,3										//MotorD
#define 	PWM1_5	2,4
#define 	PWM1_6	2,5


// PWM1 register map		Table 445.
//***************************************************************
#define 	IR		(* ( ( registro_t  * ) 0x40018000 ))	//Interrupt Register. The IR can be written to clear interrupts. The IR can be read to identify which of eight possible interrupt sources are pending.
#define 	TCR		(* ( ( registro_t  * ) 0x40018004 ))
#define 	TC		(* ( ( registro_t  * ) 0x40018008 ))
#define 	PR		(* ( ( registro_t  * ) 0x4001800C ))
#define 	PC		(* ( ( registro_t  * ) 0x40018010 ))
#define 	MCR		(* ( ( registro_t  * ) 0x40018014 ))
#define 	MR0		(* ( ( registro_t  * ) 0x40018018 ))
#define 	MR1		(* ( ( registro_t  * ) 0x4001801C ))
#define 	MR2		(* ( ( registro_t  * ) 0x40018020 ))
#define 	MR3		(* ( ( registro_t  * ) 0x40018024 ))
#define 	CCR		(* ( ( registro_t  * ) 0x40018028 ))
#define 	CR0		(* ( ( registro_t  * ) 0x4001802C ))
#define 	CR1		(* ( ( registro_t  * ) 0x40018030 ))
#define 	CR2		(* ( ( registro_t  * ) 0x40018034 ))
#define 	CR3		(* ( ( registro_t  * ) 0x40018038 ))
#define 	MR4		(* ( ( registro_t  * ) 0x40018040 ))
#define 	MR5		(* ( ( registro_t  * ) 0x40018044 ))
#define 	MR6		(* ( ( registro_t  * ) 0x40018048 ))
#define 	PCR		(* ( ( registro_t  * ) 0x4001804C ))
#define 	LER		(* ( ( registro_t  * ) 0x40018050 ))
#define 	CTCR	(* ( ( registro_t  * ) 0x40018070 ))


// Motor Control Pulse Width Modulator (MCPWM) 	Table 454.
//***************************************************************
#define 	MCCON			(* ( ( registro_t  * ) 0x400B8000 ))	//PWM Control Read Address
#define 	MCCON_SET		(* ( ( registro_t  * ) 0x400B8004 ))	//PWM Control Set Address
#define 	MCCON_CLR		(* ( ( registro_t  * ) 0x400B8008 ))	//PWM Control Clear Address
#define 	MCCAPCON		(* ( ( registro_t  * ) 0x400B800C ))	//Capture Control read Address
#define 	MCCAPCON_SET	(* ( ( registro_t  * ) 0x400B8010 ))	//CApture Control set Address
#define 	MCCAPCON_CLR	(* ( ( registro_t  * ) 0x400B8014 ))	//Event Control Clear Address
#define 	MCTC0			(* ( ( registro_t  * ) 0x400B8018 ))	//Timer Counter register, channel 0
#define 	MCTC1			(* ( ( registro_t  * ) 0x400B801C ))	//Timer Counter register, channel 1
#define 	MCTC2			(* ( ( registro_t  * ) 0x400B8020 ))	//Timer Counter register, channel 2
#define 	MCLIM0			(* ( ( registro_t  * ) 0x400B8024 ))	//Limit Register, channel 0
#define 	MCLIM1			(* ( ( registro_t  * ) 0x400B8028 ))	//Limit Register, channel 1
#define 	MCLIM2			(* ( ( registro_t  * ) 0x400B802C ))	//Limit Register, channel 2
#define 	MCMAT0			(* ( ( registro_t  * ) 0x400B8030 ))	//Match register, channel 0
#define 	MCMAT1			(* ( ( registro_t  * ) 0x400B8034 ))	//Match register, channel 1
#define 	MCMAT2			(* ( ( registro_t  * ) 0x400B8038 ))	//Match register, channel 2
#define 	MCDT			(* ( ( registro_t  * ) 0x400B803C ))	//Dead time register
#define 	MCCP			(* ( ( registro_t  * ) 0x400B8040 ))	//Commutation Pattern register
#define 	MCCAP0			(* ( ( registro_t  * ) 0x400B8044 ))	//Capture register, channel 0
#define 	MCCAP1			(* ( ( registro_t  * ) 0x400B8048 ))	//Capture register, channel 1
#define 	MCCAP2			(* ( ( registro_t  * ) 0x400B804C ))	//Capture register, channel 2
#define 	MCINTEN			(* ( ( registro_t  * ) 0x400B8050 ))	//Interrupt Enable Read Address
#define 	MCINTEN_SET		(* ( ( registro_t  * ) 0x400B8054 ))	//Interrupt Enable Set Address
#define 	MCINTEN_CLR		(* ( ( registro_t  * ) 0x400B8058 ))	//Interrupt Enable Clear Address
#define 	MCCNTCON		(* ( ( registro_t  * ) 0x400B805C ))	//Count Control Read Address
#define 	MCCNTCON_SET	(* ( ( registro_t  * ) 0x400B8060 ))	//Count Control Set Address
#define 	MCCNTCOT_CLR	(* ( ( registro_t  * ) 0x400B8064 ))	//Count Control Clear Address
#define 	MCINTF			(* ( ( registro_t  * ) 0x400B8068 ))	//Interrupt Flags Read Address
#define 	MCINTF_SET		(* ( ( registro_t  * ) 0x400B806C ))	//Interrupt Flags Set Address
#define 	MCINTF_CLR		(* ( ( registro_t  * ) 0x400B8070 ))	//Interrupt Flags Clear Address
#define 	MCCAP_CLR		(* ( ( registro_t  * ) 0x400B8074 ))	//Capture Clear Address
//*******************************************************************

//MCPWM Control read address (MCCON - 0x400B 8000) lpc17xx_um.pdf pag. 526
//*******************************************************************
#define 	RUN0	0
#define 	CENTER0	1
#define 	POLA0	2
#define 	DTE0	3
#define 	DISUP0	4
#define 	RUN1	8
#define 	CENTER1	9
#define 	POLA1	10
#define 	DTE1	11
#define 	DISUP1	12
#define 	RUN2	16
#define 	CENTER2	17
#define 	POLA2	18
#define 	DTE2	19
#define 	DISUP2	20
#define 	INVBDC	29
#define 	ACMODE	30
#define 	DCMODE	31
//
//*******************************************************************
//				PWM Interrupt Register 	(PWM1IR - 0x4001 8000)	Table 446
//           NAME		   BIT			FUNCTION							RESET VALUE
#define	PWMMR0Interrupt		0	//  Interrupt flag for PWM match channel 0. 	0
#define	PWMMR1Interrupt 	1 	//  Interrupt flag for PWM match channel 1.		0
#define PWMMR2Interrupt 	2 	//  Interrupt flag for PWM match channel 2. 	0
#define PWMMR3Interrupt 	3 	//  Interrupt flag for PWM match channel 3. 	0
#define PWMCAP0Interrupt	4 	//  Interrupt flag for capture input 0 			0
#define PWMCAP1Interrupt	5	//  Interrupt flag for capture input 1. 		0
//							7:6   - RESERVED, user software should not write ones to reserved bits. The value read from a reserved bit is not defined.
#define PWMMR4Interrupt 	8	//  Interrupt flag for PWM match channel 4. 	0
#define PWMMR5Interrupt 	9	//  Interrupt flag for PWM match channel 5. 	0
#define PWMMR6Interrupt 	10	//  Interrupt flag for PWM match channel 6. 	0
//							31:11 - RESERVED, user software should not write ones to reserved bits. The value read from a reserved bit is not defined.

//*******************************************************************
//				PWM Timer Control Register (PWM1TCR - 0x4001 8004)	Table 447
//           NAME		   BIT			FUNCTION																		RESET VALUE
#define		CounterEnable	0	//	1 The PWM Timer Counter and PWM Prescale Counter are enabled for counting. 			0
								//	0 The counters are disabled.
#define 	CounterReset 	1	//	1 The PWM Timer Counter and the PWM Prescale Counter are synchronously reset on the next positive edge of PCLK.
								//	0 Clear reset.
//							2 	  - RESERVED, user software should not write ones to reserved bits. The value read
#define		PWMEnable		3	//	1 PWM mode is enabled.(counter resets to 1) causes the shadow registers to operate in connection with the Match registers.
								//	Timer mode is enabled (counter resets to 0)
//*******************************************************************
// 				PWM Count control Register (PWM1CTCR - 0x4001 8070)	Table 448.
//           NAME		 		BIT			FUNCTION
// 		Counter/TimerMode		1:0
//	 	 TimerMode   	00 // the TC is incremented when the Prescale Counter matches the Prescale Register.
// 	 	 CounterMode	01 // the TC is incremented on RISING  	edges of the PCAP input selected by bits 3:2.
//	 	 CounterMode 	10 // the TC is incremented on FALLINNG edges of the PCAP input selected by bits 3:2.
//	 	 CounterMode	11 // the TC is incremented on BOTH    	edges of the PCAP input selected by bits 3:2.// 		CountInputSelect		3:2
#define	  	 PCAP10 		00 // When bits 1:0 of this register are not 00, these bits select which PCAP pin which carries the signal used to increment the TC.
#define	 	 PCAP11 		01 //(Other combinations are reserved)
							  //31:4 - Reserved, user software should not write ones to reserved bits. The value read from a

//*******************************************************************
//				Match Control Register (PWM1MCR - address 0x4001 8014)	Table 449: (0 = Feature Disabled )
//      NAME 		BIT			FUNCTION
#define PWMMR0I 	0  // Interrupt on PWMMR0: an interrupt is generated when PWMMR0 matches the value inthe PWMTC.
#define PWMMR0R 	1  // Reset on PWMMR0: the PWMTC will be reset if PWMMR0 matches it. 0
#define PWMMR0S 	2  // Stop on PWMMR0: the PWMTC and PWMPC will be stopped and PWMTCR[0] will be set to 0 if PWMMR0 matches the PWMTC.
#define PWMMR1I 	3  // Interrupt on PWMMR1: an interrupt is generated when PWMMR1 matches the value in the PWMTC.
#define PWMMR1R 	4  // Reset on PWMMR1: the PWMTC will be reset if PWMMR1 matches it. 0
#define PWMMR1S 	5  // Stop on PWMMR1: the PWMTC and PWMPC will be stopped and PWMTCR[0] will be set to 0 if PWMMR1 matches the PWMTC.
#define PWMMR2I 	6  // Interrupt on PWMMR2: an interrupt is generated when PWMMR2 matches the value in the PWMTC.
#define PWMMR2R 	7  // Reset on PWMMR2: the PWMTC will be reset if PWMMR2 matches it. 0
#define PWMMR2S 	8  // Stop on PWMMR2: the PWMTC and PWMPC will be stopped and PWMTCR[0] will be set to 0 if PWMMR2 matches the PWMTC.
#define PWMMR3I 	9  // Interrupt on PWMMR3: an interrupt is generated when PWMMR3 matches the value inthe PWMTC.
#define PWMMR3R 	10 // Reset on PWMMR3: the PWMTC will be reset if PWMMR3 matches it. 0
#define PWMMR3S 	11 // Stop on PWMMR3: The PWMTC and PWMPC will be stopped and PWMTCR[0] will be set to 0 if PWMMR3 matches the PWMTC.
#define PWMMR4I 	12 // Interrupt on PWMMR4: An interrupt is generated when PWMMR4 matches the valuein the PWMTC.
#define PWMMR4R		13 //  Reset on PWMMR4: the PWMTC will be reset if PWMMR4 matches it. 0
#define PWMMR4S     14 // Stop on PWMMR4: the PWMTC and PWMPC will be stopped and PWMTCR[0] will be set to 0 if PWMMR4 matches the PWMTC.
#define	PWMMR5I  	15 // Interrupt on PWMMR5: An interrupt is generated when PWMMR5 matches the value in the PWMTC.
#define	PWMMR5R 	16 // Reset on PWMMR5: the PWMTC will be reset if PWMMR5 matches it.
#define PWMMR5S 	17 // Stop on PWMMR5: the PWMTC and PWMPC will be stopped and PWMTCR[0] will be set to 0 if PWMMR5 matches the PWMTC.
#define PWMMR6I 	18 // Interrupt on PWMMR6: an interrupt is generated when PWMMR6 matches the value inthe PWMTC.
#define PWMMR6R 	19 // Reset on PWMMR6: the PWMTC will be reset if PWMMR6 matches it.
#define PWMMR6S 	20 // Stop on PWMMR6: the PWMTC and PWMPC will be stopped and PWMTCR[0] will be set to 0 if PWMMR6 matches the PWMTC.
 	 	 	 	//  31:21 - Reserved, user software should not write ones
//*******************************************************************
// 	 	 	PWM Capture Control Register (PWM1CCR - 0x4001 8028) 	Table 450:
//      NAME 		   BIT			FUNCTION
#define CAPn0Rising		0	// (Capture)   A synchronously sampled rising edge on the CAPn.0 input will cause CR0 to be loaded with the contents of the TC.
#define CAPn0Falling	1	// (Capture)   A synchronously sampled falling edge on CAPn.0 will cause CR0 to be loaded with the contents of TC.
#define CAPn0Event		2	// (interrupt) A CR0 load due to a CAPn.0 event will generate an interrupt.
#define CAPn1Rising		3	// (Capture)   A synchronously sampled rising edge on the CAPn.1 input will cause CR1 to beloaded with the contents of the TC.
#define CAPn1Falling	4	// (Capture)   A synchronously sampled falling edge on CAPn.1 will cause CR1 to be loaded with the contents of TC.
#define CAPn1Event		5	// (interrupt) A CR1 load due to a CAPn.1 event will generate an interrupt.
//				31:6 - Reserved, user software should not write ones to reserved bits. The value read from a reserved bit is not defined.
//*******************************************************************
//		 	PWM Control Register 		(PWM1PCR -  0x4001 804C)	Table 451:
				//1:0 	Unused Unused, always zero.
#define PWMSEL2 	2 	// 1 Selects DOUBLE edge controlled mode for the PWM2 output.
						// 0 Selects single edge controlled mode for PWM2.
#define PWMSEL3 	3 	// 1 Selects DOUBLE edge controlled mode for the PWM3 output.
						// 0 Selects single edge controlled mode for PWM3.
#define PWMSEL4 	4 	// 1 Selects DOUBLE edge controlled mode for the PWM4 output.
						// 0 Selects single edge controlled mode for PWM4.
#define PWMSEL5 	5 	// 1 Selects DOUBLE edge controlled mode for the PWM5 output.
						// 0 Selects single edge controlled mode for PWM5.
#define PWMSEL6 	6 	// 1 Selects DOUBLE edge controlled mode for the PWM6 output.
						// 0 Selects single edge controlled mode for PWM6.
				  //8:7 - RESERVED, user software should not write ones to reserved bits. The value read from a
#define PWMENA1		9  	// 1 The PWM1 output enabled.
#define PWMENA2		10 	// 1 The PWM2 output enabled.
#define PWMENA3		11 	// 1 The PWM3 output enabled.
#define PWMENA4		12 	// 1 The PWM4 output enabled.
#define PWMENA5		13 	// 1 The PWM5 output enabled.
#define PWMENA6		14	// 1 The PWM6 output enabled.
				  //31:15 Unused Unused, always zero.
//*******************************************************************
//			PWM Latch Enable Register 	(PWM1LER - 0x4001 8050)		Table 452:
//See Section 24.6.4	“PWM Match Control Register (PWM1MCR - 0x4001 8014)”.

#define  EnPWMMa0Latch	0 //	1: allows the last value written to the PWM Match 0 register to be become effective when the timer is next reset by a PWM Match event.
#define  EnPWMMa1Latch	3 //	1: allows the last value written to the PWM Match 1 register to be become effective when the timer is next reset by a PWM Match event.
#define  EnPWMMa2Latch	2 //	1: allows the last value written to the PWM Match 2 register to be become effective when the timer is next reset by a PWM Match event.
#define  EnPWMMa3Latch	3 //	1: allows the last value written to the PWM Match 3 register to be become effective when the timer is next reset by a PWM Match event.
#define  EnPWMMa4Latch	4 //	1:  the last value written to the PWM Match 4 register to be become effective when the timer is next reset by a PWM Match event.
#define  EnPWMMa5Latch	5 //	1: the last value written to the PWM Match 5 register to be become effective when the timer is next reset by a PWM Match event.
#define  EnPWMMa6Latch	6 //	1: the last value written to the PWM Match 6 register to be become effective when the timer is next reset by a PWM Match event.
					  //31:7 - Reserved, user software should not write ones to reserved bits. The value read from a reserved bit is not defined.
//*******************************************************************




#endif /* PWM_H_ */
