INC_PATH = include/
DIRECTIVES = -fno-builtin -nostartfiles -nostdlib -I $(INC_PATH)
FLAGS = -Wall -g -m32 -c

all:
	nasm -f aout -g loader.asm -o loader.o 
	nasm -f aout -g asm/interrupts.asm -o asm_interrupts.o
	nasm -f aout -g asm/io.asm -o asm_io.o
	nasm -f aout -g asm/cpuid.asm -o asm_cpuid.o
	
	#System code
	gcc $(FLAGS) arch/handlers.c -o arch_hanlders.o $(DIRECTIVES)
	gcc $(FLAGS) drivers/crtc6845.c -o crtc6845.o $(DIRECTIVES)
	gcc $(FLAGS) arch/cpuid.c -o arch_cpuid.o $(DIRECTIVES)
	gcc $(FLAGS) klib/klib.c  -o klib_klib.o $(DIRECTIVES)
	gcc $(FLAGS) klib/kvideo.c  -o klib_kvideo.o $(DIRECTIVES)
	gcc $(FLAGS) kernel.c -o kernel.o $(DIRECTIVES) 
	gcc $(FLAGS) lib/string.c -o lib_string.o $(DIRECTIVES)
	gcc $(FLAGS) drivers/serial.c -o drivers_serial.o $(DIRECTIVES)
	gcc $(FLAGS) sys/mmu.c -o sys_mmu.o $(DIRECTIVES)
	
	
	#Pic Code
	gcc $(FLAGS) pic/stateMachine.c -o pic_stateMachine.o $(DIRECTIVES)
	gcc $(FLAGS) pic/serialMotors.c -o pic_serialMotors.o $(DIRECTIVES)
	gcc $(FLAGS) pic/pic.c -o pic_pic.o $(DIRECTIVES)
	gcc $(FLAGS) pic/packageBuffer.c -o pic_packageBuffer.o $(DIRECTIVES)
	gcc $(FLAGS) pic/package.c -o pic_package.o $(DIRECTIVES)
	gcc $(FLAGS) pic/serialComm.c -o pic_serialComm.o $(DIRECTIVES)
	
	
	ld -melf_i386 -T link.ld -o kernel.bin loader.o kernel.o asm_interrupts.o asm_io.o crtc6845.o klib_klib.o klib_kvideo.o arch_hanlders.o lib_string.o asm_cpuid.o arch_cpuid.o drivers_serial.o sys_mmu.o pic_serialMotors.o pic_pic.o  pic_stateMachine.o pic_packageBuffer.o pic_package.o pic_serialComm.o
	rm *.o
	mcopy kernel.bin z:/boot -o
clean:
	rm *.o
	rm kernel.bin
	
