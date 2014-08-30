//
// Created by Marcus Gabilheri on 8/30/14.
// Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//


#ifndef __MeshInstance_H_
#define __MeshInstance_H_

#include <iostream>
#include "json11.hpp"
#import "MeshInstance.h"
#include <glm/glm.hpp>
#include <vector>
#include <GL/glew.h>
#include "Utils.h"
#include "Camera.h"

using namespace std;
using namespace glm;
using namespace json11;

class MeshInstance {

public:
    GLuint shaderProgram;
    
    // replace with material
    glm::vec4 diffuseColor;
    RGBAImage diffuseTexture;
    
    Transform T;
	
public:
    
    MeshInstance() {};
    
    void setShader(GLuint shader) { shaderProgram = shader; }
    void setDiffuseColor(const glm::vec4 &c) { diffuseColor = c; }
    void setScale(const glm::vec3 &s) { T.scale = s; }
    void setRotation(const glm::quat &r) { T.rotation = r; }
    void setTranslation(const glm::vec3 &t) { T.translation = t; }
    
    void refreshTransform(void);
    
    void draw(SceneCamera &camera);
    

};


#endif //__MeshInstance_H_
