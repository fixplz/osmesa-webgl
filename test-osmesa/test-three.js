// require('segfault-handler').registerHandler()

var THREE = require('three')
var Canvas = require('canvas')


var webgl = require('../index')
var gl = new webgl.WebGLCompat(800, 800)
gl.shaderCompat = true
gl.disableExtensions = true

var canvas = {
    getContext: function(type) {
        if(type == 'webgl') return gl
    },
    width: gl.width,
    height: gl.height,
    style: {},
}


var scene = new THREE.Scene();
var camera = new THREE.PerspectiveCamera( 75, gl.width/gl.height, 0.1, 1000 );

var renderer = new THREE.WebGLRenderer({ canvas: canvas })

renderer.setSize( gl.width, gl.height );
renderer.setClearColor( 0, 0 )


var image = new Canvas.Image()
image.src = require('fs').readFileSync('texture.jpg')
console.log('image',image.width,image.height)
var texture = new THREE.Texture(image)
texture.needsUpdate = true

var cube = new THREE.Mesh( new THREE.CubeGeometry( 1, 1, 1 ), new THREE.MeshPhongMaterial( { map: texture } ) )
cube.rotation.x += 1;
cube.rotation.y += 1;
scene.add(cube);

var sphere = new THREE.Mesh( new THREE.SphereGeometry( 0.3 ), new THREE.MeshPhongMaterial( { color: 0xff0000 } ) ) 
sphere.position.x = 2;
scene.add(sphere);

var pointLight = new THREE.PointLight(0xFFFFFF);
scene.add( pointLight )
pointLight.position.z = 5

camera.position.z = 5;

renderer.render(scene, camera);

// document.body.appendChild( renderer.domElement );


var fs = require('fs')
var saveBuffer = require('./saveBuffer')

fs.writeFileSync('output.png', saveBuffer(gl.buffer, gl.width, gl.height, true))

