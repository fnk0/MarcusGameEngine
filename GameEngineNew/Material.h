//
// Created by Marcus Gabilheri on 9/13/14.
// Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//


#ifndef __Material_H_
#define __Material_H_

#include <GL/glew.h>
#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec4.hpp>
#include <vector>
#include "iostream"
#include "EngineUtil.h"
#include "Light.h"
#include "SceneCamera.h"

//-------------------------------------------------------------------------//
// TEMPLATES
//-------------------------------------------------------------------------//

template<class T> class NameVal
{
public:
    string name;
    T val;
    NameVal() { name = ""; }
    NameVal(string &n, T &v) { name = n; val = v; }
};

template<class T> class NameIdVal
{
public:
    string name;
    int id;
    T val;
    NameIdVal() { name = ""; id = -1; }
    NameIdVal(string &n, int i, T &v) { name = n; id = i; val = v; }
};


class Material {

private:

    std::string name;
    vector< NameIdVal<glm::vec4> > colors;
    vector< NameIdVal<RGBAImage*> > textures;;
    GLuint shaderProgram;

public:

    basic_string<char, char_traits<char>, allocator<char>> const &getName() const {
        return name;
    }

    void setName(basic_string<char, char_traits<char>, allocator<char>> const &name) {
        Material::name = name;
    }


    vector<NameIdVal<glm::vec4>> const &getColors() const {
        return colors;
    }

    void setColors(vector<NameIdVal<glm::vec4>> const &colors) {
        Material::colors = colors;
    }

    vector<NameIdVal<RGBAImage *>> const &getTextures() const {
        return textures;
    }

    void setTextures(vector<NameIdVal<RGBAImage *>> const &textures) {
        Material::textures = textures;
    }

    GLuint getShaderProgram() const {
        return shaderProgram;
    }

    void setShaderProgram(GLuint shaderProgram) {
        Material::shaderProgram = shaderProgram;
    }

    void addColor(NameIdVal<glm::vec4> &color) {
        colors.push_back(color);
    }

    void addTexture(NameIdVal<RGBAImage*> &texture) {
        textures.push_back(texture);
    }

    // Sends all the data to OpenGL in 2 methods and more stuff too
    // Look at d2l for more info
    void bindMaterial(Transform &T, SceneCamera &camera);

    void loadLights();
    void loadColors();
    void loadTextures();
};



// THIS CODE SHOULD GO SOMEWHERE TO ALLOW MULTIPLE TEXTURES
/*
// MATERIAL TEXTURES
for (int i = 0; i< (int)textures.size(); i++) {
    if (textures[i].id == -1) {
        loc = glGetUniformLocation(shaderProgram, textures[i].name.c_str());
        textures[i].id = loc;
    }
    if (textures[i].id >= 0) {
        glActiveTexture(GL_TEXTURE0 + i);
        glUniform(textures[i].id, i);
        glBindTexture(GL_TEXTURE_2D, textures[i].val->textureId);
        glBindSampler(textures[i].id, textures[i].val->samplerId);
    }
}
*/
#endif //__Material_H_
