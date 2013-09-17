#include "boundingbox.h"

#define EPSILON 0.00001

BoundingBox::BoundingBox(Face* f) : isLeaf(true), left(0), right(0), face(f)
{
	boxMin = Vec3(FLT_MAX);
	boxMax = Vec3(-FLT_MAX);
	
	for (int i = 0; i < 3; i++)
	{
		Vec3 p = f->getVertices()[i]->getPos();
		for (int j = 0; j < 3; j++)
		{
			boxMax[j] = boxMax[j] < p[j] ? p[j] : boxMax[j];
			boxMin[j] = boxMin[j] > p[j] ? p[j] : boxMin[j];
		}
	}
}

int max_of(const float* d)
{
	if (d[0] > d[1])
	{
		if (d[0] > d[2]) return 0;
		return 2;
	}
	else
	{
		if (d[1] > d[2]) return 1;
		return 2;
	}
}

int min_of(const float* d)
{
	if (d[0] < d[1])
	{
		if (d[0] < d[2]) return 0;
		return 2;
	}
	else
	{
		if (d[1] < d[2]) return 1;
		return 2;
	}
}

Intersection* BoundingBox::intersect(const Ray& r, float T_min)
{
	Vec3 d = Vec3(r.dir);
	Vec3 p = r.pos;

	for (int i = 0; i < 3; i++)
		if (d[i] == .0f)
			d[i] = FLT_MIN; 

	float min[3] = {};
	float max[3] = {};

	for (int j = 0; j < 3; j++)
	{
		if (d[j] > 0)
		{
			min[j] = (boxMin[j] - p[j]) / d[j];
			max[j] = (boxMax[j] - p[j]) / d[j];
		}
		else
		{
			min[j] = (boxMax[j] - p[j]) / d[j];
			max[j] = (boxMin[j] - p[j]) / d[j];
		}
	}

	int max_of_min = max_of(min);
	int min_of_max = min_of(max);
	float t1 = min[max_of_min];
	float t2 = max[min_of_max];

	//no intersection point
	if (t2 < t1) return NULL;

	//t < 0
	if (t2 < EPSILON) return NULL;
	
	//is leaf
	float min_t = FLT_MAX;
	if (isLeaf)
		return face->intersect(r, min_t);
	
	int a1 = r.pos.get(pivot)+ t1 * r.dir.get(pivot) > midLine ? 1 : -1;
	int a2 = r.pos.get(pivot)+ t2 * r.dir.get(pivot) > midLine ? 1 : -1;

	Intersection* lIntc = left->intersect(r, min_t);
	// no intersection from left
	if (lIntc == NULL)
		return right->intersect(r, min_t);

	Intersection* rIntc = right->intersect(r, lIntc->t);
	if (rIntc == NULL)
	{
		return lIntc;
	}
	else
	{
		delete lIntc;
		return rIntc;
	}
}

void BoundingBox::mergeBox(BoundingBox* b)
{	
	for (int j = 0; j < 3; j++)
	{
		boxMax[j] = boxMax[j] < b->boxMax[j] ? b->boxMax[j] : boxMax[j];
		boxMin[j] = boxMin[j] > b->boxMin[j] ? b->boxMin[j] : boxMin[j];
	}
}

void BoundingBox::mergePoint(Vec3 p)
{	
	for (int j = 0; j <3; j++)
	{
		boxMax[j] = boxMax[j] < p[j] ? p[j] : boxMax[j];
		boxMin[j] = boxMin[j] > p[j] ? p[j] : boxMin[j];
	}
}

void BoundingBox::partition(std::vector<BoundingBox*> boxes)
{
	// less than 2 left
	if(boxes.size() == 0)
	{
		std::cout << "something went wrong in bounding box partition. error 1" << std::endl;
		return;
	}
	
	if(boxes.size() == 1)
	{
		boxMax = boxes[0]->boxMax;
		boxMin = boxes[0]->boxMin;
		left = boxes[0]->left;
		right = boxes[0]->right;
		return;
	}

	Vec3 min = Vec3(FLT_MAX);
	Vec3 max = Vec3(-FLT_MAX);

	//choose the longest axis
	BoundingBox avgBox = BoundingBox(min, max);
	for(BoundingBox* b : boxes)
	{
		avgBox.mergePoint((b->boxMax + b->boxMin) * 0.5f);
	}
	Vec3 diff = avgBox.boxMax - avgBox.boxMin;
	pivot = diff.maxElement();

	//split the box
	midLine = diff[pivot] / 2.0f + avgBox.boxMin[pivot];
	std::vector<BoundingBox*> lBox;
	std::vector<BoundingBox*> rBox;
	left = new BoundingBox(min, max);
	right = new BoundingBox(min, max);

	for(BoundingBox* b: boxes)
	{
		if (b->boxMax[pivot] + b->boxMin[pivot] < midLine * 2)
		{
			left->mergeBox(b);
			lBox.push_back(b);
		}
		else
		{
			right->mergeBox(b);
			rBox.push_back(b);
		}
	}

	if(lBox.size() == 0 || rBox.size() == 0)
	{
		/*std::cout << "something went wrong in bounding box partition. error 2 -> " << lBox.size() << " | "  <<  rBox.size() << std::endl;
		std::cout << avgBox.boxMin[pivot] << "  " << midLine << "  " << avgBox.boxMax[pivot] << std::endl;
		std::cout << avgBox.boxMin << std::endl;
		std::cout << avgBox.boxMax << std::endl;
		for(BoundingBox* b: boxes)
		{
			std::cout << b->boxMin[pivot] << "  " <<  b->boxMax[pivot] << std::endl;
		}*/
		// force partition
		lBox = std::vector<BoundingBox*>();
		rBox = std::vector<BoundingBox*>();
		for (int i = 0; i < boxes.size(); i++)
		{
			if (i < boxes.size() / 2)
			{
				lBox.push_back(boxes[i]);
			}
			else
			{
				rBox.push_back(boxes[i]);
			}
		}
	}
	
	
	//recursion
	if (lBox.size() == 1)
	{
		delete left;
		left = lBox[0];
	}
	else
	{
		left->partition(lBox);
	}
		
	if (rBox.size() == 1)
	{
		delete right;
		right = rBox[0];
	}
	else
	{
		right->partition(rBox);
	}
}

Vec3 BoundingBox::shadowAttenuation(const Ray& r, float T_min)
{
	//return Vec3(1.0f);
	Intersection* intc = intersect(r, T_min);

	if (intc == NULL) return Vec3(1.0f);

	//leaf
	if (isLeaf) 
	{
		if(face->intersect(r, T_min))
		{
			if (intc->mat->isTransmissive)
				return intc->mat->kt;
			else
				return Vec3(.0f);
		}
		else return Vec3(1.0f);
	}
		
	return left->shadowAttenuation(r, T_min) * right->shadowAttenuation(r, T_min);

}