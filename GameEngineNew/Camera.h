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
#include <glm/ext.hpp>

#endif /* defined(__GameEngineNew__Camera__) */

using namespace std;
using namespace json11;
using namespace glm;

class SceneCamera {
    
private:
    Json json;
    std::string cameraName;
    // look from, look at, view up
    glm::vec3 eye, center, vup;
    glm::mat4x4 worldViewProject;
    
    float fovy; // vertical field of view
    float znear, zfar; // near and far clip planes
    
public:


    SceneCamera() {};

    Json const &getJson() const {
        return json;
    }

    void setJson(Json const &json) {
        SceneCamera::json = json;
    }

    basic_string<char, char_traits<char>, allocator<char>> const &getCameraName() const {
        return cameraName;
    }

    void setCameraName(basic_string<char, char_traits<char>, allocator<char>> const &cameraName) {
        SceneCamera::cameraName = cameraName;
    }

    vec3 getEye() const {
        return eye;
    }

    void setEye(vec3 eye) {
        SceneCamera::eye = eye;
    }

    vec3 getCenter() const {
        return center;
    }

    void setCenter(vec3 center) {
        SceneCamera::center = center;
    }

    vec3 getVup() const {
        return vup;
    }

    void setVup(vec3 vup) {
        SceneCamera::vup = vup;
    }

    float getFovy() const {
        return fovy;
    }

    void setFovy(float fovy) {
        SceneCamera::fovy = fovy;
    }

    float getZnear() const {
        return znear;
    }

    void setZnear(float znear) {
        SceneCamera::znear = znear;
    }

    float getZfar() const {
        return zfar;
    }

    void setZfar(float zfar) {
        SceneCamera::zfar = zfar;
    }

    mat4x4 const &getWorldViewProject() const {
        return worldViewProject;
    }

    void setWorldViewProject(mat4x4 const &worldViewProject) {
        SceneCamera::worldViewProject = worldViewProject;
    }

    void refreshTransform(float screenWidth, float screenHeight);

    void init();
};