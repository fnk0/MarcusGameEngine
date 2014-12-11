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
       
};

#endif /* defined(__GameEngineNew__VelocityScript__) */
