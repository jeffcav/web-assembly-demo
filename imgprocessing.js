request = new XMLHttpRequest();
request.open('GET', 'imgfuncs.wasm');
request.responseType = 'arraybuffer';
request.send();
request.onload = function() {
  enablew();
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


function enablew() {
  var bytes = request.response;
  WebAssembly.instantiate(bytes, importObject).then(results => {
      var winv = function() {
	return results.instance.exports.winvert();
      }
    var wasmbtn = document.getElementById('wasmbtn');
    wasmbtn.addEventListener('click', winv);

	  //results.instance.exports.winvert();
  });
}

function draw(img) {
  var canvas = document.getElementById('canvas');
  var ctx = canvas.getContext('2d');
  ctx.drawImage(img, 0, 0);
  img.style.display = 'none';
  var imageData = ctx.getImageData(0, 0, canvas.width, canvas.height);
  var data = imageData.data;

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
}
