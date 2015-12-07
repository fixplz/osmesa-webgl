module.exports = getBuffer

var PNG = require('pngjs').PNG

function getBuffer(buffer, width, height, alpha) {
    flipBuffer(buffer, width, height, alpha)

    var png = new PNG()
    png.width = width
    png.height = height
    png.data = buffer

    return PNG.sync.write(png)
}

function flipBuffer(buffer, width, height, alpha) {
    var step = alpha ? 4 : 3

    for (var y = 0; y < height / 2 | 0; ++y) {
        for (var i = 0; i < width * step; ++i) {
            var ix1 = y * width * step + i
            var ix2 = (height - 1 - y) * width * step + i
            var val1 = buffer[ix1]
            var val2 = buffer[ix2]
            buffer[ix2] = val1
            buffer[ix1] = val2
        }
    }
}
