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

enum color {
	COLOR_BLACK 	= 0x00,
	COLOR_GREY		= 0x07,
	COLOR_WHITE 	= 0x0F,
	COLOR_RED		= 0x40,
	COLOR_ORANGE	= 0x42,
	COLOR_YELLOW	= 0x43,
	COLOR_GREEN		= 0x48,
	COLOR_CYAN		= 0x4C,
	COLOR_BLUE		= 0x4F,
	COLOR_PURPLE	= 0x52,
};

void print_binary(int x, int y, uint32_t data) {
	int i = 0;
	for (int byte = 3; byte >= 0; byte--) {
		for (int bit = 7; bit >= 0; bit--) {
			gfx_raw_draw(x + i, y, ((data & (0xFF << (byte << 3))) & (1 << bit)) ? COLOR_GREEN : COLOR_RED);
			i++;
		}
	}
}

void init();
void test() {
	vga_putc(69, 40, COLOR_RED);
	vga_putc(70, 40, COLOR_RED);
	vga_putc(69, 41, COLOR_RED);
	vga_putc(70, 41, COLOR_RED);
}

void test2() {
	vga_putc(69, 40, COLOR_GREEN);
	vga_putc(70, 40, COLOR_GREEN);
	vga_putc(69, 41, COLOR_GREEN);
	vga_putc(70, 41, COLOR_GREEN);
}

void main() {
	init();
	pit_reg_event(test, 10000, 0);
	pit_reg_event(test2, 10000, 10000);

	if (!gfx_init(320, 200, (void *) 0xA0000, 1, 0)) {
		vga_putc(319, 199, 0xF);
		while (1);
	}

	struct gfxRect rect = {
		16, 16, 0, 0, COLOR_PURPLE
	};

	gfx_rect_draw(&rect);
	print_binary(32, 32, 1);
	print_binary(32, 34, 127);
	print_binary(32, 36, 0xFFFFFFFF);
	print_binary(32, 38, 0xFF7F00FF);

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
