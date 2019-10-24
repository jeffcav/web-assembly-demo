#define HEIGHT 512
#define WIDTH 512
#include <stdlib.h> // for rand
#include <emscripten.h>

int data[WIDTH * HEIGHT];

int* EMSCRIPTEN_KEEPALIVE getdata() {
	return &data[0];
}

int EMSCRIPTEN_KEEPALIVE setdata(int *buf) {
	int i, j=0;
	for (i = 0; i < WIDTH*HEIGHT; i++) {
		data[i] = buf[i];
		if (buf[i] > 0)
			j = 1;
	}
	return j;
}

int * EMSCRIPTEN_KEEPALIVE paint(int seed) {
	srand(seed);
	int i;
	/*
 	for (i = 0; i < HEIGHT*WIDTH; i++) {
		data[i] = rand() % 0xffffffff;
	}
	*/
	
        for (i = 0; i < HEIGHT*WIDTH; i++) {
                data[i] -= rand() % 0xff;
        }
        

	return &data[0];
}

int* EMSCRIPTEN_KEEPALIVE winvert(int *src) {
	int i, mask = 0xffffff00, val;
	for (i = 0; i < HEIGHT*WIDTH; i++) {
		data[i] = src[i];
		//data[i] = 0xabc123ab;

		//val = (val & 0xff00ffff) | ((0x00ff0000-(val & 0x00ff0000)) & 0x00ff0000);
		//data[i] = val;

		//data[i] = data[i] + 0x1;
		/*
		unsigned char r,g,b,a;
		a = (origin[i] & mask_red) >> 24;
		b = (origin[i] & mask_green) >> 16;
		g = (origin[i] & mask_blue) >> 8;
		r = (origin[i] & mask_alpha);

		r = 255 - r;
		g = 255 - g;
		b = 255 - b;

		origin[i] = 0;

		origin[i] |= a;
		origin[i] <<= 8;

		origin[i] |= b;
		origin[i] <<= 8;

		origin[i] |= g;
		origin[i] <<= 8;

		origin[i] |= r;

		//origin[i] = mask - origin[i];
		*/
	}

	return &data[0];
}
