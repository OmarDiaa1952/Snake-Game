#pragma once
#ifndef BSP_H
#define BSP_H


//https://www.ti.com/product/LM3S6965
//https://www.ti.com/lit/ds/symlink/lm3s6965.pdf
//page 16	list of registers
//page 103	peripheral registers
//page 185	system control registers
//page 432	UART registers
//page 440	UART register map

//page 185 system control register map
typedef struct SystemRegStruct
{
	unsigned DID0;		//Device identification 0
	unsigned DID1;		//Device identification 0
	unsigned DC0;		//Device Capabilities 0
	unsigned reserved0;
	unsigned DC1;		//Device Capabilities 1
	unsigned DC2;		//Device Capabilities 2
	unsigned DC3;		//Device Capabilities 3
	unsigned DC4;		//Device Capabilities 4
	unsigned reserved1[4];
	unsigned PBORCTL;	//Brown-out reset control
	unsigned LDOPCTL;	//LDO power control
	unsigned reserved2[2];
	unsigned SRCR0;		//Software reset control 0
	unsigned SRCR1;		//Software reset control 1
	unsigned SRCR2;		//Software reset control 2
	unsigned reserved3;
	unsigned RIS;		//Raw interrupt status
	unsigned IMC;		//Interrupt mask control
	unsigned MISC;		//Masked interrupt status and clear
	unsigned RESC;		//Reset cause
	unsigned RCC;		//Run-mode clock configuration
	unsigned PLLCFG;	//XTAL to PLL translation
	unsigned reserved4[2];
	unsigned RCC2;		//Run-mode clock configuration 2
	unsigned reserved5[35];
	unsigned RCGC0;		//Run mode clock gating control register 0
	unsigned RCGC1;		//Run mode clock gating control register 1
	unsigned RCGC2;		//Run mode clock gating control register 2
	unsigned reserved6;
	unsigned SCGC0;		//Sleep mode clock gating control register 0
	unsigned SCGC1;		//Sleep mode clock gating control register 1
	unsigned SCGC2;		//Sleep mode clock gating control register 2
	unsigned reserved7;
	unsigned DCGC0;		//Deep sleep mode clock gating constol register 0
	unsigned DCGC1;		//Deep sleep mode clock gating constol register 1
	unsigned DCGC2;		//Deep sleep mode clock gating constol register 2
	unsigned reserved8[6];
	unsigned DSLPCLKCFG;	//Deep sleep clock configuration
} SystemReg;

//page 440	UART register map
typedef struct UARTRegStruct
{
	unsigned UARTDR;		//data
	unsigned UARTRSR_ECR;	//receive status/error clear
	unsigned reserved0[4];
	unsigned UARTFR;		//flag
	unsigned reserved1;
	unsigned UARTILPR;		//IrDA low-power register
	unsigned UARTIBRD;		//integer baud-rate divisor
	unsigned UARTFBRD;		//fractional baud-rate divisor
	unsigned UARTLCRH;		//line control
	unsigned UARTCTL;		//control
	unsigned UARTIFLS;		//interrupt FIFO level select
	unsigned UARTIM;		//interrupt mask
	unsigned UARTRIS;		//raw interrupt status
	unsigned UARTMIS;		//masked interrupt status
	unsigned UARTICR;		//interrupt clear
	unsigned reserved2[994];
	unsigned UARTPeriphID4;	//peripheral identification 4
	unsigned UARTPeriphID5;	//peripheral identification 5
	unsigned UARTPeriphID6;	//peripheral identification 6
	unsigned UARTPeriphID7;	//peripheral identification 7
	unsigned UARTPeriphID0;	//peripheral identification 0
	unsigned UARTPeriphID1;	//peripheral identification 1
	unsigned UARTPeriphID2;	//peripheral identification 2
	unsigned UARTPeriphID3;	//peripheral identification 3
	unsigned UARTPCellD3;	//primecell identification 3
} UARTReg;

