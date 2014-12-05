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

class MoveCameraScript : public Script {
    
    
private:
    Scene* scene;
    float t = 0.1f;
    float r = 0.05f;
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
};

#endif /* defined(__GameEngineNew__MoveCameraScript__) */
