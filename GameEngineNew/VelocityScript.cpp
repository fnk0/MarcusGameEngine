//
//  VelocityScript.cpp
//  GameEngineNew
//
//  Created by POWERS VERONICA E on 12/7/14.
//  Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#include "VelocityScript.h"

void VelocityScript::run() {
    const float TIMESTEP = float(1.0/60.0);
    Node *node = this->getNode();
    Scene *scene = node->getScene();
    glm::vec3 velocity = node->getVelocity();
    float increment = 0.1;
    float e = increment * TIMESTEP;
    
    Node* intersectingNode = this->intersects();
    if(intersectingNode != nullptr) {
        VelocityScript::doAction(intersectingNode);
    }
    else {
        if((node->T.translation.x >= 7) || (node->T.translation.x <= 0)) {
            glm::vec3 newVelocity = glm::vec3(-1.0 * velocity.x, velocity.y, velocity.z); // Reverse direction of travel on x axis.
            node->setVelocity(newVelocity);
        }
        if((node->T.translation.y >= 7) || (node->T.translation.y <= 0)) {
            glm::vec3 newVelocity = glm::vec3(velocity.x, -1.0 * velocity.y, velocity.z); // Reverse direction of travel on y axis.
            node->setVelocity(newVelocity);
        }
        if((node->T.translation.z >= 7) || (node->T.translation.z <= 0)) {
            glm::vec3 newVelocity = glm::vec3(velocity.x, velocity.y, -1.0 * velocity.z); // Reverse direction of travel on z axis.
            node->setVelocity(newVelocity);
        }
        
        if(node->getName() == "player") {
            if(glfwGetKey(scene->gWindow, 'J')) { // Speed up in x direction
                if(velocity.x >= 0) node->accelerate(glm::vec3(increment, 0, 0), TIMESTEP);
                else node->accelerate(glm::vec3(-1.0 * increment, 0, 0), TIMESTEP);
            }
            if(glfwGetKey(scene->gWindow, 'K')) { // Slow down in x direction
                if(velocity.x > e) node->accelerate(glm::vec3(-1.0 * increment, 0, 0), TIMESTEP);
                else if(velocity.x < -e) node->accelerate(glm::vec3(increment, 0, 0), TIMESTEP);
                else node->accelerate(glm::vec3((-node->velocity.x)/TIMESTEP, 0, 0), TIMESTEP);  // Used to negate any small amount of velocity in the x direction.
            }
            if(glfwGetKey(scene->gWindow, 'L')) { // Speed up in y direction
                if(velocity.y >= 0) node->accelerate(glm::vec3(0, increment, 0), TIMESTEP);
                else node->accelerate(glm::vec3(0, -1.0 * increment, 0), TIMESTEP);
            }
            if(glfwGetKey(scene->gWindow, ';')) { // Slow down in y direction
                if(velocity.y > e) node->accelerate(glm::vec3(0, -1.0 * increment, 0), TIMESTEP);
                else if(velocity.y < -e) node->accelerate(glm::vec3(0, increment, 0), TIMESTEP);
                else node->accelerate(glm::vec3(0, (-node->velocity.y)/TIMESTEP, 0), TIMESTEP);  // Used to negate any small amount of velocity in the y direction.
            }
            if(glfwGetKey(scene->gWindow, 'U')) { // Speed up in z direction
                if(velocity.z >= 0) node->accelerate(glm::vec3(0, 0, increment), TIMESTEP);
                else node->accelerate(glm::vec3(0, 0, -1.0 * increment), TIMESTEP);
            }
            if(glfwGetKey(scene->gWindow, 'I')) { // Slow down in z direction
                if(velocity.z > e) node->accelerate(glm::vec3(0, 0, -1.0 * increment), TIMESTEP);
                else if(velocity.z < -e) node->accelerate(glm::vec3(0, 0, increment), TIMESTEP);
                else node->accelerate(glm::vec3(0, 0, (-node->velocity.z)/TIMESTEP), TIMESTEP);  // Used to negate any small amount of velocity in the z direction.
            }
            
            node->update(TIMESTEP);
        }
    }
};

Node* VelocityScript::intersects() {
    bool didCollide = false;
    Node* collisionNode;
    Scene* scene = this->getNode()->getScene();
    const map<std::string, Node*> map = scene->getMapNodes();
    for(auto outer_iter = map.begin(); outer_iter != map.end(); outer_iter++) {
        didCollide = glm::dot(this->getNode()->T.translation - outer_iter->second->T.translation, this->getNode()->T.translation - outer_iter->second->T.translation) < (0.5 + 0.7)*(0.5 + 0.7);  //radii
        if(didCollide) {
            collisionNode = outer_iter->second;
            break;
        }
    }
    return collisionNode;
}

void VelocityScript::doAction(Node* intersectingNode) {
    const float kSpring = 4.0;
    const float TIMESTEP = float(1.0/60.0);
    Node* currentNode = this->getNode();
    glm::vec3 distance = intersectingNode->T.translation - currentNode->T.translation;
    
    glm::vec3 FD = glm::normalize(distance);
    float mass0 = currentNode->getMass();
    float mass1 = intersectingNode->getMass();
    currentNode->accelerate((-FD * kSpring)/mass0, TIMESTEP);
    intersectingNode->accelerate((FD * kSpring)/mass1, TIMESTEP);
}
