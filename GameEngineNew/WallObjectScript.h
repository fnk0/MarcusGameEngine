//
// Created by Marcus Gabilheri on 12/8/14.
// Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//


#include "GameObjectScript.h"

#ifndef __WallObjectScript_H_
#define __WallObjectScript_H_

class WallObjectScript : public GameObjectScript {

public:


private:
    virtual void run() override;

    virtual void doAction() override;

    void refreshCamera();
};


#endif //__WallObjectScript_H_
