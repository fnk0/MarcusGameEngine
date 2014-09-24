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

class Material {


private:
    std::vector<std::string> uniforms;
    std::string name;
    std::vector<NameIdColor> colors;
    std::vector<RGBAImage*> textures;
    glm::vec4 diffuseColor;
    GLuint shaderProgram;

public:

    basic_string<char, char_traits<char>, allocator<char>> const &getName() const {
        return name;
    }

    void setName(basic_string<char, char_traits<char>, allocator<char>> const &name) {
        Material::name = name;
    }

    vector<NameIdColor> const &getColors() const {
        return colors;
    }

    void setColors(vector<NameIdColor> const &colors) {
        Material::colors = colors;
    }

    vector<RGBAImage *> const &getTextures() const {
        return textures;
    }

    void setTextures(vector<RGBAImage *> const &textures) {
        Material::textures = textures;
    }

    GLuint getShaderProgram() const {
        return shaderProgram;
    }

    void setShaderProgram(GLuint shaderProgram) {
        Material::shaderProgram = shaderProgram;
    }


    vector<string> const &getUniforms() const {
        return uniforms;
    }

    void setUniforms(vector<string> const &uniforms) {
        Material::uniforms = uniforms;
    }

    glm::vec4 const &getDiffuseColor() const {
        return diffuseColor;
    }

    void setDiffuseColor(glm::vec4 const &diffuseColor) {
        Material::diffuseColor = diffuseColor;
    }

    void loadUniforms();
    void loadTextures();
};

class NameIdColor {

private:
    std::string name;
    GLuint  id;
    glm::vec4 color;

public:
    std::basic_string<char, std::char_traits<char>, std::allocator<char>> const &getName() const {
        return name;
    }

    void setName(std::basic_string<char, std::char_traits<char>, std::allocator<char>> const &name) {
        NameIdColor::name = name;
    }

    GLuint getId() const {
        return id;
    }

    void setId(GLuint id) {
        NameIdColor::id = id;
    }

    glm::vec4 const &getColor() const {
        return color;
    }

    void setColor(glm::vec4 const &color) {
        NameIdColor::color = color;
    }
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
