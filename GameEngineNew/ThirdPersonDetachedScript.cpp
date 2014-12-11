//
//  ThirdPersonDetachedScript.cpp
//  GameEngineNew
//
//  Created by POWERS VERONICA E on 12/10/14.
//  Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#include "ThirdPersonDetachedScript.h"

void ThirdPersonDetachedScript::run() {
    
    if(this->scene == nullptr) {
        this->scene = this->getNode()->getScene();
    }
    
    if(glfwGetKey(scene->gWindow, 'A')){
        MoveCameraScript::pressA();
    }
    if(glfwGetKey(scene->gWindow, 'D')){
        MoveCameraScript::pressD();
    }
    if(glfwGetKey(scene->gWindow, 'W')){
        MoveCameraScript::pressW();
    }
    if(glfwGetKey(scene->gWindow, 'S')){
        MoveCameraScript::pressS();
    }
    if(glfwGetKey(scene->gWindow, 'Q')){
        MoveCameraScript::pressQ();
    }
    if(glfwGetKey(scene->gWindow, 'E')){
        MoveCameraScript::pressE();
    }
    if(glfwGetKey(scene->gWindow, GLFW_KEY_UP)){
        MoveCameraScript::pressUp();
    }
    if(glfwGetKey(scene->gWindow, GLFW_KEY_DOWN)){
        MoveCameraScript::pressDown();
    }
    if(glfwGetKey(scene->gWindow, GLFW_KEY_LEFT)){
        MoveCameraScript::pressLeft();
    }
    if(glfwGetKey(scene->gWindow, GLFW_KEY_RIGHT)){
        MoveCameraScript::pressRight();
    }
    
    if(glfwGetKey(scene->gWindow, 'X')) {
        this->refreshCamera();
    }
}

void ThirdPersonDetachedScript::refreshCamera() {
    this->scene->getCamera()->setEye(this->scene->getPlayerNode()->T.translation + (this->scene->getPlayerNode()->T.rotation * glm::vec3(0,0, -1)) * 20.0f + 5.0f * glm::vec3(0,1,0));
    this->scene->getCamera()->setCenter(this->scene->getPlayerNode()->T.translation + 3.0f * glm::vec3(0,1,0));
    this->scene->getCamera()->refreshTransform(this->scene->getWorldSettings()->getWidth(), this->scene->getWorldSettings()->getHeight());

}