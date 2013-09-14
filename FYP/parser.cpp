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
		Object* currObj = NULL;
		// std::vector<Vertex*> vertices;
        
        std::vector<Vec3> vertexCoords;
        std::vector<Vec3> vertexNormals;
        
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

				// Vertex* newVertex = new Vertex(coords);

				// vertices.push_back(newVertex);

            } else if (item == "vn") { // vertex normal
                float normals[3];
                
                for (int i = 0; getline(ss, item, ' '); i++) {
                    normals[i] = atof(item.c_str());
                }
                
                vertexNormals.push_back(Vec3(normals));
                
			} else if (item == "f") { // face
                Face* f = new Face;

				for (int i = 0; getline(ss, item, ' '); i++) {
                    char str[item.length()];
                    std::strcpy(str, item.c_str());
                    
                    char* pch;
                    
                    pch = std::strtok(str, "//");
                    int vertexIndex = atof(pch) - 1;
                    
                    pch = std::strtok(NULL, "//");
                    int normalIndex = atof(pch) - 1;
                    
                    Vertex* v;
                    auto result = vertices.find(vertexIndex);
                    
                    if (result == vertices.end()) { // cannot find vertex with index
                        v = new Vertex(vertexCoords[vertexIndex], vertexNormals[normalIndex]);
                        vertices.insert(std::pair<int, Vertex*>(vertexIndex, v));
                    } else {
                        v = result->second;
                    }
                    
                    f->addVertex(v);
                    // std::cout << *f << std::cout;
				}
                currObj->addFace(f);
			} else if (item == "usemtl") { // material
                getline(ss, item, ' ');
                currObj->materialName = item;
            }
		}
        
        for (Face* f : currObj->getFaces()) {
            std::cout << *f << std::endl;
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
