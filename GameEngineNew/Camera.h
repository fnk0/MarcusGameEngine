//
//  Camera.h
//  GameEngineNew
//
//  Created by Marcus Gabilheri on 8/30/14.
//  Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#ifndef __GameEngineNew__Camera__
#define __GameEngineNew__Camera__

#include <iostream>
#include "json11.hpp"
#include <glm/glm.hpp>

#endif /* defined(__GameEngineNew__Camera__) */

using namespace std;
using namespace json11;
using namespace glm;

class Camera {
    
private:
    Json json;
    string cameraName;
    // look from, look at, view up
    glm::vec3 eye, center, vup;
    
    float fovy; // vertical field of view
    float znear, zfar; // near and far clip planes
    
public:


    Camera() {};

    Json const &getJson() const {
        return json;
    }

    void setJson(Json const &json) {
        Camera::json = json;
    }

    basic_string<char, char_traits<char>, allocator<char>> const &getCameraName() const {
        return cameraName;
    }

    void setCameraName(basic_string<char, char_traits<char>, allocator<char>> const &cameraName) {
        Camera::cameraName = cameraName;
    }

    vec3 getEye() const {
        return eye;
    }

    void setEye(vec3 eye) {
        Camera::eye = eye;
    }

    vec3 getCenter() const {
        return center;
    }

    void setCenter(vec3 center) {
        Camera::center = center;
    }

    vec3 getVup() const {
        return vup;
    }

    void setVup(vec3 vup) {
        Camera::vup = vup;
    }

    float getFovy() const {
        return fovy;
    }

    void setFovy(float fovy) {
        Camera::fovy = fovy;
    }

    float getZnear() const {
        return znear;
    }

    void setZnear(float znear) {
        Camera::znear = znear;
    }

    float getZfar() const {
        return zfar;
    }

    void setZfar(float zfar) {
        Camera::zfar = zfar;
    }

    void init();
};