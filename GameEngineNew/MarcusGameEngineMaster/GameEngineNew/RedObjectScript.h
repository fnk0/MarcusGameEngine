//
// Created by Marcus Gabilheri on 12/8/14.
// Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//


#ifndef __RedObjectScript_H_
#define __RedObjectScript_H_

#include "GameObjectScript.h"

class RedObjectScript : public GameObjectScript{

public:


private:
    virtual void run() override;

    virtual void doAction() override;
};


#endif //__RedObjectScript_H_
