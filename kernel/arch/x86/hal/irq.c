#include <arch/x86/hal/irq.h>

#define PIC_REMAP_OFFSET		0x20

IRQHandler irq_handlers[16];

void irq_handler(Registers * regs) {
	int irq = regs->interrupt - PIC_REMAP_OFFSET;

	if (irq_handlers[irq] != NULL) {
		irq_handlers[irq](regs);
	} else {
		pic_send_eoi();
	}
}

void irq_init() {
    disable_interrupts();

	pic_config(PIC_REMAP_OFFSET, PIC_REMAP_OFFSET + 8);

	for (int i = 0; i < 16; i++) {
		isr_reg_handler(PIC_REMAP_OFFSET + i, irq_handler);
		pic_mask(PIC_REMAP_OFFSET + i);
	}

	enable_interrupts();
}

void irq_reg_handler(int irq, IRQHandler handler) {
	irq_handlers[irq] = handler;
    pic_unmask(irq);
}
