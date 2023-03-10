#include <gfx.h>
#define GFX_INIT_CHECK(value) if (!initialized) return value;
#define GFX_VOID_INIT_CHECK() if (!initialized) return;

static uint16_t screen_width;
static uint16_t screen_height;
static bool initialized = false;
static void * framebuffer = NULL;
static uint8_t gfx_depth = 1;
static uint8_t gfx_space = 0;

bool gfx_init(uint16_t width, uint16_t height, void * fb, uint8_t depth, uint8_t space) {
	if (initialized) {
		return false;
	}

	screen_width = width;
	screen_height = height;
	framebuffer = fb;
	gfx_depth = depth;
	gfx_space = space;
	initialized = true;

	return true;
}

void gfx_raw_draw(int x, int y, uint32_t color) {
	GFX_VOID_INIT_CHECK();

	if (gfx_depth == 1) {
		((uint8_t *) framebuffer)[x + (y * screen_width) * (gfx_space + 1)] = color;
	} else if (gfx_depth == 2) {
		((uint16_t *) framebuffer)[x + (y * screen_width) * (gfx_space + 1)] = color;
	} else if (gfx_depth == 3) {
		((uint8_t *) framebuffer)[x + (y * screen_width) * (gfx_space + 1) * 3] = color & 0xFF; ((uint8_t *) framebuffer)[(x + (y * screen_width) * (gfx_space + 1) * 3) + 1] = color & 0xFF00; ((uint8_t *) framebuffer)[(x + (y * screen_width) * (gfx_space + 1) * 3) + 2] = color & 0xFF0000;
	} else if (gfx_depth == 4) {
		((uint32_t *) framebuffer)[x + (y * screen_width) * (gfx_space + 1)] = color;
	} else {
		return;
	}
}

//  rect:

void gfx_rect_draw(struct gfxRect * rect) {
	GFX_VOID_INIT_CHECK();
	
	for (int w = 0; w < rect->width; w++) {
		for (int h = 0; h < rect->height; h++) {
			gfx_raw_draw(w + rect->x, h + rect->y, rect->color);
		}
	}
}
