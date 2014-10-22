//
//  Node.cpp
//  GameEngineNew
//
//  Created by Marcus Gabilheri on 10/14/14.
//  Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#include "Node.h"


void Node::refreshTransforms() {
    /*
    Transform childrenTransform;
    for(int i = 0; i < nodes.size(); i++) {
        nodes[i]->refreshTransforms();
        childrenTransform.transform *= nodes[i]->T.transform;
    }
    */
    T.refreshTransform();

    Node* _parent = scene->getNodes()[this->parent];
    if(_parent != NULL) {
       //parent->T.refreshTransform();
       T.transform = T.transform * _parent->T.transform; //* childrenTransform.transform;
       for(int i = 0; i < nodes.size(); i++) {
           map<std::string, Node*> nodeMap = scene->getNodes();
           nodeMap[nodes[i]]->refreshTransforms();
       }
    }
}

//void Node::draw(glm::mat4x4 &mat, glm::mat4x4 &matInverse, SceneCamera &camera)
void Node::draw(SceneCamera &camera)
{
    this->refreshTransforms();
    meshInstance->setT(this->T);
    meshInstance->material.bindMaterial(T, camera);
    if (meshInstance != NULL) meshInstance->draw(camera);
    else printf("Error! Null Mesh.");
}
