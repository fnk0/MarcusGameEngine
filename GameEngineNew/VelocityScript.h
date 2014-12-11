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
#include "GameObjectScript.h"
#include <math.h>

#define PI 3.14159265

class VelocityScript : public GameObjectScript {
    
private:
    Transform t;
    double theta = 0;
    
    virtual void run() override;
    Node* intersects();
public:
    void doAction(Node*);
    
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
};

#endif /* defined(__GameEngineNew__VelocityScript__) */
