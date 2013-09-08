#include "object.h"

Object::Object() {

}

void Object::addFace(Face* f) {
	faces.push_back(f);
	f->setObject(this);
}