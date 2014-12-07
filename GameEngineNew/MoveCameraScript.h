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
#define PLAYER "player"

class MoveCameraScript : public Script {
    
    
private:
    Scene* scene;
    float t = 10.0f;
    float r = 0.5f;
public:
    void run();
    void pressA();
    void pressD();
    void pressW();
    void pressS();
    void pressQ();
    void pressE();
    void pressUp();
    void pressDown();
    void pressLeft();
    void pressRight();
    void refreshCamera();
};

#endif /* defined(__GameEngineNew__MoveCameraScript__) */