#define HEIGHT 512
#define WIDTH 512
#include <emscripten.h>

int data[WIDTH * HEIGHT];

int* EMSCRIPTEN_KEEPALIVE getdata() {
	return &data[0];
}

int* EMSCRIPTEN_KEEPALIVE winvert() {
	int i;
	int neg = 0xffffff;
	for (i = 0; i < HEIGHT*WIDTH; i++) {
		data[i] = (neg - data[i]) | 0xff000000;
		//data[i] = 0xabc123ab;
	}

	return &data[0];
}
