//
// Created by Marcus Gabilheri on 8/30/14.
// Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//


#ifndef __Mesh_H_
#define __Mesh_H_

#include <iostream>
#include "json11.hpp"
#import "MeshInstance.h"
#include <glm/glm.hpp>
#include <vector>
#include <GL/glew.h>
#include "Utils.h"

using namespace std;
using namespace glm;
using namespace json11;

class Mesh {

private:
    string meshName;
    string fileName;
    vector<MeshInstance> meshInstances;
    vector<string> attributes;
    vector<float> vertexData;
    vector<int> indices;
    
    Utils utils;

public:
    
    Mesh() {}
    
    int numIndices;
    GLuint vao; // vertex array handle
    GLuint ibo; // index buffer handle

    basic_string<char, char_traits<char>, allocator<char>> const &getMeshName() const {
        return meshName;
    }

    void setMeshName(basic_string<char, char_traits<char>, allocator<char>> const &meshName) {
        Mesh::meshName = meshName;
    }

    basic_string<char, char_traits<char>, allocator<char>> const &getFileName() const {
        return fileName;
    }

    void setFileName(basic_string<char, char_traits<char>, allocator<char>> const &fileName) {
        Mesh::fileName = fileName;
    }

    vector<MeshInstance> const &getMeshInstances() const {
        return meshInstances;
    }

    void setMeshInstances(vector<MeshInstance> const &meshInstances) {
        Mesh::meshInstances = meshInstances;
    }
    
    vector<string> const &getAttributes() const {
        return attributes;
    }
    
    void setAttributes(vector<string> const &attrs) {
        Mesh::attributes = attrs;
    }
    
    vector<float> const &getVertexData() const {
        return vertexData;
    }
    
    void setVertexData(vector<float> const &vData) {
        Mesh::vertexData = vData;
    }
    
    vector<int> getIndices(void) {
        return indices;
    }
    
    void setIndices(vector<int> const &indices) {
        Mesh::indices = indices;
    }

    Utils getUtils() {
        return utils;
    }
    
    bool readFromPly(const string &fileName, bool flipz = false);
    bool sendToOpenGL(void);
    void draw(void);
};


#endif //__Mesh_H_
