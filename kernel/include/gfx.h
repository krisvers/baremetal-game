#ifndef GFX_H
#define GFX_H
#include <std/stdbool.h>
#include <std/stddef.h>
#include <std/types.h>

struct gfxRect {
	int width, height, x, y;
	uint32_t color;
};

struct gfxBitmap {
	int width, height;
	uint8_t depth;
	uint8_t transparent;
	uint8_t * data;	
};

bool gfx_init(uint16_t width, uint16_t height, void * fb, uint8_t depth, uint8_t space);
void gfx_raw_draw(int x, int y, uint32_t color);
void gfx_rect_draw(struct gfxRect * rect);

#endif
