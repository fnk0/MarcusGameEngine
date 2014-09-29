//
// Created by Marcus Gabilheri on 9/13/14.
// Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#include "Material.h"

#define DIFFUSE_COLOR "uDiffuseColor"
#define DIFFUSE_TEXTURE "uDiffuseTex"
#define SPECULAR_TEXTURE "uSpecularTexture"
#define OBJECT_WORLD_M "uObjectWorldM"
#define OBJECT_WORLD_INVERSE_M "uObjectWorldInverseM"
#define OBJECT_PERSPECT_M "uObjectPerpsectM"


void Material::loadColors() {

    GLint loc = -1;

    for(int i = 0; i < (int) colors.size(); i++) {
        if(colors[i].getId() == -1) {
            loc = glGetUniformLocation(shaderProgram, colors[i].getName().c_str());
            colors[i].setId(loc);
        }
        if(colors[i].getId() >= 0) {
            glUniform4fv(loc, 1, &colors[i].getColor()[0]);


        }
    }
}

void Material::loadTextures() {

    GLint loc = -1;

    for (int i = 0; i< (int) textures.size(); i++) {
        if (textures[i].getId() == -1) {
            loc = glGetUniformLocation(shaderProgram, textures[i].getName().c_str());
            textures[i].setId(loc);
        }
        if (textures[i].getId() >= 0) {
            glActiveTexture(GL_TEXTURE0 + i);
            glUniform1i(textures[i].getId(), i);
            glBindTexture(GL_TEXTURE_2D, textures[i].getTexture()->textureId);
            glBindSampler(textures[i].getId(), textures[i].getTexture()->samplerId);
        }
    }
}
