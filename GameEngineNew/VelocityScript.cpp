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
    Node *node = getNode();
    Scene *scene = node->getScene();
    glm::vec3 velocity = node->getVelocity();
    float increment = 0.1;
    float e = increment * TIMESTEP;
    
    Node* intersectingNode = this->intersects();
    if(intersectingNode != nullptr) {
        VelocityScript::doAction(intersectingNode);
    }
    else {
        if((node->T.translation.x >= 15) || (node->T.translation.x <= 0)) {
            glm::vec3 newVelocity = glm::vec3(-1.0 * velocity.x, velocity.y, velocity.z); // Reverse direction of travel on x axis.
            node->setVelocity(newVelocity);
        }
        if((node->T.translation.y >= 15) || (node->T.translation.y <= 0)) {
            glm::vec3 newVelocity = glm::vec3(velocity.x, -1.0 * velocity.y, velocity.z); // Reverse direction of travel on y axis.
            node->setVelocity(newVelocity);
        }
        if((node->T.translation.z >= 15) || (node->T.translation.z <= 0)) {
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
        }
    }
};

Node* VelocityScript::intersects() {
    bool didCollide = false;
    Scene* scene = getNode()->getScene();
    const map<std::string, Node*> map = scene->getMapNodes();
    for(auto outer_iter = map.begin(); outer_iter != map.end(); outer_iter++) {
        /*if(getNode()->getName() == "player") {
            printVec(getNode()->T.translation);
        }*/
        if(getNode()->getName() != outer_iter->second->getName()) {
            float dotProduct = glm::dot(getNode()->T.translation - outer_iter->second->T.translation, getNode()->T.translation - outer_iter->second->T.translation);
            float dSquared = (getNode()->getRadius() + outer_iter->second->getRadius())*(getNode()->getRadius() + outer_iter->second->getRadius());
            didCollide = dotProduct < dSquared;
            if(didCollide) {
                //printf("dot product: %f\n", dotProduct);
                //printf("dSquared: %f\n", dSquared);
                //printVec(getNode()->T.translation);
                //printVec(outer_iter->second->T.translation);
                Node* collisionNode = outer_iter->second;
                return collisionNode;
            }
        }
    }
    return nullptr;
}

void VelocityScript::doAction(Node* intersectingNode) {
    const float kSpring = 250.0;
    const float TIMESTEP = float(1.0/60.0);
    Node* currentNode = getNode();
    glm::vec3 distance = intersectingNode->T.translation - currentNode->T.translation;
    printVec(distance);
    
    glm::vec3 FD = glm::normalize(distance);
    float mass0 = currentNode->getMass();
    float mass1 = intersectingNode->getMass();
    currentNode->accelerate((-FD * kSpring)/mass0, TIMESTEP);
    intersectingNode->accelerate((FD * kSpring)/mass1, TIMESTEP);
}
