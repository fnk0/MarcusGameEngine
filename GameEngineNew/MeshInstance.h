//
// Created by Marcus Gabilheri on 9/4/14.
// Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#ifndef __GameEngineNew__MeshInstance__
#define __GameEngineNew__MeshInstance__

#include "Mesh.h"
#include "SceneCamera.h"

class MeshInstance {

public:
    Mesh *mesh;
    GLuint shaderProgram;

    // Replace with material
    glm::vec4 diffuseColor;
    RGBAImage diffuseTexture;

    Transform T;

public:
    MeshInstance(void);

    void setMesh(Mesh *mesh) {MeshInstance::mesh = mesh; }
    void setShader(GLuint shader) { shaderProgram = shader; }
    void setDiffuseColor(const glm::vec4 &c) { diffuseColor = c; }
    void setScale(const glm::vec3 &s) { T.scale = s; }
    void setRotation(const glm::quat &r) { T.rotation = r; }
    void setTranslation(const glm::vec3 &t) { T.translation = t; }

    void refreshTransform(void);

    void draw(SceneCamera &camera);


    Mesh *getMesh() const {
        return mesh;
    }

    GLuint getShaderProgram() const {
        return shaderProgram;
    }

    void setShaderProgram(GLuint shaderProgram) {
        MeshInstance::shaderProgram = shaderProgram;
    }

    glm::detail::tvec4<float, glm::highp> const &getDiffuseColor() const {
        return diffuseColor;
    }

    RGBAImage const &getDiffuseTexture() const {
        return diffuseTexture;
    }

    void setDiffuseTexture(RGBAImage const &diffuseTexture) {
        MeshInstance::diffuseTexture = diffuseTexture;
    }

    Transform const &getT() const {
        return T;
    }

    void setT(Transform const &T) {
        MeshInstance::T = T;
    }
};


#endif //__MeshInstance_H_
