#include "lib/kern_io/screen.h"
#include "lib/types.h"
#include "lib/kern_io/ports/ports.h"
#include "lib/kern_io/keyboard.h"

void kmain() {
	screen_clear(screen_colorgen(BLACK, GREEN));
	screen_writestr("  <- key pressed", screen_colorgen(BLACK, GREEN));
	idt_init();
	keyboard_init();
	while(1) {
		while(keyboard_available() == 0);
		screen_writechar(keyboard_read(), GREEN);
	}
}