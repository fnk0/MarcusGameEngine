//
//  ThirdPersonDetachedScript.h
//  GameEngineNew
//
//  Created by POWERS VERONICA E on 12/10/14.
//  Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#ifndef __GameEngineNew__ThirdPersonDetachedScript__
#define __GameEngineNew__ThirdPersonDetachedScript__

#include <stdio.h>
#include "Script.h"
#include "MoveCameraScript.h"
#include "ThirdPersonScript.h"

class ThirdPersonDetachedScript : public ThirdPersonScript {
public:
    virtual void run() override;
    virtual void refreshCamera();
};

#endif /* defined(__GameEngineNew__ThirdPersonDetachedScript__) */
