    //
// Created by Marcus Gabilheri on 9/4/14.
// Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//


#ifndef __GameEngineNew__SceneCamera_H_
#define __GameEngineNew__SceneCamera_H_

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class SceneCamera {

private:
    glm::vec3 eye;
    glm::vec3 center;
    glm::vec3 vup;

    float fovy, znear, zfar;

    glm::mat4x4 worldViewProject;

public:
    void refreshTransform(float screenWidth, float screenHeight);

    glm::vec3 getEye() const {
        return eye;
    }

    void setEye(glm::vec3 eye) {
        SceneCamera::eye = eye;
    }

    glm::vec3 getCenter() const {
        return center;
    }

    void setCenter(glm::vec3 center) {
        SceneCamera::center = center;
    }

    glm::vec3 getVup() const {
        return vup;
    }

    void setVup(glm::vec3 vup) {
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

    glm::mat4x4 getWorldViewProject() const {
        return worldViewProject;
    }

    void setWorldViewProject(glm::mat4x4 worldViewProject) {
        SceneCamera::worldViewProject = worldViewProject;
    }

    void translateGlobal(const glm::vec3 &t) {
        eye += t;
        center += t;
    }

    void translateLocal(const glm::vec3 &t) {
        glm::vec3 zz = glm::normalize(eye - center);
        glm::vec3 xx = glm::normalize(glm::cross(vup, zz));
        glm::vec3 yy = glm::cross(zz, xx);
        glm::vec3 tt = t.x*xx + t.y*yy + t.z*zz;
        eye += tt; center += tt;
    }
    void rotateGlobal(glm::vec3 axis, float angle) {
        glm::mat4x4 R = glm::axisAngleMatrix(axis, angle);
        glm::vec4 zz = glm::vec4(eye - center, 0);
        glm::vec4 Rzz = R*zz;
        center = eye - glm::vec3(Rzz);

        glm::vec4 up = glm::vec4(vup, 0);
        glm::vec4 Rup = R*up;
        vup = glm::vec3(Rup);
    }
    void rotateLocal(glm::vec3 axis, float angle) {
        glm::vec3 zz = glm::normalize(eye - center);
        glm::vec3 xx = glm::normalize(glm::cross(vup, zz));
        glm::vec3 yy = glm::cross(zz, xx);
        glm::vec3 aa = xx * axis.x + yy * axis.y + zz * axis.z;
        rotateGlobal(aa, angle);
    }
};


#endif //__SceneCamera_H_
