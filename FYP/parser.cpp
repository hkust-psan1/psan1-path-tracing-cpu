#include "parser.h"

namespace Parser {
    Scene* parseScene(std::string filename) {
        Scene* s = parseObjFile(filename);
        filename.replace(filename.length() - 3, 3, "mtl");
        parseMtlFile(filename, s);
        return s;
    }
    
	Scene* parseObjFile(std::string filename) {
		std::ifstream input(filename.c_str());

		if (!input) { // file does not exist
			throw "file does not exist";
		}

		std::vector<Object*> sceneObjects;
        std::vector<Light*> sceneLights;
		Object* currObj = NULL;
        PointLight* currLight = NULL;
		// std::vector<Vertex*> vertices;
        
        std::vector<Vec3> vertexCoords;
        std::vector<Vec3> vertexNormals;
        std::vector<Vec3> vertexTexCoords;
        
        // map from vertex coord index to vertex
        std::map<int, Vertex*> vertices;
		
		for (std::string line; getline(input, line); ) {
			std::stringstream ss(line);
			std::string item;

			getline(ss, item, ' ');

			if (item == "o") { // start of a new object
				if (currObj) { // if it's not the first object parsed
					sceneObjects.push_back(currObj); // add old object to list
				}

				currObj = new Object;
			} else if (item == "v") { // vertex
				float coords[3];

				for (int i = 0; getline(ss, item, ' '); i++) {
					coords[i] = atof(item.c_str());
				}
                
                vertexCoords.push_back(Vec3(coords));

            } else if (item == "vn") { // vertex normal
                float normals[3];
                
                for (int i = 0; getline(ss, item, ' '); i++) {
                    normals[i] = atof(item.c_str());
                }
                
                vertexNormals.push_back(Vec3(normals));
            
            } else if (item == "vt") { // texture coordinate
                float texCoords[2];
                
                for (int i = 0; getline(ss, item, ' '); i++) {
                    texCoords[i] = atof(item.c_str());
                }
                
                vertexTexCoords.push_back(Vec3(texCoords[0], texCoords[1], 0)); // texture coords are 2D
            
			} else if (item == "f") { // face
                Face* f = new Face;

				for (int i = 0; getline(ss, item, ' '); i++) { // item is in the format <P>/<T>/<N>
                    std::stringstream _ss(item);
                    std::string index; // index of the vectors parsed
                    
                    /* parsing for position */
                    getline(_ss, index, '/');
                    int vertexIndex = atof(index.c_str()) - 1;

                    /* parsing for texture coords */
                    getline(_ss, index, '/');
                    int texIndex = -1;
                    if (index.length() != 0) {
                        texIndex = atof(index.c_str()) - 1;
                    }
                    
                    /* parsing for normal */
                    getline(_ss, index, '/');
                    int normalIndex = atof(index.c_str()) - 1;

                    /* find vertex already created or create new vertex */
                    Vertex* v;
                    auto result = vertices.find(vertexIndex); // the pair found
                    
                    if (result == vertices.end()) { // cannot find vertex with index
                        v = new Vertex(vertexCoords[vertexIndex], vertexNormals[normalIndex]);
                        vertices.insert(std::pair<int, Vertex*>(vertexIndex, v));
                        
                        if (texIndex != -1) { // if texture coords is defined
                            v->setTexCoords(vertexTexCoords[texIndex]);
                        }
                    } else { // found vertex with index
                        v = result->second; // get vertex from map
                    }

                    // f->addVertex(v);
                    // std::cout << i << std::endl;
                    f->vertices[i] = v;
				}

                f->calculateFaceNormal();
                currObj->addFace(f);
			} else if (item == "usemtl") { // material
                getline(ss, item, ' ');
                currObj->materialName = item;
            } else if (item == "@smooth") { // smooth shading on or off
                getline(ss, item, ' ');
                currObj->smoothShading = (item == "on");
            } else if (item == "l") {
                if (currLight) {
                    sceneLights.push_back(currLight);
                }
                
                getline(ss, item, ' ');
                string name = item;
                getline(ss, item, ' ');
                string lightType = item;
                
                if (lightType == "POINT") {
                    currLight = new PointLight;
                }
                
            } else if (item == "pos") {
                float pos[3];
                
				for (int i = 0; getline(ss, item, ' '); i++) {
					pos[i] = atof(item.c_str());
				}
                
                currLight->position = Vec3(pos[0], pos[2], pos[1]);
            } else if (item == "color") {
                float c[3];
                
				for (int i = 0; getline(ss, item, ' '); i++) {
					c[i] = atof(item.c_str());
				}
                
                currLight->color = Vec3(c);
            } else if (item == "energy") {
                getline(ss, item, ' ');
                currLight->energy = atof(item.c_str());
            }
		}
        
		sceneObjects.push_back(currObj); // add the last object to the list
		Scene* s = new Scene(sceneObjects);
        
        sceneLights.push_back(currLight);
        s->lights = sceneLights;
        
        /* DO move this piece of code to other places!!! */
        for (Object* obj : s->getObjects()) {
            float maxX = -FLT_MAX, maxY = -FLT_MAX, maxZ = -FLT_MAX;
            float minX = FLT_MAX, minY = FLT_MAX, minZ = FLT_MAX;
            
            for (Face* f : obj->getFaces()) {
                for (Vertex* v : f->vertices) {
                    const Vec3& pos = v->getPos();
                    maxX = pos.x > maxX ? pos.x : maxX;
                    maxY = pos.y > maxY ? pos.y : maxY;
                    maxZ = pos.z > maxZ ? pos.z : maxZ;
                    
                    minX = pos.x < minX ? pos.x : minX;
                    minY = pos.y < minY ? pos.y : minY;
                    minZ = pos.z < minZ ? pos.z : minZ;
                }
            }
            
            obj->buildBox(Vec3(minX, minY, minZ), Vec3(maxX, maxY, maxZ));
            
            //std::cout << obj->boundingBoxMin << std::endl << obj->boundingBoxMax << std::endl;
        }
		s->buildBox();
		return s;
	}

	void parseMtlFile(std::string filename, Scene* scene) {
		std::ifstream input(filename.c_str());
        
        string directory;
        int tmp, pos = 0;
        int lastIndex;

        while ((tmp = filename.find(SLASH, pos)) != string::npos) {
            pos = tmp + 1;
            lastIndex = tmp;
        }
        
        directory = filename.substr(0, lastIndex);        

		if (!input) { // file does not exist
			throw "file does not exist";
		}
		
        std::vector<Material*> materials;
		Material* currMat = NULL;
        
		for (std::string line; getline(input, line); ) {
            std::stringstream ss(line);
			std::string item;
            
			getline(ss, item, ' ');
			
            if (item == "newmtl") {
                getline(ss, item, ' ');
                
                if (currMat) {
                    materials.push_back(currMat);
                }
                currMat = new Material(item);
            } else if (item == "Ka") {
                float rgb[3];
                for (int i = 0; getline(ss, item, ' '); i++) {
                    rgb[i] = atof(item.c_str());
                }
                
                currMat->ka = Vec3(rgb);
            } else if (item == "Kd") {
                float rgb[3];
                for (int i = 0; getline(ss, item, ' '); i++) {
                    rgb[i] = atof(item.c_str());
                }
                
                currMat->kd = Vec3(rgb);
            } else if (item == "Ks") {
                float rgb[3];
                for (int i = 0; getline(ss, item, ' '); i++) {
                    rgb[i] = atof(item.c_str());
                }
                
                currMat->ks = Vec3(rgb);
            } else if (item == "map_Kd") {
                getline(ss, item, ' ');
                QPixmap map((directory + "/" + item).c_str());
                currMat->diffuseMap = new QImage(map.toImage());
            } else if (item == "map_Disp") {
                getline(ss, item, ' ');
                QPixmap map((directory + "/" + item).c_str());
                currMat->displacementMap = new QImage(map.toImage());
            } else if (item == "map_Ks") {
                getline(ss, item, ' ');
                QPixmap map((directory + "/" + item).c_str());
                currMat->specularMap = new QImage(map.toImage());
            } else if (item == "Alpha") {
                getline(ss, item, ' ');
                currMat->alpha = atof(item.c_str());
            } else if (item == "IOR") {
                getline(ss, item, ' ');
                currMat->ior = atof(item.c_str());		
				currMat->ior_inverse = 1.0f / currMat->ior;
                
                if (abs(currMat->ior - 1.0f) < 0.0001f) {
                    currMat->isTransmissive = false;
                } else {
                    currMat->isTransmissive = true;
                }
            } else if (item == "RefractGloss") {
                getline(ss, item, ' ');
                currMat->refractGloss = atof(item.c_str());
            } else if (item == "ReflectFactor") {
                getline(ss, item, ' ');
                currMat->reflectFactor = atof(item.c_str());
            } else if (item == "ReflectGloss") {
                getline(ss, item, ' ');
                currMat->reflectGloss = atof(item.c_str());
            }
		}
		materials.push_back(currMat);
		
        for (Material* mat : materials) {
            for (Object* obj : scene->getObjects()) {
                if (obj->materialName == mat->name) {
                    obj->mat = mat;
                }
            }
        }
	}

};
