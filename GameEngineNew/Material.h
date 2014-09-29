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


class NameIdColor {

private:
    std::string name;
    GLint  id;
    glm::vec4 color;

public:
    std::basic_string<char, std::char_traits<char>, std::allocator<char>> const &getName() const {
        return name;
    }

    void setName(std::basic_string<char, std::char_traits<char>, std::allocator<char>> const &name) {
        NameIdColor::name = name;
    }

    GLint getId() const {
        return id;
    }

    void setId(GLint id) {
        NameIdColor::id = id;
    }

    glm::vec4 const &getColor() const {
        return color;
    }

    void setColor(glm::vec4 const &color) {
        NameIdColor::color = color;
    }
};

class NameIdTexture {

private:
    std::string name;
    GLint id;
    RGBAImage* texture;

public:
    basic_string<char, char_traits<char>, allocator<char>> const &getName() const {
        return name;
    }

    void setName(basic_string<char, char_traits<char>, allocator<char>> const &name) {
        NameIdTexture::name = name;
    }

    GLint getId() const {
        return id;
    }

    void setId(GLint id) {
        NameIdTexture::id = id;
    }

    RGBAImage *getTexture() const {
        return texture;
    }

    void setTexture(RGBAImage *texture) {
        NameIdTexture::texture = texture;
    }
};

class Material {

private:

    std::string name;
    std::vector<NameIdColor> colors;
    std::vector<NameIdTexture> textures;
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


    vector<NameIdTexture> const &getTextures() const {
        return textures;
    }

    void setTextures(vector<NameIdTexture> const &textures) {
        Material::textures = textures;
    }

    GLuint getShaderProgram() const {
        return shaderProgram;
    }

    void setShaderProgram(GLuint shaderProgram) {
        Material::shaderProgram = shaderProgram;
    }

    void addColor(NameIdColor &color) {
        colors.push_back(color);
    }

    void addTexture(NameIdTexture &texture) {
        textures.push_back(texture);
    }

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
