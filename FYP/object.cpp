#include "object.h"

Object::Object() {
    // mat = new Material();
}

void Object::addFace(Face* f) {
	faces.push_back(f);
	f->setObject(this);
}

void Object::buildBox(Vec3 min, Vec3 max)
{
	root = new BoundingBox(min, max);
	std::vector<BoundingBox*> boxes;
	for (Face* f: faces)
	{
		BoundingBox* b = new BoundingBox(f);
		boxes.push_back(b);
	}
	root->partition(boxes);
}
