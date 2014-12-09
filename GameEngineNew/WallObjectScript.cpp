//
// Created by Marcus Gabilheri on 12/8/14.
// Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#include "WallObjectScript.h"


void WallObjectScript::run() {
    GameObjectScript::run();
}

void WallObjectScript::refreshCamera() {

    this->getNode()->scene->getCamera()->setEye(this->getNode()->scene->getPlayerNode()->T.translation + (this->getNode()->scene->getPlayerNode()->T.rotation * glm::vec3(0,0, -1)) * 20.0f + 5.0f * glm::vec3(0,1,0));
    this->getNode()->scene->getCamera()->setCenter(this->getNode()->scene->getPlayerNode()->T.translation + 3.0f * glm::vec3(0,1,0));
    this->getNode()->scene->getCamera()->refreshTransform(this->scene->getWorldSettings()->getWidth(), this->scene->getWorldSettings()->getHeight());
}

void WallObjectScript::doAction() {

    glm::vec3 strifeDown(0, 0, -1);
    this->getNode()->scene->getPlayerNode()->translateLocal(strifeDown);
    this->refreshCamera();

}
