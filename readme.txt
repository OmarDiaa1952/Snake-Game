SimpleRTOS

An implementation of a very simple RTOS.


Build:
After installing the arm-none-eabi toolchain, run:

	make build


Run:
After installing the arm-none-eabi toolchain, run:

	make run



Installing the arm-none-eabi toolchain:

1. Download the arm-none-eabi toolchain from:
https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/downloads

2. Install dependencies:

	sudo apt-get install libpython3.6
	sudo apt-get install libncursesw5
	export arm-none-eabi/bin to path

3. For emulation, install qemu:

	sudo apt-get install qemu

4. For cross-debugging, it is recommended to use VS Code with the provided launch.json

