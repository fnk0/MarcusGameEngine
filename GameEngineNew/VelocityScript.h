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
        
        if((node->T.translation.x >= 3) || (node->T.translation.x <= -3)) {
            glm::vec3 newVelocity = glm::vec3(-1.0 * velocity.x, -1.0 * velocity.y, -1.0 * velocity.z); // Reverse direction of travel.
            node->setVelocity(newVelocity);
        }
        
        if(glfwGetKey(scene->gWindow, 'J')) { // Speed up
            if(velocity.x >= 0) node->accelerate(glm::vec3(0.1, 0, 0), TIMESTEP);
            else node->accelerate(glm::vec3(-0.1, 0, 0), TIMESTEP);
        }
        if(glfwGetKey(scene->gWindow, 'K')) { // Slow down
            if(velocity.x >= 0) node->accelerate(glm::vec3(-0.1, 0, 0), TIMESTEP);
            else node->accelerate(glm::vec3(0.1, 0, 0), TIMESTEP);
        }
        
        node->update(TIMESTEP);
    };
};

#endif /* defined(__GameEngineNew__VelocityScript__) */
