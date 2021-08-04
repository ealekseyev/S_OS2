;;kernel_launch.asm

STACK_SIZE equ 8192
MAGIC_NUM equ 0x1BADB002
FLAGS_NUM equ 0x00
;nasm directive - 32 bit
bits 32
section .text
    ;multiboot spec
    align 4
    dd MAGIC_NUM                 ;magic
    dd FLAGS_NUM                 ;flags
    dd - (MAGIC_NUM + FLAGS_NUM) ;checksum. m+f+c should be zero

global start
extern kmain	                 ;kmain is defined in the c file

start:
    cli 			        ;block interrupts
    mov esp, stack_space	;set stack pointer
    call kmain
    hlt		 	            ;halt the CPU

section .bss
    resb STACK_SIZE		    ;8KB for stack
    stack_space: