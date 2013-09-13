#include "parser.h"

namespace Parser {
    Scene* parseScene(std::string filename) {
        Scene* s = parseObjFile(filename);
        filename.replace(filename.length() - 3, 3, "mtl");
        std::cout << filename << std::endl;
        parseMtlFile(filename, s);
        return s;
    }
    
	Scene* parseObjFile(std::string filename) {
		std::ifstream input(filename.c_str());

		if (!input) { // file does not exist
			throw "file does not exist";
		}

		std::vector<Object*> sceneObjects;
		Object* currObj = NULL;
		std::vector<Vertex*> vertices;
		
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

				Vertex* newVertex = new Vertex(coords);

				vertices.push_back(newVertex);

			} else if (item == "f") { // face
				int firstVertexIndex, lastVertexIndex;

				for (int i = 0; getline(ss, item, ' '); i++) {
					int vertexIndex = atoi(item.c_str());
					if (i == 0) {
						firstVertexIndex = vertexIndex;
					} else if (i >= 2) {
						Face* f = new Face;
						f->addVertex(vertices[firstVertexIndex - 1]);
						f->addVertex(vertices[lastVertexIndex - 1]);
						f->addVertex(vertices[vertexIndex - 1]);

						currObj->addFace(f);
					}
					lastVertexIndex = vertexIndex;
				}
			} else if (item == "usemtl") { // material
                getline(ss, item, ' ');
                currObj->materialName = item;
            }
		} 

		sceneObjects.push_back(currObj); // add the last object to the list
		Scene* s = new Scene(sceneObjects);
		
		return s;
	}

	void parseMtlFile(std::string filename, Scene* scene) {
		std::ifstream input(filename.c_str());

		if (!input) { // file does not exist
			throw "file does not exist";
		}
		
		// Material* mat;
		Object* currObj = NULL;
        
		for (std::string line; getline(input, line); ) {
            std::stringstream ss(line);
			std::string item;
            
			getline(ss, item, ' ');
			
            if (item == "newmtl") {
                getline(ss, item, ' ');
                for (Object* obj : scene->getObjects()) {
                    if (obj->materialName == item) {
                        currObj = obj;
                        currObj->mat = new Material();
                    }
                }
            } else if (item == "Ka") {
                float rgb[3];
                for (int i = 0; getline(ss, item, ' '); i++) {
                    rgb[i] = atof(item.c_str());
                }
                
                currObj->mat->ka = Vec3(rgb);
            } else if (item == "Kd") {
                float rgb[3];
                for (int i = 0; getline(ss, item, ' '); i++) {
                    rgb[i] = atof(item.c_str());
                }
                
                currObj->mat->kd = Vec3(rgb);
            } else if (item == "Ks") {
                float rgb[3];
                for (int i = 0; getline(ss, item, ' '); i++) {
                    rgb[i] = atof(item.c_str());
                }
                
                currObj->mat->ks = Vec3(rgb);
            }
		}
	}
};
