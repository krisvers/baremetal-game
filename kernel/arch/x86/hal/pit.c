#include <arch/x86/hal/pit.h>

static size_t ticks = 0;
static struct pit_event pit_events[8];
static uint8_t pit_event_num = 0;

static void timer_handler(Registers * regs) {
    pic_send_eoi();
    ticks++;

	for (uint8_t i = 0; i < pit_event_num; i++) {
		if (ticks % pit_events[i].interval == 0) {
			pit_events[i].func();
		}
	}
}

void pit_reg_event(void (*func)(), size_t interval, int offset) {
	struct pit_event * tmp = &pit_events[pit_event_num];

	tmp->func = func;
	tmp->interval = interval + offset;

	pit_event_num++;
}

void pit_set_freq(size_t hz) {
    size_t div = 3579545 / (hz * 3);
    outb(0x43, 0x36);
    outb(0x40, div & 0xFF);
    outb(0x40, div >> 8);
}

void pit_init() {
    pit_set_freq(10000);
    irq_reg_handler(0, timer_handler);
}
