#include "subdivision_renderer.h"

SubdivisionRenderer::SubdivisionRenderer(int w, int h)
: width(w), height(h) {
    /* initialize the 2d array */
    pixelRendered = new bool*[height];
    for (int i = 0; i < height; i++) {
        pixelRendered[i] = new bool[width];
    }
}

void SubdivisionRenderer::render() {
    currDepth = 0;
    renderAtCurrDepth();
}

void SubdivisionRenderer::renderAtCurrDepth() {
    int gridSize = 64 / pow(2, currDepth);
    int offset = gridSize / 2;
    
    for (int i = 0; i < height; i += gridSize) {
        for (int j = 0; j < width; j += gridSize) {
            int x = j + offset;
            int y = i + offset;
        }
    }
}

void SubdivisionRenderer::generateImage() {
    
}
