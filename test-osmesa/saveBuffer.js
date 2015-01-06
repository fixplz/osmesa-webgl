module.exports = saveBuffer

function saveBuffer(buffer, width, height, alpha) {
    buffer = new Buffer(buffer)

    var step = alpha ? 4 : 3

    if(alpha) {
        for (var i = 0; i < buffer.length / step; ++i) {
            buffer[i*step + 3] = 255 - buffer[i*step + 3]
        }
    }

    var Png = require('png').Png

    return new Png(buffer, width, height, alpha ? 'rgba' : 'rgb').encodeSync()
}
