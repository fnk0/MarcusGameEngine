//
// Created by Marcus Gabilheri on 9/4/14.
// Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#include "MeshInstance.h"

//-------------------------------------------------------------------------//

MeshInstance::MeshInstance(void)
{
    mesh = NULL;
    T.scale = glm::vec3(1, 1, 1);
    T.translation = glm::vec3(0, 0, 0);
}

//-------------------------------------------------------------------------//

void MeshInstance::draw(SceneCamera &camera)
{
    T.refreshTransform();
    material.bindMaterial(T, camera);
    if (mesh != NULL) mesh->draw();
    else printf("Error! Null Mesh.");
}
//-------------------------------------------------------------------------//

