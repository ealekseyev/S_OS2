#!/bin/bash
# compiles all ASM files specified in ASM_LINKLIST,
# compiles c kernel,
# links everything and generates bootable kernel.

ASM_LINKLIST=("kernel_launch.s" "lib/kern_io/ports/ports_io.s")

strindex() { 
  x="${1%%$2*}"
  [[ "$x" = "$1" ]] && echo -1 || echo "${#x}"
}

for val in ${ASM_LINKLIST[@]}; do
    suffix=$(strindex $val ".s")
    base_path=$(echo $val | cut -c 1-$suffix)
    base_name=$(echo $base_path | rev | cut -d'/' -f-1 | rev)
    echo "compiling $base_name.s"
    #nasm -f elf32 "$base_path.s" -o obj/"$base_name.o"
done
gcc -m32 -c kernel.c -o obj/kernel.o -w
ld -m elf_i386 -T link.ld -o boot/$1 obj/*.o