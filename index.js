var WebGLMesa = require('./build/Release/webgl.node')

function WebGLBase(width, height) {
    if(! (this instanceof WebGLBase)) {
        return WebGLBase.apply(Object.create(WebGLBase.prototype), arguments)
    }

    this._context = WebGLMesa.CreateContext.call(null, arguments)

    this.width = width
    this.height = height

    this.buffer = new Buffer(width * height * 4)

    this.makeCurrent()
}

WebGLBase.prototype = Object.create(WebGLMesa)

WebGLBase.prototype.makeCurrent = function() {
    WebGLMesa.MakeCurrent(this._context, this.buffer, this.width, this.height)
}

WebGLBase.prototype.destroy = function() {
    WebGLMesa.DestroyContext(this._context)
}

module.exports = require('node-webgl-wrapper')(WebGLBase)

module.exports.CreateContext = WebGLMesa.CreateContext
module.exports.DestroyContext = WebGLMesa.DestroyContext
module.exports.MakeCurrent = WebGLMesa.MakeCurrent
