//
//  ThirdPersonScript.cpp
//  GameEngineNew
//
//  Created by Dawkins on 12/4/14.
//  Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#include "ThirdPersonScript.h"

void ThirdPersonScript::refreshCamera() {
    
    this->scene->getCamera()->setEye(this->scene->getPlayerNode()->T.translation + (this->scene->getPlayerNode()->T.rotation * glm::vec3(0,0, -1)) * 20.0f + 5.0f * glm::vec3(0,1,0));
    this->scene->getCamera()->setCenter(this->scene->getPlayerNode()->T.translation + 3.0f * glm::vec3(0,1,0));
    this->scene->getCamera()->refreshTransform(this->scene->getWorldSettings()->getWidth(), this->scene->getWorldSettings()->getHeight());
}


void ThirdPersonScript::shootBullet() {

    if(glfwGetKey(this->scene->getGWindow(), GLFW_KEY_SPACE)) {

    }
}

void ThirdPersonScript::pressA() {
    glm::vec3 strifeLeft(0.5, 0, 0);
    this->scene->getPlayerNode()->translateLocal(strifeLeft);
    this->getNode()->aPressed = true;
    this->refreshCamera();
}

void ThirdPersonScript::pressD() {
    glm::vec3 strifeRight(-0.5, 0, 0);
    this->scene->getPlayerNode()->translateLocal(strifeRight);
    this->getNode()->dPressed = true;
    this->refreshCamera();;
}

void ThirdPersonScript::pressW() {
    glm::vec3 strifeUp(0, 0, 1);
    this->scene->getPlayerNode()->translateLocal(strifeUp);
    this->getNode()->wPressed = true;
    this->refreshCamera();
}

void ThirdPersonScript::pressS() {
    glm::vec3 strifeDown(0, 0, -1);
    this->scene->getPlayerNode()->translateLocal(strifeDown);
    this->getNode()->sPressed = true;
    this->refreshCamera();
}

void ThirdPersonScript::pressQ() {
    glm::vec3 rotate(0, 0.5, 0);
    this->scene->getPlayerNode()->T.rotateGlobal(rotate, r);
    this->refreshCamera();
}

void ThirdPersonScript::pressE() {
    glm::vec3 rotate(0, 0.5, 0);
    this->scene->getPlayerNode()->T.rotateGlobal(rotate, -r);
    this->refreshCamera();
}
