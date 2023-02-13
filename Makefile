#steps:
#	(vs code)	make (build)
#	(terminal)	make serve
#	(vs code)	F5 (or make connect in terminal)
#CFLAGS = -Ic:/FreeRTOSv202212.00/FreeRTOS/Source/include -Ic:/FreeRTOSv202212.00/FreeRTOS/Source/portable/MSVC-MingW -Ic:/FreeRTOSv202212.00/FreeRTOS-Plus/VisualStudio_StaticProjects/FreeRTOS-Kernel
build:
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -g -c startup.c -o startup.o
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -g -c system.c -o system.o
	arm-none-eabi-as -mcpu=cortex-m3 -mthumb -g context_switch.s -o context_switch.o
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -g -c main.c -o main.o
	arm-none-eabi-ld -g -T linker_script.ld startup.o system.o context_switch.o main.o -o out.elf
	arm-none-eabi-objcopy -O binary out.elf out.bin
objdump:
	arm-none-eabi-objdump -dr out.elf >objdump.txt


run:
	qemu-system-arm -M lm3s6965evb -m 128M -kernel out.bin -nographic


serve:
	qemu-system-arm -M lm3s6965evb -m 128M -s -S -kernel out.bin -nographic
connect:
	arm-none-eabi-gdb -x gdb.txt
#	file out.elf
#	target remote localhost:1234


clean:
	rm -f startup.o system.o main.o out.elf out.bin

