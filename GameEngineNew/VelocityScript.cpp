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
        if((node->T.translation.x >= 13) || (node->T.translation.x <= 7)) {
            glm::vec3 newVelocity = glm::vec3(-1.0 * velocity.x, velocity.y, velocity.z); // Reverse direction of travel on x axis.
            node->setVelocity(newVelocity);
        }
        if((node->T.translation.y >= 13) || (node->T.translation.y <= 7)) {
            glm::vec3 newVelocity = glm::vec3(velocity.x, -1.0 * velocity.y, velocity.z); // Reverse direction of travel on y axis.
            node->setVelocity(newVelocity);
        }
        if((node->T.translation.z >= 13) || (node->T.translation.z <= 7)) {
            glm::vec3 newVelocity = glm::vec3(velocity.x, velocity.y, -1.0 * velocity.z); // Reverse direction of travel on z axis.
            node->setVelocity(newVelocity);
        }
        
        
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
};

Node* VelocityScript::intersects() {
    bool didCollide = false;
    Node* collisionNode;
    Scene* scene = this->scene;
    const map<std::string, Node*> map = scene->getMapNodes();
    for(auto outer_iter = map.begin(); outer_iter != map.end(); outer_iter++) {
        didCollide = glm::dot(this->getNode()->T.translation - outer_iter->second->T.translation, this->getNode()->T.translation - outer_iter->second->T.translation) < (0.5 + 0.7)*(0.5 + 0.7);
        if(didCollide) {
            collisionNode = outer_iter->second;
            break;
        }
    }
    return collisionNode;
}

void VelocityScript::doAction(Node* intersectingNode) {
    Node* currentNode = this->getNode();
    glm::vec3 distance = currentNode->T.translation - intersectingNode->T.translation;
    
    glm::vec3 velocity1 = currentNode->getVelocity();
    float numerator1 = distance.x * velocity1.x + distance.y * velocity1.y+ distance.z * velocity1.z;
    float denominator1 = sqrt((distance.x + distance.y + distance.z) * (velocity1.x + velocity1.y + velocity1.z));
    float angle1xyz = acos(numerator1/denominator1);
    
    glm::vec3 velocity2 = currentNode->getVelocity();
    float numerator2 = distance.x * velocity2.x + distance.y * velocity2.y+ distance.z * velocity2.z;
    float denominator2 = sqrt((distance.x + distance.y + distance.z) * (velocity2.x + velocity2.y + velocity2.z));
    float angle2xyz = acos(numerator2/denominator2);
    
    glm::vec3 vCenter1 = velocity1 * cos(angle1xyz);
    glm::vec3 vCenter2 = velocity2 * cos(angle2xyz);
    
    float angle1xz =
    float angle1xy =
    
    vCenter1.x = vCenter1 * sin(
}
