//
// Created by Marcus Gabilheri on 12/8/14.
// Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//




#ifndef __GameObjectScript_H_
#define __GameObjectScript_H_

#include "Script.h"
#include "Scene.h"

class GameObjectScript : public Script{

public:
    Scene* scene;
    virtual void run() override;
    bool intersects();
    virtual void doAction();
};


#endif //__GameObjectScript_H_
