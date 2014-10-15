//
//  Node.h
//  GameEngineNew
//
//  Created by Marcus Gabilheri on 10/14/14.
//  Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#ifndef __GameEngineNew__Node__
#define __GameEngineNew__Node__

#include <stdio.h>
#include "EngineUtil.h"
#include "MeshInstance.h"

class Node {

    Transform T;
    MeshInstance *meshInstance;
    vector<Node*> nodes;
    ISound *sound;

};

#endif /* defined(__GameEngineNew__Node__) */
