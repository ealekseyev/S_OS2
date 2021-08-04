#include "../../types.h"
#include "../screen.h"
#include "ports_io.s"

#define IDT_SIZE 256 // 256 idt gates

typedef struct __attribute__((__packed__)) {
	uint16_t low_offset: 16;
	uint16_t selector: 16;
	uint8_t zero: 8;
	uint8_t type_flags: 8;
	uint16_t high_offset: 16;
} idt_t;

// global idt table
static idt_t global_idt[IDT_SIZE];
static uint8_t interrupt_mask = 0xFF; // all ones, open interrupts are 0

// extern prototypes - assembly
extern void port_write(uint16_t port_num, uint8_t data);
extern uint8_t port_read(uint16_t port_num);
extern void load_idt(uint32_t ptr);
extern void kb_handler(void);

void set_idt_entry(uint8_t gate_num, uint32_t handler_addr) {
	global_idt[gate_num].low_offset = handler_addr & 0xffff;
	global_idt[gate_num].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	global_idt[gate_num].zero = 0;
	global_idt[gate_num].type_flags = 0x8e; /* INTERRUPT_GATE */
	global_idt[gate_num].high_offset = (handler_addr >> 16) & 0xffff;
}

void reload_idts() {
	uint32_t idt_ptr[2];
	idt_ptr[0] = (sizeof (idt_t) * IDT_SIZE) + (((uint32_t)global_idt & 0xffff) << 16);
	idt_ptr[1] = (uint32_t) global_idt >> 16;
	load_idt(idt_ptr[0]);
}
void add_interrupt_mask(uint8_t interrupts) {
	interrupt_mask = interrupt_mask & interrupts; // appends the zeroes (interrupts)
	port_write(0x21 , interrupt_mask);
}

void set_interrupt_mask(uint8_t interrupts) {
	interrupt_mask = interrupts;
	port_write(0x21 , interrupt_mask);
}

void idt_init(void) {
	/* populate IDT entry of keyboard's interrupt */
	//set_idt_entry(0x21, keyboard_handler_address);

	/*     Ports
	*	 PIC1	PIC2
	*Command 0x20	0xA0
	*Data	 0x21	0xA1
	*/

	/* ICW1 - begin initialization */
	port_write(0x20 , 0x11);
	port_write(0xA0 , 0x11);

	/* ICW2 - remap offset address of IDT */
	/*
	* In x86 protected mode, we have to remap the PICs beyond 0x20 because
	* Intel has designated the first 32 interrupts as "reserved" for cpu exceptions
	*/
	port_write(0x21 , 0x20);
	port_write(0xA1 , 0x28);

	/* ICW3 - setup cascading */
	port_write(0x21 , 0x00);  
	port_write(0xA1 , 0x00);  

	/* ICW4 - environment info */
	port_write(0x21 , 0x01);
	port_write(0xA1 , 0x01);
	/* Initialization finished */

	/* mask interrupts */
	port_write(0x21 , interrupt_mask);
	port_write(0xA1 , interrupt_mask);

	__asm__("sti"); // enable interrupts
}


/*void kb_init(void) {
	idt_init();
	set_idt_entry(0x21, (uint32_t) kb_handler); // 0x21 - keyboard
	reload_idts();
	// 0xFD is 11111101 - enables only IRQ1 (keyboard)
	port_write(0x21 , 0xFD);
}

void kern_int_handler(void) __interrupt__((attribute)){
	uint8_t status;
	int8_t keycode;

	// write EOI
	port_write(0x20, 0x20);

	status = port_read(KEYBOARD_STATUS_PORT);
	// Lowest bit of status will be set if buffer is not empty
	if (status & 0x01) {
		keycode = port_read(KEYBOARD_DATA_PORT);
		if(keycode < 0)
			return;
		screen_writestr(keyboard_map[keycode], screen_colorgen(BLACK, GREEN));

	}
}*/