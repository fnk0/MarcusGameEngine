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
    
private:
    glm::vec3 lightColor, direction, position, attenuation;
    float intensity;
    int type;

    
public:

    float* serialize(void);

    glm::vec3 const &getLightColor() const {
        return lightColor;
    }

    void setLightColor(glm::vec3 const &lightColor) {
        Light::lightColor = lightColor;
    }


    float getIntensity() const {
        return intensity;
    }

    void setIntensity(float intensity) {
        Light::intensity = intensity;
    }

    glm::vec3 const &getDirection() const {
        return direction;
    }

    void setDirection(glm::vec3 const &direction) {
        Light::direction = direction;
    }

    glm::vec3 const &getPosition() const {
        return position;
    }

    void setPosition(glm::vec3 const &position) {
        Light::position = position;
    }
};



#endif /* defined(__GameEngineNew__Light__) */
