//https://embeddedfreak.wordpress.com/2009/08/10/cortex-m3-systick-peripheral/
void uart_init();
void print(const char *str);
int print_ihex(unsigned n);
void panic(void);

void handler_Reset(void);
void handler_NMI(void);
void handler_HardFault(void);
void handler_MemManage(void);
void handler_BusFault(void);
void handler_UsageFault(void);
void handler_SVC(void);
void handler_DebugMon(void);
void handler_PendSV(void);
void handler_SysTick(void);
#if 0
__attribute__((section(".vectors"))) void vector_table(void)
{
	handler_Reset();
	handler_undefined();
}
void handler_undefined(void)
{
	for(;;);
}
void handler_software_interrupt(void)
{
	for(;;);
}
#endif
#if 1
unsigned long __sys_stack[256];
__attribute__((section(".isr_vector"))) void (*const vector_table[])(void)=
{
	(void (*)(void))((unsigned long)__sys_stack + sizeof(__sys_stack)),
	//&__stack_top,		//The initial stack pointer
	handler_Reset,		//The reset handler
	handler_NMI,		//The NMI handler
	handler_HardFault,	//The hard fault handler
	handler_MemManage,	//The MPU fault handler
	handler_BusFault,	//The bus fault handler
	handler_UsageFault,	//The usage fault handler
	0,					//Reserved
	0,					//Reserved
	0,					//Reserved
	0,					//Reserved
	handler_SVC,		//SVCall handler
	handler_DebugMon,	//Debug monitor handler
	0,					//Reserved
	handler_PendSV,		//The PendSV handler
	handler_SysTick,	//The SysTick handler
};
#endif
#if 1
extern unsigned _etext;
extern unsigned _data;
extern unsigned _edata;
extern unsigned _bss;
extern unsigned _ebss;
extern unsigned __stack_top;
#endif
int main(void);
void handler_Reset(void)
{
#if 1
	unsigned *src, *dst;

	//Copy the data segment initializers from flash to SRAM.
	src=&_etext;
	dst=&_data;
	for(;dst<&_edata;++src, ++dst)
		*dst=*src;

	//Zero fill the BSS section
#if 0
	__asm(
		"    ldr     r0, =_bss\n"
		"    ldr     r1, =_ebss\n"
		"    mov     r2, #0\n"
		"    .thumb_func\n"
		"zero_loop:\n"
		"        cmp     r0, r1\n"
		"        it      lt\n"
		"        strlt   r2, [r0], #4\n"
		"        blt     zero_loop"
	);
#else
	for(dst=&_ebss;dst<&_bss;++dst)
		*dst=0;
#endif
	//asm("LDR sp, =__stack_top");
#endif
	uart_init();
	int ret=main();
	print("Main returned ");
	print_ihex(ret);
	for(;;);
}
void handler_NMI(void)
{
	panic();
	print("NMI handler\n");//what is NMI?
	for(;;);
}
void handler_HardFault(void)
{
	asm("push {r4-r11}");
	panic();
	asm("pop {r4-r11}");
	print("Hard fault\n");
	for(;;);
}
void handler_MemManage(void)
{
	panic();
	print("Memory protection unit (MPU) fault\n");
	for(;;);
}
void handler_BusFault(void)
{
	panic();
	print("Bus fault\n");
	for(;;);
}
void handler_UsageFault(void)
{
	panic();
	print("Usage fault\n");
	for(;;);
}
void handler_SVC(void)
{
	panic();
	print("SVCall handler\n");
	for(;;);
}
void handler_DebugMon(void)
{
	panic();
	print("Debug monitor handler\n");
	for(;;);
}
