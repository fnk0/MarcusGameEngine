//
// Created by Marcus Gabilheri on 9/4/14.
// Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//


#include "WorldSettings.h"

#ifndef __Scene_H_
#define __Scene_H_
#include "WorldSettings.h"
#include "MeshInstance.h"

class SceneCamera;
class WorldSettings;
class Mesh;
class MeshInstance;

class Scene {

private:
    WorldSettings* worldSettings;
    SceneCamera* camera;
    map<std::string, Mesh*> meshes;
    map<std::string, RGBAImage*> textures;
    vector<MeshInstance*> meshInstances;

public:
    GLFWwindow* gWindow = NULL;
    void loadScene(std::string &fileName);
    void loadFloatsArray(float* floatArray, json11::Json::array jsonArray);
    void static keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    WorldSettings *getWorldSettings() const {
        return worldSettings;
    }

    void setWorldSettings(WorldSettings *worldSettings) {
        Scene::worldSettings = worldSettings;
    }

    SceneCamera *getCamera() const {
        return camera;
    }

    void setCamera(SceneCamera *camera) {
        Scene::camera = camera;
    }

    map<string, Mesh *> const &getMeshes() const {
        return meshes;
    }

    void setMeshes(map<string, Mesh *> const &meshes) {
        Scene::meshes = meshes;
    }

    vector<MeshInstance *>  const &getMeshInstances() const {
        return meshInstances;
    }

    void setMeshInstances(vector<MeshInstance *> const &meshInstances) {
        Scene::meshInstances = meshInstances;
    }


    map<string, RGBAImage *> const &getTextures() const {
        return textures;
    }

    void setTextures(map<string, RGBAImage *> const &textures) {
        Scene::textures = textures;
    }


    GLFWwindow *getGWindow() const {
        return gWindow;
    }

    void setGWindow(GLFWwindow *gWindow) {
        Scene::gWindow = gWindow;
    }
};


#endif// __Scene_H_
