//
//  Script.h
//  GameEngineNew
//
//  Created by Dawkins on 10/28/14.
//  Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#ifndef __GameEngineNew__Script__
#define __GameEngineNew__Script__

#include <stdio.h>
#include <iostream>
#include <map>
#include "Node.h"

class Node;

class Script {
    
private:
    std::map<std::string, void*> values;
    Node* node;
public:
    virtual void run(){};
    void set(std::string key, void* value);
    void* get(std::string key);
    Node* getNode() {
        return this->node;
    };
    void setNode(Node* node) {
        this->node = node;
    };
};

#endif /* defined(__GameEngineNew__Script__) */
