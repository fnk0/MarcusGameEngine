//
// Created by Marcus Gabilheri on 9/4/14.
// Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#include "SceneCamera.h"

void SceneCamera::refreshTransform(float screenWidth, float screenHeight)
{
    glm::mat4x4 worldView = glm::lookAt(eye, center, vup);
    glm::mat4x4 project = glm::perspective((float)fovy,
            (float)(screenWidth / screenHeight), (float)znear, (float)zfar);
    worldViewProject = project * worldView;
}