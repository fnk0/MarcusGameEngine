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
    glm::vec3 strifeUp(0, 0, 1);
    glm::vec3 strifeRight(-0.5, 0, 0);
    glm::vec3 strifeLeft(0.5, 0, 0);
    if(this->getNode()->getScene()->getPlayerNode()->wPressed) {
        this->getNode()->scene->getPlayerNode()->translateLocal(strifeDown);
    }

    if(this->getNode()->getScene()->getPlayerNode()->aPressed) {
        this->getNode()->scene->getPlayerNode()->translateLocal(strifeRight);
    }

    if(this->getNode()->getScene()->getPlayerNode()->dPressed) {
        this->getNode()->scene->getPlayerNode()->translateLocal(strifeLeft);
    }

    if(this->getNode()->getScene()->getPlayerNode()->sPressed) {
        this->getNode()->scene->getPlayerNode()->translateLocal(strifeUp);
    }

    this->getNode()->getScene()->getPlayerNode()->wPressed = false;
    this->getNode()->getScene()->getPlayerNode()->aPressed = false;
    this->getNode()->getScene()->getPlayerNode()->sPressed = false;
    this->getNode()->getScene()->getPlayerNode()->dPressed = false;

    this->refreshCamera();

}


bool WallObjectScript::intersects() {
    glm::vec3 scale = this->getNode()->T.scale;
    //printVec(scale);
    glm::vec3 pScale = this->getNode()->getScene()->getPlayerNode()->T.scale;
    glm::vec3 wMax = this->getNode()->T.translation + scale;
    glm::vec3 wMin = this->getNode()->T.translation - scale;
    glm::vec3 pMax = this->getNode()->getScene()->getPlayerNode()->T.translation + pScale;
    glm::vec3 pMin = this->getNode()->getScene()->getPlayerNode()->T.translation - pScale;

    glm::vec3 iMin = glm::vec3(glm::max(wMin.x, pMin.x), glm::max(wMin.y, pMin.y), glm::max(wMin.z, pMin.z));
    glm::vec3 iMax = glm::vec3(glm::min(wMax.x, pMax.x), glm::min(wMax.y, pMax.y), glm::min(wMax.z, pMax.z));

    glm::vec3 diff = iMax - iMin;

    return diff.x > 0 && diff.y > 0 && diff.z > 0;
}
