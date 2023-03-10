#ifndef GFX_H
#define GFX_H
#include <std/stdbool.h>
#include <std/stddef.h>
#include <std/types.h>

struct gfxRect {
	int width, height, x, y;
	int color;
};

bool gfx_init(uint16_t width, uint16_t height, void * fb, uint8_t mode);
void gfx_raw_draw(int x, int y, uint8_t color);
void gfx_rect_draw(struct gfxRect * rect);

#endif
