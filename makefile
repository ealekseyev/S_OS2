cpy_fetch make/cpy_fetch.sh:
	bash make/cpy_fetch.sh
del_fetch:
	cd ~/Documents/GitHub
	rm -rf S_OS2
	git clone https://github.com/ealekseyev/S_OS2.git
	cd S_OS2
git_push make/git_push.sh:
	bash make/git_push.sh $(COMMIT)
# compiles ASM, compiles c kernel, linkes all object files
build make/build.sh:
	bash make/build.sh $(KERNEL)
run_intel:
	qemu-system-i386 -kernel $(KERNEL)
run_x86:
	qemu-system-x86_64 -kernel $(KERNEL)
