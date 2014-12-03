//
//  HastyVect3.cpp
//  GameEngineNew
//
//  Created by Dawkins on 11/11/14.
//  Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#include "HastyVect3.h"

void HastyVect3::move(float time, glm::vec3 velocity) {
    this->x = this->x + (time * velocity.x);
    this->y = this->y + (time * velocity.y);
    this->z = this->z + (time * velocity.z);
};

glm::vec3 HastyVect3::get_vec3() {
    glm::vec3 v;
    v.x = this->x;
    v.y = this->y;
    v.z = this->z;
    return v;
};