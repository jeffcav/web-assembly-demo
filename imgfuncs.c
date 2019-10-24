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

int* EMSCRIPTEN_KEEPALIVE winvert() {
	int i;
	int neg = 0xffffff;
	for (i = 0; i < HEIGHT*WIDTH; i++) {
		data[i] = (neg - data[i]) | 0xff000000;
		//data[i] = 0xabc123ab;
	}

	return &data[0];
}
