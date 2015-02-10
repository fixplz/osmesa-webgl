var WebGLMesa = require('./build/Release/webgl.node')

function WebGLBase(width, height) {
    if(! (this instanceof WebGLBase)) {
        return WebGLBase.apply(Object.create(WebGLBase.prototype), arguments)
    }

    this.resize(width, height)
}

WebGLBase.prototype = Object.create(WebGLMesa)

WebGLBase.prototype.makeCurrent = function() {
    if(! this._context)
        this._context = WebGLMesa.CreateContext()

    WebGLMesa.MakeCurrent(this._context, this.buffer, this.width, this.height)
}

WebGLBase.prototype.reset = function() {
    WebGLMesa.DestroyContext(this._context)
    this._context = null
}

WebGLBase.prototype.resize = function(width, height) {
    if(width == this.width && height == this.height)
        return

    this.width = width
    this.height = height

    this.buffer = new Buffer(width * height * 4)
}

module.exports = require('node-webgl-wrapper')(WebGLBase)

module.exports.CreateContext = WebGLMesa.CreateContext
module.exports.DestroyContext = WebGLMesa.DestroyContext
module.exports.MakeCurrent = WebGLMesa.MakeCurrent
