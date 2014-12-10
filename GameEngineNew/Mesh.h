//
// Created by Marcus Gabilheri on 9/4/14.
// Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//


#ifndef __GameEngineNew__Mesh_H_
#define __GameEngineNew__Mesh_H_

#include "EngineUtil.h"

// Consider adding a Level of detail to the Mesh
// So if the camera is far away low polygon meshes can be loaded.

class Mesh {

public:
    std::string meshName;
    std::string meshFile;
    std::vector<std::string> attributes;
    std::vector<float> vertexData;
    std::vector<int> indices;
    int numIndices;

    GLuint vao; // vertex array handle
    GLuint ibo; // index buffer handle

public:

    bool readFromPly(const std::string &fileName, bool flipZ = false);
    bool sendToOpenGL(void);
    void draw(void);

    std::string getMeshName() const {
        return meshName;
    }

    void setMeshName(std::string meshName) {
        Mesh::meshName = meshName;
    }

    string getMeshFile() const {
        return meshFile;
    }

    void setMeshFile(string meshFile) {
        Mesh::meshFile = meshFile;
    }

    std::vector<std::string> const &getAttributes() const {
        return attributes;
    }

    void setAttributes(std::vector<std::string> const &attributes) {
        Mesh::attributes = attributes;
    }

    std::vector<float> const &getVertexData() const {
        return vertexData;
    }

    void setVertexData(std::vector<float> const &vertexData) {
        Mesh::vertexData = vertexData;
    }

    std::vector<int> const &getIndices() const {
        return indices;
    }

    void setIndices(std::vector<int> const &indices) {
        Mesh::indices = indices;
    }

    int getNumIndices() const {
        return numIndices;
    }

    void setNumIndices(int numIndices) {
        Mesh::numIndices = numIndices;
    }

    GLuint getVao() const {
        return vao;
    }

    void setVao(GLuint vao) {
        Mesh::vao = vao;
    }

    GLuint getIbo() const {
        return ibo;
    }

    void setIbo(GLuint ibo) {
        Mesh::ibo = ibo;
    }
};


#endif //__Mesh_H_
