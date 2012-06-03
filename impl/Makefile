INC_PATH = include/
DIRECTIVES = -fno-builtin -nostartfiles -nostdlib -I $(INC_PATH)
FLAGS = -g -m32 -c

all:
	nasm -f aout -g loader.asm -o loader.o 
	nasm -f aout -g asm/interrupts.asm -o asm_interrupts.o
	nasm -f aout -g asm/io.asm -o asm_io.o
	nasm -f aout -g asm/cpuid.asm -o asm_cpuid.o
	
	gcc $(FLAGS) arch/handlers.c -o arch_hanlders.o $(DIRECTIVES)
	gcc $(FLAGS) drivers/crtc6845.c -o crtc6845.o $(DIRECTIVES)
	gcc $(FLAGS) arch/cpuid.c -o arch_cpuid.o $(DIRECTIVES)
	gcc $(FLAGS) klib/klib.c  -o klib_klib.o $(DIRECTIVES)
	gcc $(FLAGS) klib/kvideo.c  -o klib_kvideo.o $(DIRECTIVES)
	gcc $(FLAGS) kernel.c -o kernel.o $(DIRECTIVES) 
	gcc $(FLAGS) lib/string.c -o lib_string.o $(DIRECTIVES)
	
	ld -melf_i386 -T link.ld -o kernel.bin kernel.o loader.o asm_interrupts.o asm_io.o crtc6845.o klib_klib.o klib_kvideo.o arch_hanlders.o lib_string.o asm_cpuid.o arch_cpuid.o
	rm *.o
	mcopy kernel.bin a:/boot -o
clean:
	rm *.o
	rm kernel.bin
	
