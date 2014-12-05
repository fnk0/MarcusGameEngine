//
//  MoveCameraScript.cpp
//  GameEngineNew
//
//  Created by Dawkins on 12/4/14.
//  Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#include "MoveCameraScript.h"

void MoveCameraScript::run() {
    
    if(this->scene == nullptr) {
        this->scene = this->getNode()->getScene();
    }
    
    if(glfwGetKey(scene->gWindow, 'A')){
        this->pressA();
    }
    if(glfwGetKey(scene->gWindow, 'D')){
        this->pressD();
    }
    if(glfwGetKey(scene->gWindow, 'W')){
        this->pressW();
    }
    if(glfwGetKey(scene->gWindow, 'S')){
        this->pressS();
    }
    if(glfwGetKey(scene->gWindow, 'Q')){
        this->pressQ();
    }
    if(glfwGetKey(scene->gWindow, 'E')){
        this->pressE();
    }
    if(glfwGetKey(scene->gWindow, GLFW_KEY_UP)){
        this->pressUp();
    }
    if(glfwGetKey(scene->gWindow, GLFW_KEY_DOWN)){
        this->pressDown();
    }
    if(glfwGetKey(scene->gWindow, GLFW_KEY_LEFT)){
        this->pressLeft();
    }
    if(glfwGetKey(scene->gWindow, GLFW_KEY_RIGHT)){
        this->pressRight();
    }
    
    this->scene->getCamera()->refreshTransform(scene->getWorldSettings()->getWidth(), scene->getWorldSettings()->getHeight());
    
}

void MoveCameraScript::pressA() {
    glm::vec3 strifeLeft(-t, 0, 0);
    this->scene->getCamera()->translateLocal(strifeLeft);
}

void MoveCameraScript::pressD() {
    glm::vec3 strifeRight(t, 0, 0);
    scene->getCamera()->translateLocal(strifeRight);
}

void MoveCameraScript::pressW() {
    glm::vec3 strifeUp(0, t, -t);
    scene->getCamera()->translateLocal(strifeUp);
}

void MoveCameraScript::pressS() {
    glm::vec3 strifeDown(0, -t, t);
    scene->getCamera()->translateLocal(strifeDown);
}

void MoveCameraScript::pressQ() {
    glm::vec3 rotate(0, 1, 0);
    scene->getCamera()->rotateGlobal(rotate, r);
}

void MoveCameraScript::pressE() {
    glm::vec3 rotate(0, 1, 0);
    scene->getCamera()->rotateGlobal(rotate, -r);
}

void MoveCameraScript::pressUp() {
    glm::vec3 moveForward(0, 0, t);
    scene->getCamera()->translateLocal(moveForward);
}

void MoveCameraScript::pressDown() {
    glm::vec3 moveBack(0, 0, -t);
    scene->getCamera()->translateLocal(moveBack);
}

void MoveCameraScript::pressLeft() {
    glm::vec3 rotate(0, 1, 0);
    scene->getCamera()->rotateGlobal(rotate, r);
}

void MoveCameraScript::pressRight() {
    glm::vec3 rotate(0, 1, 0);
    scene->getCamera()->rotateGlobal(rotate, -r);
}