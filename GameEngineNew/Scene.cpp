//
//  Scene.cpp
//  GameEngineNew
//
//  Created by Marcus Gabilheri on 8/29/14.
//  Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#include "Scene.h"

Scene::Scene(string fileName) {

    ifstream file(fileName);

    string jsonStr((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    
    string err;
    auto json = Json::parse(jsonStr, err);
    
    // Initialize World Settings object
    WorldSettings worldSettings;
    worldSettings.setJson(json);
    worldSettings.init();
    setWorldSettings(worldSettings);
    
    // Initialize the Camera Object
    SceneCamera camera;
    camera.setJson(json);
    camera.init();
    setCamera(camera);
    
    testJSON();
    
};

void Scene::testJSON() {
    
    cout << "Camera Name: " << camera.getCameraName() << "\n";
    
}

