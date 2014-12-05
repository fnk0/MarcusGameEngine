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
        if(colors[i].id == -1) {
            loc = glGetUniformLocation(shaderProgram, colors[i].name.c_str());
            colors[i].id = loc;
        }
        if(colors[i].id >= 0) {
            glUniform4fv(loc, 1, &colors[i].val[0]);
        }
    }
}

void Material::loadTextures() {

    GLint loc = -1;

    for (int i = 0; i< (int) textures.size(); i++) {
        if (textures[i].id == -1) {
            loc = glGetUniformLocation(shaderProgram, textures[i].name.c_str());
            textures[i].id = loc;
        }
        if (textures[i].id >= 0) {
            glActiveTexture(GL_TEXTURE0 + i);
            glUniform1i(textures[i].id, i);
            glBindTexture(GL_TEXTURE_2D, textures[i].val->textureId);
            glBindSampler(textures[i].id, textures[i].val->samplerId);
        }
    }
}

void Material::bindMaterial(Transform &T, SceneCamera &camera)
{
    glUseProgram(shaderProgram);

    // MATRICES FROM TRANSFORM
    GLint loc = glGetUniformLocation(shaderProgram, OBJECT_WORLD_M);
    if (loc != -1) glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(T.transform));
    //
    loc = glGetUniformLocation(shaderProgram, OBJECT_WORLD_INVERSE_M);
    if (loc != -1) glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(T.invTransform));
    //
    glm::mat4x4 objectWorldViewPerspect = camera.getWorldViewProject() * T.transform;
    loc = glGetUniformLocation(shaderProgram, OBJECT_PERSPECT_M);
    if (loc != -1) glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(objectWorldViewPerspect));
    
    printMat(T.transform);
    
    // MATERIAL COLOR
    for (int i = 0; i < (int) colors.size(); i++) {
        if (colors[i].id == -1) {
            loc = glGetUniformLocation(shaderProgram, colors[i].name.c_str());
            colors[i].id = loc;
        }
        if (colors[i].id >= 0) {
            glUniform4fv(colors[i].id, 1, &colors[i].val[0]);
        }
    }

    // MATERIAL TEXTURES
    for (int i = 0; i < (int) textures.size(); i++) {
        if (textures[i].id == -1) {
            loc = glGetUniformLocation(shaderProgram, textures[i].name.c_str());
            textures[i].id = loc;
        }
        if (textures[i].id >= 0) {
            //printf("\n%d %d\n", textures[i].id, textures[i].val->samplerId);
            glActiveTexture(GL_TEXTURE0 + i);
            glUniform1i(textures[i].id, i);
            glBindTexture(GL_TEXTURE_2D, textures[i].val->textureId);
            glBindSampler(textures[i].id, textures[i].val->samplerId);
        }
    }
}