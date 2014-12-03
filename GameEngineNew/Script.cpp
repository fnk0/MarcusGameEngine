//
//  Script.cpp
//  GameEngineNew
//
//  Created by Dawkins on 10/28/14.
//  Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#include "Script.h"

void Script::set(std::string key, void *value) {
    this->values[key] = value;
};

void* Script::get(std::string key) {
    return this->values[key];
};