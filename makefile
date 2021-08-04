cpy_fetch make/cpy_fetch.sh:
	sh make/cpy_fetch.sh
del_fetch:
	cd ~/Documents/GitHub
	rm -rf S_OS2
	git clone https://github.com/ealekseyev/S_OS2.git
	cd S_OS2
git_push make/git_push.sh:
	sh make/git_push.sh $(COMMIT)
build:
	nasm -f elf32 kernel_launch.s -o obj/kernel_launch.o
	gcc -m32 -c kernel.c -o obj/kernel.o
	ld -m elf_i386 -T link.ld -o boot/$(KERNEL) obj/kernel_launch.o obj/kernel.o
run_intel:
	qemu-system-i386 -kernel $(KERNEL)
run_x86:
	qemu-system-x86_64 -kernel $(KERNEL)
