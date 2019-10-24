#include <emscripten.h>

#define HEIGHT 512
#define WIDTH 512

int buffer[WIDTH * HEIGHT];

int* EMSCRIPTEN_KEEPALIVE get_buffer() {
	return &buffer[0];
}

int* EMSCRIPTEN_KEEPALIVE invert_colors() {
	int i;
	int neg = 0xffffff;
	for (i = 0; i < HEIGHT*WIDTH; i++)
		buffer[i] = (neg - buffer[i]) | 0xff000000;

	return &buffer[0];
}

