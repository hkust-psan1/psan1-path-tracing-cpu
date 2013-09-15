#include "vertex.h"

Vertex::Vertex(const Vec3& p, const Vec3& n)
    : pos(p), normal(n), hasTexture(false) {

}

/*
Vertex::Vertex(const Vec3& p, const Vec3& n, const Vec3& t)
    : pos(p), normal(n), texCoords(t), hasTexture(true) {
    
}
*/