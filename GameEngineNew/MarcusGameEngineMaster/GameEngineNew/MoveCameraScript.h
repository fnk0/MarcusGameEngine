//
//  MoveCameraScript.h
//  GameEngineNew
//
//  Created by Dawkins on 12/4/14.
//  Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#ifndef __GameEngineNew__MoveCameraScript__
#define __GameEngineNew__MoveCameraScript__

#include <stdio.h>
#include "Script.h"
#include "Node.h"
#define PLAYER "player"

class MoveCameraScript : public Script {

private:
   
public:
    Scene* scene;
    float t = 10.0f;
    float r = 0.5f;
    void run();
    virtual void pressA();
    virtual void pressD();
    virtual void pressW();
    virtual void pressS();
    virtual void pressQ();
    virtual void pressE();
    virtual void pressUp();
    virtual void pressDown();
    virtual void pressLeft();
    virtual void pressRight();

};

#endif /* defined(__GameEngineNew__MoveCameraScript__) */
