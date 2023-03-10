#pragma once
#include <arch/x86/drivers/cpubasics.h>
#include <arch/x86/hal/isr.h>
#include <arch/x86/hal/irq.h>

struct pit_event {
	void (*func)();
	size_t interval;
};

void pit_reg_event(void (*func)(), size_t interval, int offset);
void pit_set_freq(size_t hz);
void pit_init();
