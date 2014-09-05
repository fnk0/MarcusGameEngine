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

    // Inefficient.  Looks up uniforms by string every time.
    // Setting the uniforms should probably part of a Material
    // class.

    GLint loc = glGetUniformLocation(shaderProgram, "uDiffuseColor");
    if (loc != -1) glUniform4fv(loc, 1, &diffuseColor[0]);

    loc = glGetUniformLocation(shaderProgram, "uDiffuseTex");
    glBindTexture(GL_TEXTURE_2D, diffuseTexture.textureId);
    if (loc != -1) glBindSampler(loc, diffuseTexture.samplerId);
    else ERROR("Could not bind texture", false);
    //printVec(color);

    //cout << "Scale: " << T.scale.x << " " << T.scale.y << " " << T.scale.z << "\n";

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

    mesh->draw();
}
//-------------------------------------------------------------------------//

