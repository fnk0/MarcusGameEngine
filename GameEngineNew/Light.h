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
#import <OpenGL/OpenGL.h>

// A point light source will need a color, direction and position
// 3 or 4 vec4
// Directional light is infinite far away and shines with the uLight color intensity
// Point color says that there;s a light with a certain position in space with a certain intensity
// Also there's a follow up function
// Divides by the square root distance of a lightSource + 1

class Light {
public:
    // type is in attenuation.w
    glm::vec4 position, direction, color, attenuation, coneAngles;

    Light(const Light &L) {
        position = L.position;
        direction = L.direction;
        color = L.color;
        attenuation = L.attenuation;
        coneAngles = L.coneAngles;
    }

    Light() {
        position = glm::vec4(0, 0, 0, 1);
        direction = glm::vec4(0, 1, 0, 0);
        color = glm::vec4(1, 0, 0, 1);
        attenuation = glm::vec4(0, 0, 0, 0);
        coneAngles = glm::vec4(0.5, 0.55, 0, 0);
    }
};

#define NO_LIGHT 0
#define AMBIENT_LIGHT 1
#define DIRECTIONAL_LIGHT 2
#define POINT_LIGHT 3
#define SPOT_LIGHT 4
#define HEAD_LIGHT 5
#define RIM_LIGHT 6

#define MAX_LIGHTS 10
#define LIGHT_BUFFER_ID 1
extern GLuint gLightBufferObject;
extern int gNumLights;
extern Light gLights[MAX_LIGHTS];

#endif /* defined(__GameEngineNew__Light__) */
