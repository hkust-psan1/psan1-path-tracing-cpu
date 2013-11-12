#include <iostream>
#include <fstream>
#include <sstream>

#include "object.h"
#include "light.h"
#include "scene.h"
using namespace std;

#define SLASH '/'

class ObjKVPair {
public:
    ObjKVPair(const string& k, const string& v);
    string key;
    string value;
};

class ObjFileNode {
public:
    void addKVPair(const string& key, const string& value);
    const string& getType();
    const string& getName();
    
    // get one value corresponding to the given key
    const string& getOneValue(const string& key);
    vector<ObjKVPair> kvPairs;
};

class Parser {
public:
    Scene* parseFile(std::string filename);
    
    void scenePostProcess(Scene* scene);
    
    // check if a symbol mean the start of a new node
    bool isNewNodeSymbol(string symbol);
    
    Object* processObject(ObjFileNode* node);
    Light* processLight(ObjFileNode* node);
    Material* processMaterial(ObjFileNode* node);
    Face* processFace(const string& s);
    
    Vec3 processVec3(const string& s);
    
private:
    string directory;
    
    vector<Vec3> vertexCoords;
    vector<Vec3> vertexNormals;
    vector<Vec3> vertexTexCoords;
    
    vector<ObjFileNode*> fileNodes;
};
