//
//  ThirdPersonScript.h
//  GameEngineNew
//
//  Created by Dawkins on 12/4/14.
//  Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#ifndef __GameEngineNew__ThirdPersonScript__
#define __GameEngineNew__ThirdPersonScript__

#include <stdio.h>
#include "Script.h"
#include "MoveCameraScript.h"

class ThirdPersonScript : public MoveCameraScript {

private:
public:
    void run() {
        MoveCameraScript::run();
        
    };
    
    virtual void refreshCamera();

    virtual void pressA() override;

    virtual void pressD() override;

    virtual void pressW() override;

    virtual void pressS() override;

    virtual void pressQ() override;

    virtual void pressE() override;
};

#endif /* defined(__GameEngineNew__ThirdPersonScript__) */
