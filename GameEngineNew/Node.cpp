//
//  Node.cpp
//  GameEngineNew
//
//  Created by Marcus Gabilheri on 10/14/14.
//  Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#include "Node.h"


void Node::refreshTransforms() {

    Transform childrenTransform;

    for(int i = 0; i < nodes.size(); i++) {
        childrenTransform.transform *= nodes[i]->T.transform;
    }
    if(parent != NULL) {
        T.transform *= parent->T.transform * childrenTransform.transform;
    } else {
        T.transform *= childrenTransform.transform;
    }
}
