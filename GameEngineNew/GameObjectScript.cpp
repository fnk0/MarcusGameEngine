//
// Created by Marcus Gabilheri on 12/8/14.
// Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#include "GameObjectScript.h"

void GameObjectScript::run() {
    
    if(this->scene == nullptr) {
        this->scene = this->getNode()->getScene();
    }

    if(this->intersects()) {
        this->doAction();
        //std::cout << "Map Size: " << this->scene->getNodes().size() << std::endl;
    }
}

void GameObjectScript::doAction() {

}

bool GameObjectScript::intersects() {
    Node* playerNode = this->scene->getPlayerNode();

    return glm::dot(this->getNode()->T.translation - playerNode->T.translation, this->getNode()->T.translation - playerNode->T.translation) < (0.5 + 0.7)*(0.5 + 0.7);
}
