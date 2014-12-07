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
    map<std::string, Node*> nodeMap = scene->getNodes();
    if(_parent != NULL) {
       //parent->T.refreshTransform();
       T.transform = T.transform * _parent->T.transform; //* childrenTransform.transform;
       for(int i = 0; i < nodes.size(); i++) {
           nodeMap[nodes[i]]->refreshTransforms();
       }
    }
}

//void Node::draw(glm::mat4x4 &mat, glm::mat4x4 &matInverse, SceneCamera &camera)
void Node::draw(SceneCamera &camera)
{
    
    this->refreshTransforms();
    
    if(this->isBillboard) {
        glm::vec3 cp = camera.getEye() - this->T.translation;
        //printVec(cp);
        float theta = atan2(cp.x, cp.z);
        //this->T.rotation = glm::normalize(glm::quat(-theta, glm::vec3(0, 1, 0)));
        
        glm::mat4x4 rotationMatrix = glm::mat4x4(
                cos(theta), 0.0, -sin(theta), 0.0,
                0.0, 1.0, 0.0, 0.0,
                sin(theta), 0.0, cos(theta), 0.0,
                0.0, 0.0, 0.0, 1.0);
        
        this->T.transform *= rotationMatrix;
    }
    
    if(this->scripts.size() > 0) {
        for(std::vector<Script*>::iterator it = this->scripts.begin(); it != this->scripts.end(); ++it) {
            (*it)->run();
        }
    }

    meshInstance->material.bindMaterial(T, camera);
    if (meshInstance != NULL) meshInstance->draw(camera);
    else printf("Error! Null Mesh.");
}

void Node::translateLocal(glm::vec3 &translation) {
    
    this->T.translateLocal(translation, *this->scene->getCamera());
}