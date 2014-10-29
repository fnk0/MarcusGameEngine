//
// Created by Marcus Gabilheri on 9/4/14.
// Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#include "MeshInstance.h"

//-------------------------------------------------------------------------//

MeshInstance::MeshInstance(void)
{
    mesh = NULL;
}

//-------------------------------------------------------------------------//

void MeshInstance::draw(SceneCamera &camera)
{
    if (mesh != NULL) mesh->draw();
    else printf("Error! Null Mesh.");
}
//-------------------------------------------------------------------------//

