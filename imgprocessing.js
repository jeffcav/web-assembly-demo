var img = new Image();
img.src = 'https://www.cosy.sbg.ac.at/~pmeerw/Watermarking/lena_color.gif';
var canvas = document.getElementById('canvas');
var ctx = canvas.getContext('2d');
img.onload = function() {
  ctx.drawImage(img, 0, 0);
  img.style.display = 'none';
};

