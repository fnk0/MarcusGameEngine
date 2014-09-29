//
// Created by Marcus Gabilheri on 9/4/14.
// Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#include "MeshInstance.h"

//-------------------------------------------------------------------------//

MeshInstance::MeshInstance(void)
{
    mesh = NULL;
    shaderProgram = NULL_HANDLE;
    diffuseColor = glm::vec4(1, 1, 1, 1);
}

//-------------------------------------------------------------------------//

void MeshInstance::draw(SceneCamera &camera)
{
    glUseProgram(shaderProgram);

    GLint loc = -1;

    material.setShaderProgram(shaderProgram);

    material.loadColors();
    material.loadTextures();
    scene->loadLights(shaderProgram);

    T.refreshTransform();
    //printMat(transform);

    loc = glGetUniformLocation(shaderProgram, "uObjectWorldM");
    if (loc != -1) glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(T.transform));
    //else ERROR("Could not load uniform uObjectWorldM", false);

    loc = glGetUniformLocation(shaderProgram, "uObjectWorldInverseM");
    if (loc != -1) glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(T.invTransform));
    //else ERROR("Could not load uniform mnesuObjectWorldInverseM", false);

    glm::mat4x4 objectWorldViewPerspect = camera.getWorldViewProject() * T.transform;
    loc = glGetUniformLocation(shaderProgram, "uObjectPerpsectM");
    if (loc != -1) glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(objectWorldViewPerspect));
    //else ERROR("Could not load uniform uObjectPerpsectM", false);
    if(mesh != NULL)
        mesh->draw();
}
//-------------------------------------------------------------------------//

