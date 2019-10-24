#define HEIGHT 512
#define WIDTH 512
#include <emscripten.h>

unsigned int data[WIDTH * HEIGHT];

unsigned int* EMSCRIPTEN_KEEPALIVE winvert() {
	int i, mask = 0xffffff00;
	for (i = 0; i < HEIGHT*WIDTH; i++) {
		data[i] = mask - data[i];
	}

	return &data[0];
}
