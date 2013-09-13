#ifndef FYP_subdivision_renderer_h
#define FYP_subdivision_renderer_h

#include "includes.h"

class SubdivisionRenderer {
public:
    SubdivisionRenderer(int w, int h);
    void render();
    void generateImage();
private:
    void renderAtCurrDepth();
    
    int width, height;
    bool** pixelRendered;
    int currDepth;
};

#endif
