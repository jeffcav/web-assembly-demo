request = new XMLHttpRequest();
request.open('GET', 'imgfuncs.wasm');
request.responseType = 'arraybuffer';
request.send();
request.onload = function() {
};

var img = new Image();
img.src = 'lena_color.gif';
img.onload = function() {
  draw(this);
};


var importObject = {
            'env': {
            'memoryBase': 0,
            'tableBase': 0,
            'memory': new WebAssembly.Memory({initial: 256, maximum:256}),
            'table': new WebAssembly.Table({initial: 256, element: 'anyfunc'}),
            'abort': alert,
            'emscripten_resize_heap': _emscripten_resize_heap}}



function draw(img) {
	// Get Canvas image
	var canvas = document.getElementById('canvas');
	var ctx = canvas.getContext('2d');
	ctx.drawImage(img, 0, 0);
	img.style.display = 'none';
	var imageData = ctx.getImageData(0, 0, canvas.width, canvas.height);
	var data = imageData.data;

	// Assing JS invert to a button
	var invert = function() {
		for (var i = 0; i < data.length; i += 4) {
			data[i]     = 255 - data[i];     // red
			data[i + 1] = 255 - data[i + 1]; // green
			data[i + 2] = 255 - data[i + 2]; // blue
		}
		ctx.putImageData(imageData, 0, 0);
  	};

	var jsbtn = document.getElementById('jsbtn');
	jsbtn.addEventListener('click', invert);

	// Assign WASM Invert to a button
	var bytes = request.response;
	WebAssembly.instantiate(bytes, importObject).then(results => {
		// Initialize WASM buffer with current Canvas content
		init_pointer = results.instance.exports.getdata();
		var init_data = new Uint8ClampedArray(importObject.env.memory.buffer, init_pointer, canvas.width * canvas.height * 4);
		var init_img = new ImageData(init_data, canvas.width, canvas.height);
		init_img.data.set(data);

		var winvf = function() {
			var pointer = results.instance.exports.winvert();
			var inv_data = new Uint8ClampedArray(importObject.env.memory.buffer, pointer, canvas.width * canvas.height * 4);
        	        var inv_img = new ImageData(inv_data, canvas.width, canvas.height);
			ctx.putImageData(inv_img, 0, 0);
		}

		var wasmbtn = document.getElementById('wasmbtn');
		wasmbtn.addEventListener('click', winvf);
	});
}

