#include "parser.h"

ObjKVPair::ObjKVPair(const string& k, const string& v) : key(k), value(v) {}

const string& ObjFileNode::getType() {
    return getOneValue("TYPE");
}

const string& ObjFileNode::getName() {
    return getOneValue("NAME");
}

const string& ObjFileNode::getOneValue(const string &key) {
    for (ObjKVPair& pair : kvPairs) {
        if (pair.key == key) {
            return pair.value;
        }
    }
}

void ObjFileNode::addKVPair(const string &key, const string &value) {
    kvPairs.push_back(ObjKVPair(key, value));
}

bool Parser::isNewNodeSymbol(string symbol) {
    return symbol == "o" || symbol == "l" || symbol == "mtllib" || symbol == "newmtl";
}

Scene* Parser::parseFile(string filename) {
    vector<string> lines;
    
    ifstream objInput(filename.c_str());
    filename.replace(filename.length() - 3, 3, "mtl");
    ifstream mtlInput(filename);
    
    int tmp, pos = 0;
    int lastIndex;
    while ((tmp = filename.find(SLASH, pos)) != string::npos) {
        pos = tmp + 1;
        lastIndex = tmp;
    }
    
    directory = filename.substr(0, lastIndex);
    
    for (string line; getline(objInput, line); ) {
        lines.push_back(line);
    }
    
    for (string line; getline(mtlInput, line); ) {
        lines.push_back(line);
    }
    
    ObjFileNode* currNode;
    
    for (string& line : lines ) {
        stringstream ss(line);
        string key, value;
        
        getline(ss, key, ' ');
        getline(ss, value, '\n');
        
        if (!key.empty() && key != "#") {
            if (isNewNodeSymbol(key)) { // symbol mean start of new node
                currNode = new ObjFileNode;
                fileNodes.push_back(currNode);
                currNode->addKVPair("TYPE", key);
                currNode->addKVPair("NAME", value);
            } else { // normal symbol that does not start any node
                currNode->addKVPair(key, value);
            }
        }
    }
    
    Scene* scene = new Scene;
    
    for (ObjFileNode* node : fileNodes) {
        string nodeType = node->getType();
        if (nodeType == "o") { // object
            Object* obj = processObject(node);
            scene->addObject(obj);
            
            if (obj->isLight()) {
                scene->addLight(static_cast<_Light*>(obj));
            }
        } else if (nodeType == "l") { // light
            // scene->addLight(processLight(node));
        }
    }
    
    scenePostProcess(scene);
    return scene;
}

Object* Parser::processObject(ObjFileNode* node) {
    Object* obj = new Object;
    for (ObjKVPair& pair : node->kvPairs) {
        if (pair.key == "v") { // vertex position
            Vec3 v = processVec3(pair.value);
            vertexCoords.push_back(v);
        } else if (pair.key == "vn") { // vertex normal
            Vec3 vn = processVec3(pair.value);
            vertexNormals.push_back(vn);
        } else if (pair.key == "vt") { // vertex texture coordinate
            Vec3 vt = processVec3(pair.value);
            vertexTexCoords.push_back(vt);
        } else if (pair.key == "f") { // face
            Face* f = processFace(pair.value);
            obj->addFace(f);
        } else if (pair.key == "usemtl") { // material
            for (ObjFileNode* node : fileNodes) {
                if (node->getType() == "newmtl" && node->getName() == pair.value) { // is material and name match
                    obj->mat = processMaterial(node);
                }
            }
        } else if (pair.key == "@smooth") { // smooth
            obj->smoothShading = (pair.value == "on");
        }
    }
    return obj;
}

Light* Parser::processLight(ObjFileNode *node) {
    Light* light;
    string lightType = node->getOneValue("lighttype");
    
    if (lightType == "POINT") {
        light = new PointLight;
    }
    
    for (ObjKVPair& pair : node->kvPairs) {
        if (pair.key == "pos") {
            PointLight* pl = static_cast<PointLight*>(light);
            pl->position = processVec3(pair.value);
        } else if (pair.key == "energy") {
            light->energy = atof(pair.value.c_str());
        } else if (pair.key == "color") {
            light->color = processVec3(pair.value);
        } else if (pair.key == "size") {
            
        }
    }
    return light;
}

