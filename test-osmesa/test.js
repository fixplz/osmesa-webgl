#!/usr/bin/env node

var webgl = require('../index');

var gl = webgl.WebGL(800, 800);

gl.clearColor(0.7, 0.8, 0.9, 1.0);
gl.clear(gl.COLOR_BUFFER_BIT);
gl.finish();

gl.destroy();


var fs = require('fs')
var saveBuffer = require('./saveBuffer')

fs.writeFileSync('output.png', saveBuffer(gl.buffer, gl.width, gl.height, true))
