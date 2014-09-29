//
//  Light.h
//  GameEngineNew
//
//  Created by Marcus Gabilheri on 9/16/14.
//  Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#ifndef __GameEngineNew__Light__
#define __GameEngineNew__Light__

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

// A point light source will need a color, direction and position
// 3 or 4 vec4
// Directional light is infinite far away and shines with the uLight color intensity
// Point color says that there;s a light with a certain position in space with a certain intensity
// Also there's a follow up function
// Divides by the square root distance of a lightSource + 1

class Light {
    
public:
    glm::vec4 uLightType, uLightDirection, uLightColor, uLightPosition;
};



#endif /* defined(__GameEngineNew__Light__) */
