#include <arch/x86/hal/gdt.h>
#include <arch/x86/hal/idt.h>
#include <arch/x86/hal/isr.h>
#include <arch/x86/hal/irq.h>
#include <arch/x86/hal/pic.h>
#include <arch/x86/hal/pit.h>
#include <std/stdlib.h>
#include <arch/x86/drivers/cpubasics.h>
#include <arch/x86/drivers/vga.h>
#include <arch/x86/drivers/keyboard.h>
#include <arch/x86/drivers/pci.h>
#include <std/stdbool.h>
#include <gfx.h>

void init();
void test() {
	vga_putc(69, 40, 0xF);
}

void test2() {
	vga_putc(69, 40, 0x0);
}

void main() {
	init();
	pit_reg_event(test, 10000);
	pit_reg_event(test2, 20000);

	if (!gfx_init(320, 200, (void *) 0xA0000, 0)) {
		vga_putc(319, 199, 0xF);
		while (1);
	}

	struct gfxRect rect = {
		16, 16, 0, 0, 0xF
	};

	gfx_rect_draw(&rect);

	while (1) {
		
	}
}

void init() {
	gdt_init();
	idt_init();
	isr_init();
	irq_init();
	pit_init();
	pci_init();
	keyboard_init();
}
