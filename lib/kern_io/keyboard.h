#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_
#include "../types.h"
#include "ports/ports.h"
#include "../std/memcpy.c"

#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_DATA_PORT   0x60
#define KEYBOARD_BUFLEN      0xFF
static char keymap[] = {
    0, 1
};

// buffer and pointers to keys pressed
static int available_bytes;
static char bytesread[KEYBOARD_BUFLEN] = {};
static char* nextkey = bytesread;

// func prototype
void keyboard_handler(void);

void keyboard_init(void) {
	//idt_init(); should already be initialized
    // TODO: & before func name?
	set_idt_entry(0x21, (uint32_t) keyboard_handler); // 0x21 - keyboard
	reload_idts();
	// 0xFD is 11111101 - enables only IRQ1 (keyboard)
    add_interrupt_mask(0xFD);
}

// TODO: iffy key buffer
void __attribute__((__interrupt__)) keyboard_handler(void) {
	// write EOI
	port_write(0x20, 0x20);

	uint8_t status = port_read(KEYBOARD_STATUS_PORT);
	// Lowest bit of status will be set if buffer is not empty
	if (status & 0x01) {
		int8_t keycode = port_read(KEYBOARD_DATA_PORT);
		if(keycode < 0)
			return;
        // if we've gotten to the end of keystroke buffer, 
        // copy everything back to the beginning
        if(nextkey-bytesread+available_bytes >= KEYBOARD_BUFLEN) {
            memcpy(bytesread, nextkey, available_bytes);
            nextkey = bytesread;
        }
        *(nextkey+available_bytes) = keymap[keycode];
        available_bytes++;
	}
}

// user callable functions 
char keyboard_read() {
    if(available_bytes > 0) {
        char key = (char)*nextkey;
        nextkey++;
        available_bytes--;
        // if all data has been read
        if(available_bytes == 0) {
            nextkey = bytesread;
        }
        return key;
    }
    // else return null
    return 0;
}

int keyboard_available() {
    return available_bytes;
}

void keyboard_flush() {
    nextkey = bytesread;
    available_bytes = 0;
}

#endif