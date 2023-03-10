#include <gfx.h>
#define GFX_INIT_CHECK(value) if (!initialized) return value;
#define GFX_VOID_INIT_CHECK() if (!initialized) return;

static uint16_t screen_width;
static uint16_t screen_height;
static bool initialized = false;
static uint8_t * framebuffer = NULL;
static uint8_t gfx_mode = 0;

bool gfx_init(uint16_t width, uint16_t height, void * fb, uint8_t mode) {
	if (initialized) {
		return false;
	}

	screen_width = width;
	screen_height = height;
	framebuffer = (uint8_t *) fb;
	gfx_mode = mode;
	initialized = true;

	return true;
}

void gfx_raw_draw(int x, int y, uint8_t color) {
	GFX_VOID_INIT_CHECK();

	((uint8_t *) framebuffer)[x + (y * screen_width)] = color;
}

void gfx_rect_draw(struct gfxRect * rect) {
	GFX_VOID_INIT_CHECK();
	
	for (int w = 0; w < rect->width; w++) {
		for (int h = 0; h < rect->height; h++) {
			framebuffer[w + rect->x + ((h + rect->y) * screen_width)] = rect->color;
		}
	}
}
