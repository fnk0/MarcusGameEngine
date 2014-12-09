//
//  CircleScript.h
//  GameEngineNew
//
//  Created by Dawkins on 11/18/14.
//  Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#ifndef __GameEngineNew__CircleScript__
#define __GameEngineNew__CircleScript__

#include <stdio.h>
#include "Script.h"
#include <math.h>

#define PI 3.14159265

class CircleScript : public Script {
    
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
        // TODO
        this->theta += PI/128;
        
        glm::vec3 rotation;
        rotation.x = 3 * sin(theta);
        rotation.y = this->t.translation.y;
        rotation.z = 3 * cos(theta);
        glm::vec3 translation = this->t.translation + rotation;
        this->getNode()->T.translation = translation;
        
        double lambda = PI/128;
        glm::vec3 unit(0, 1, 0);
        glm::quat r;
        glm::quat original = this->getNode()->T.rotation;
        
        r.w = cos(lambda/2);
        r.x = original.x * sin(lambda/2);
        r.y = original.y * sin(lambda/2);
        r.z = original.z * sin(lambda/2);
        
        this->getNode()->T.rotation = r;
    };
};

#endif /* defined(__GameEngineNew__CircleScript__) */
