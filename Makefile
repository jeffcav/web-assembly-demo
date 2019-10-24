all:
	emcc -O3 -g3 invert.c -o invert.js -s WASM=1

server:
	emrun --no_browser --port 8000 .

clean:
	rm -rf invert.js || true
	rm -rf invert.wasm || true
