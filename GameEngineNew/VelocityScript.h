//
//  VelocityScript.h
//  GameEngineNew
//
//  Created by POWERS VERONICA E on 12/7/14.
//  Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#ifndef __GameEngineNew__VelocityScript__
#define __GameEngineNew__VelocityScript__

#include <stdio.h>
#include "Script.h"
#include "EngineUtil.h"
#include "Scene.h"
#include <math.h>

#define PI 3.14159265

class VelocityScript : public Script {
    
private:
    Transform t;
    double theta = 0;
public:
    
    void setNode(Node* node) {
        // Setting our node
        Script::setNode(node);
        
        /*
         
         //
         // This temporarily saves our transform so we can use it again later.
         //
         
         glm::vec3 scale;
         glm::quat rotation;
         glm::vec3 translation;
         glm::mat4x4 transform;
         glm::mat4x4 invTransform;
         */
        Transform temp = this->getNode()->T;
        Transform t;
        t.scale = temp.scale;
        t.rotation = temp.rotation;
        t.translation = temp.translation;
        t.transform = temp.transform;
        t.invTransform = temp.transform;
        
    };
    
    void run() {
        const float TIMESTEP = float(1.0/60.0);
        Node *node = this->getNode();
        Scene *scene = node->getScene();
        glm::vec3 velocity = node->getVelocity();
        float increment = 0.1;
        float e = increment * TIMESTEP;
        
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
    };
};

#endif /* defined(__GameEngineNew__VelocityScript__) */
