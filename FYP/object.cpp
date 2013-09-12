#include "object.h"

Object::Object() {
    mat = new Material();
}

void Object::addFace(Face* f) {
	faces.push_back(f);
	f->setObject(this);
}
