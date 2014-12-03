//
//  HastyVect3.h
//  GameEngineNew
//
//  Created by Dawkins on 11/11/14.
//  Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#ifndef __GameEngineNew__HastyVect3__
#define __GameEngineNew__HastyVect3__

#include <stdio.h>
#include <glm/glm.hpp>

class HastyVect3 : public glm::vec3 {
private:
public:
    static HastyVect3 forge(glm::vec3 v) {
        HastyVect3 vprime;
        vprime.x = v.x;
        vprime.y = v.y;
        vprime.z = v.z;
        return vprime;
    };
    void move(float time, glm::vec3 velocity);
    glm::vec3 get_vec3();
};

#endif /* defined(__GameEngineNew__HastyVect3__) */
