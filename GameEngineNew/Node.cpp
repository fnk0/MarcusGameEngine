//
//  Node.cpp
//  GameEngineNew
//
//  Created by Marcus Gabilheri on 10/14/14.
//  Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#include "Node.h"


void Node::refreshTransforms() {

    Transform childrenTransform;

    for(int i = 0; i < nodes.size(); i++) {
        nodes[i]->refreshTransforms();
        childrenTransform.transform *= nodes[i]->T.transform;
    }
<<<<<<< HEAD
=======

>>>>>>> FETCH_HEAD
    if(parent != NULL) {
       T.transform *= parent->T.transform * childrenTransform.transform;
    } else {
        T.transform *= childrenTransform.transform;
    }
<<<<<<< HEAD
=======


>>>>>>> FETCH_HEAD
}

void Node::draw(glm::mat4x4 &mat, glm::mat4x4 &matInverse, SceneCamera &camera)
{
    T.refreshTransform();
    meshInstance->material.bindMaterial(T, camera);
    if (meshInstance != NULL) meshInstance->draw(camera);
    else printf("Error! Null Mesh.");
}