//page 103 peripheral registers
typedef struct PeriphRegStruct
{
	unsigned reserved0[4];
	unsigned STCTRL;	//SysTick Control and Status Register
	unsigned STRELOAD;	//SysTick Reload Value Register
	unsigned STCURRENT;	//Systick current value register
	unsigned reserved1[57];
	unsigned EN0;	//Interrupt 0-31 set enable
	unsigned EN1;	//Interrupt 32-43 set enable
	unsigned reserved2[30];
	unsigned DIS0;	//Interrupt 0-31 clear enable
	unsigned DIS1;	//Interrupt 32-43 clear enable
	unsigned reserved3[30];
	unsigned PEND0;	//Interrupt 0-31 set pending
	unsigned PEND1;	//Interrupt 32-43 set pending
	unsigned reserved4[30];
	unsigned UNPEND0;	//Interrupt 0-31 clear pending
	unsigned UNPEND1;	//Interrupt 32-43 clear pending
	unsigned reserved5[30];
	unsigned ACTIVE0;	//Interrupt 0-31 active bit
	unsigned ACTIVE1;	//Interrupt 32-43 active bit
	unsigned reserved6[62];
	unsigned PRI0;	//Interrupt 0-3 priority
	unsigned PRI1;	//Interrupt 4-7 priority
	unsigned PRI2;	//Interrupt 8-11 priority
	unsigned PRI3;	//Interrupt 12-15 priority
	unsigned PRI4;	//Interrupt 16-19 priority
	unsigned PRI5;	//Interrupt 20-23 priority
	unsigned PRI6;	//Interrupt 24-27 priority
	unsigned PRI7;	//Interrupt 28-31 priority
	unsigned PRI8;	//Interrupt 32-35 priority
	unsigned PRI9;	//Interrupt 36-39 priority
	unsigned PRI10;	//Interrupt 40-43 priority
	unsigned reserved7[565];
	unsigned CPUID;	//CPU ID base
	unsigned INTCTRL;	//Interrupt control and state
	unsigned VTABLE;	//Vector table offset
	unsigned APINT;	//Application interrupt and reset control
	unsigned SYSCTRL;	//System control
	unsigned CFGCTRL;	//Configuration and control
	unsigned SYSPRI1;	//System handler priority 1
	unsigned SYSPRI2;	//System handler priority 2
	unsigned SYSPRI3;	//System handler priority 3
	unsigned SYSHNDCTRL;	//System handler control and state
	unsigned FAULTSTAT;	//Configurable fault status
	unsigned HFAULTSTAT;	//Hard fault status
	unsigned reserved8;
	unsigned MMADDR;	//Memory management fault address
	unsigned FAULTADDR;	//Bus fault address,
	unsigned reserved9[21];
	unsigned MPUTYPE;	//Memory protection unit (MPU) type
	unsigned MPUCTRL;	//MPU control
	unsigned MPUNUMBER;	//MPU region number
	unsigned MPUBASE;	//MPU region base address
	unsigned MPUATTR;	//MPU region attribute and size
	unsigned MPUBASE1;	//MPU region base address alias 1
	unsigned MPUATTR1;	//MPU region attribute and size alias 1
	unsigned MPUBASE2;	//MPU region base address alias 2
	unsigned MPUATTR2;	//MPU region attribute and size alias 2
	unsigned MPUBASE3;	//MPU region base address alias 3
	unsigned MPUATTR3;	//MPU region attribute and size alias 3
	unsigned reserved10[81];
	unsigned SWTRIG;	//Software trigger interrupt
} PeriphReg;


extern volatile SystemReg *const system;
extern volatile PeriphReg *const periph;
extern volatile UARTReg *const UART0;
extern volatile UARTReg *const UART1;
extern volatile UARTReg *const UART2;
void uart_init();
void uart_putc(char c);
char uart_getc(void);
void systick_init(int period);
#define PendSV_setPriority(PRIORITY)	(periph->SYSPRI3&=0xFF1FFFFF, periph->SYSPRI3|=(PRIORITY)<<21)
#define PendSV_trigger()	(periph->INTCTRL|=1<<28)
#define PendSV_isPending()	(periph->INTCTRL>>28&1)
#define interrupts_disable()	asm("cpsid i")
#define interrupts_enable()		asm("cpsie i")

#ifdef BSP_IMPL
volatile SystemReg *const system=(volatile SystemReg*)0x400FE000;
volatile PeriphReg *const periph=(volatile PeriphReg*)0xE000E000;
volatile UARTReg *const UART0=(volatile UARTReg*)0x4000C000;
volatile UARTReg *const UART1=(volatile UARTReg*)0x4000D000;
volatile UARTReg *const UART2=(volatile UARTReg*)0x4000E000;
void uart_init()
{
	//https://www.ti.com/lit/ds/symlink/lm3s6965.pdf
	//UART init page 439
	system->RCGC1|=1;//enable UART0 clock
	UART0->UARTCTL&=~1u;//disable UART0 page 454

	//baud int & frac parts
	UART0->UARTIBRD=104, UART0->UARTFBRD=11;//9600
	//UART0->UARTIBRD=10, UART0->UARTFBRD=54;//115200

	UART0->UARTLCRH=0x00000060;//{SPS=0, WLEN=0b11, FEN=0, STP2=0, EPS=0, PEN=0, BRK=0} page 451
	UART0->UARTCTL|=1;//enable UART0 page 454
}
void uart_putc(char c)
{
	while(UART0->UARTFR&0x20);
	UART0->UARTDR=c;
}
char uart_getc(void)
{
	while(!(UART0->UARTFR&0x40));
	return UART0->UARTDR&0xFF;
}
void systick_init(int period)
{
	//SysTick init page 103
	periph->STRELOAD=period;//1/256th of max period
	periph->STCTRL|=7;//{CLK_SRC=1, INTEN=1, ENABLE=1}
}
#endif

#endif