Material* Parser::processMaterial(ObjFileNode *node) {
    Material* mat = new Material(node->getName());
    
    for (ObjKVPair& pair : node->kvPairs) {
        if (pair.key == "Ke") {
            mat->ke = atof(pair.value.c_str());
        } else if (pair.key == "Ka") {
            mat->ka = processVec3(pair.value);
        } else if (pair.key == "Kd") {
            mat->kd = processVec3(pair.value);
        } else if (pair.key == "Ks") {
            mat->ks = processVec3(pair.value);
        } else if (pair.key == "map_Kd") {
            QPixmap map((directory + "/" + pair.value).c_str());
            mat->diffuseMap = new QImage(map.toImage());
        } else if (pair.key == "map_Disp") {
            QPixmap map((directory + "/" + pair.value).c_str());
            mat->displacementMap = new QImage(map.toImage());
        } else if (pair.key == "map_Ks") {
            QPixmap map((directory + "/" + pair.value).c_str());
            mat->specularMap = new QImage(map.toImage());
        } else if (pair.key == "Alpha") {
            mat->alpha = atof(pair.value.c_str());
        } else if (pair.key == "IOR") {
            mat->ior = atof(pair.value.c_str());
            mat->ior_inverse = 1.0f / mat->ior;
            
            if (abs(mat->ior - 1.0f) < 0.0001f) {
                mat->isTransmissive = false;
            } else {
                mat->isTransmissive = true;
            }
        } else if (pair.key == "RefractGloss") {
            mat->refractGloss = atof(pair.value.c_str());
        } else if (pair.key == "ReflectFactor") {
            mat->reflectFactor = atof(pair.value.c_str());
        } else if (pair.key == "ReflectGloss") {
            mat->reflectGloss = atof(pair.value.c_str());
        }
    }
    
    return mat;
}

Vec3 Parser::processVec3(const string &s) {
    stringstream ss(s);
    string item;
    
    float coords[3] = { 0.f, 0.f, 0.f };
    
    for (int i = 0; getline(ss, item, ' '); i++) {
        coords[i] = atof(item.c_str());
    }
    
    return Vec3(coords);
}

Face* Parser::processFace(const string &s) {
    stringstream ss(s);
    string item;
    
    Face* face = new Face;
    
    for (int i = 0; getline(ss, item, ' '); i++) { // item is in the format <P>/<T>/<N>
        stringstream _ss(item);
        string index;
        
        getline(_ss, index, '/');
        int vertexIndex = atof(index.c_str()) - 1;
        Vertex* v = new Vertex(vertexCoords[vertexIndex]);
        
        getline(_ss, index, '/');
        if (index.length() > 0) {
            int texIndex = atof(index.c_str()) - 1;
            v->setTexCoords(vertexTexCoords[texIndex]);
        }
        
        getline(_ss, index, '/');
        if (index.length() > 0) {
            int normalIndex = atof(index.c_str()) - 1;
            v->setNormal(vertexNormals[normalIndex]);
        }
        
        face->vertices[i] = v;
    }
    return face;
}

void Parser::scenePostProcess(Scene *scene) {
    for (Object* obj : scene->getObjects()) {
        for (Face* f : obj->getFaces()) {
            f->calculateFaceNormal();
            f->calculateTangentSpace();
        }
    }
    
    /*
    for (Light* l : scene->getLights()) {
        l->setScene(scene);
    }
    */
    
    for (Object* obj : scene->getObjects()) {
        float maxX = -FLT_MAX, maxY = -FLT_MAX, maxZ = -FLT_MAX;
        float minX = FLT_MAX, minY = FLT_MAX, minZ = FLT_MAX;
        
        for (Face* f : obj->getFaces()) {
            for (Vertex* v : f->vertices) {
                const Vec3& pos = v->pos;
                maxX = pos.x > maxX ? pos.x : maxX;
                maxY = pos.y > maxY ? pos.y : maxY;
                maxZ = pos.z > maxZ ? pos.z : maxZ;
                
                minX = pos.x < minX ? pos.x : minX;
                minY = pos.y < minY ? pos.y : minY;
                minZ = pos.z < minZ ? pos.z : minZ;
            }
        }
        
        obj->buildBox(Vec3(minX, minY, minZ), Vec3(maxX, maxY, maxZ));
    }
    
    scene->buildBox();
}

