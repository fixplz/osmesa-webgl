#!/usr/bin/env node

var osmesa = require('../index');

var context = osmesa.CreateContext();

var width = 800, height = 800, bpp = 32;
var buffer = new Uint8Array(width * height * bpp / 8);
osmesa.MakeCurrent(context, buffer, width, height);

var gl = osmesa;
gl.clearColor(0.7, 0.8, 0.9, 1.0);
gl.clear(gl.COLOR_BUFFER_BIT);
gl.finish();

osmesa.DestroyContext(context);


var fs = require('fs')
var saveBuffer = require('./saveBuffer')

fs.writeFileSync('output.png', saveBuffer(buffer, width, height, true))
