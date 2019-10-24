all:
	emcc -O3 -g3 imgfuncs.c -o imgfuncs.js -s WASM=1

server:
	emrun --no_browser --port 8000 .

clean:
	rm imgfuncs.js
	rm imgfuncs.wasm
