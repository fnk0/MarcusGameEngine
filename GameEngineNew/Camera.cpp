//
//  Camera.cpp
//  GameEngineNew
//
//  Created by Marcus Gabilheri on 8/30/14.
//  Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#include "Camera.h"


vec3 setVecXYZ(Json::object object, string objName) {
    vec3 vec;
    float* xyz = &vec[0];
    xyz[0] = object["x"].number_value();
    xyz[1] = object["y"].number_value();
    xyz[2] = object["z"].number_value();
    return vec;
}

void SceneCamera::init() {

    if(getJson() == nullptr) {
        cout << "Failed to initialize JSON object!! \n";
        exit(0);
    }
    
    Json::object obj = getJson()["camera"].object_items();
    
    this->setCameraName(obj["name"].string_value());
    
    //TODO move this names somehwere.... kinda bad they are hardcoded now...
    setEye(setVecXYZ(obj, "eye"));
    setCenter(setVecXYZ(obj, "center"));
    setVup(setVecXYZ(obj, "vup"));
    
    setFovy(obj["fovy"].number_value());
    setZnear(obj["znear"].number_value());
    setZfar(obj["zfar"].number_value());
}

void SceneCamera::refreshTransform(float screenWidth, float screenHeight) {
    glm::mat4x4 worldView = glm::lookAt(eye, center, vup);
    glm::mat4x4 project = glm::perspective((float)fovy,
            (float)(screenWidth / screenHeight), (float)znear, (float)zfar);
    worldViewProject = project * worldView;
}