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



void Material::loadUniforms() {

    if(diffuseColor == NULL) diffuseColor = glm::vec4(1, 1, 1, 1);

    GLint loc = -1;
    for(int i = 0; i < uniforms.size(); i++) {
        if(uniforms[i].compare(DIFFUSE_COLOR)) {
            loc = glGetUniformLocation(shaderProgram, DIFFUSE_COLOR);
            if (loc != -1) glUniform4fv(loc, 1, &diffuseColor[0]);

        } else if(uniforms[i].compare(DIFFUSE_TEXTURE)) {
            loc = glGetUniformLocation(shaderProgram, DIFFUSE_TEXTURE);


        }


    }
}

void Material::loadTextures() {
    if(diffuseColor == NULL) diffuseColor = glm::vec4(1, 1, 1, 1);

    GLint loc = -1;

    for (int i = 0; i< (int) textures.size(); i++) {
        if (textures[i]->textureId == -1) {
            loc = glGetUniformLocation(shaderProgram, textures[i]->name.c_str());
            textures[i]->id = loc;
        }
        if (textures[i]->id >= 0) {
            glActiveTexture(GL_TEXTURE0 + i);
            glUniform1i(textures[i]->id, i);
            glBindTexture(GL_TEXTURE_2D, textures[i]->textureId);
            glBindSampler(textures[i]->id, textures[i]->samplerId);
        }
    }


}
