//
// Created by Marcus Gabilheri on 9/4/14.
// Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#ifndef __Scene_H_
#define __Scene_H_

#include "WorldSettings.h"
#include "MeshInstance.h"
#include "Light.h"
#include "Node.h"

// COMMONS
#define IN_FILE "file"
#define NAME "name"
#define TYPE "type"
#define VALUE "value"

// WORLD SETTINGS CONSTANTS
#define WORLD_SETTINGS "worldSettings"
#define WINDOW_TITLE "windowTitle"
#define WIDTH "width"
#define HEIGHT "height"
#define SPP "spp"
#define BACKGROUND_COLOR "backgroundColor"
#define BACKGROUND_MUSIC "backgroundMusic"

// Camera constants
#define CAMERA "camera"
#define EYE "eye"
#define CENTER "center"
#define VUP "vup"
#define FOVY "fovy"
#define ZNEAR "znear"
#define ZFAR "zfar"

// Mesh Constants
#define MESHES "meshes"

// MeshInstance constants
#define MESH_INSTANCES "meshInstances"
#define MESH "mesh"
#define SCALE "scale"
#define ROTATION "rotation"
#define TRANSLATION "translation"
#define VERTEX_SHADER "vertexShader"
#define FRAGMENT_SHADER "fragmentShader"
#define DIFFUSE_TEXTURE "diffuseTexture"
#define UNIFORM_LOCATIONS "uniformsLocation"
#define COLORS "colors"

#define LIGHTS "lights"
#define LIGHT_DIRECTION "uLightDirection"
#define LIGHT_COLOR "uLightColor"
#define LIGHT_POSITION "uLightPosition"
#define ATTENUATION "uAttenuation"
#define CONE_ANGLE "uConeAngles"

#define TYPE_AMBIENT_LIGHT "ambient"
#define TYPE_DIRECTIONAL_LIGHT "directional"
#define TYPE_POINT_LIGHT "point"
#define TYPE_SPOT_LIGHT "spot"
#define TYPE_HEAD_LIGHT "head"
#define TYPE_RIM_LIGHT "rim"

#define CAMERAS "cameras"

// Texture Constants
#define TEXTURES "textures"
#define OTHER_TEX "uOtherTex"


// Node constants
#define NODES "nodes"
#define PARENT "parent"
#define MESH_INSTANCE "meshInstance"
#define VELOCITY "velocity"
#define CHILDREN "children"
#define IS_BILLBOARD "is_billboard"
#define NODE "node"

class SceneCamera;
class WorldSettings;
class Mesh;
class MeshInstance;
class Node;

class Scene {

private:
    WorldSettings* worldSettings;
    SceneCamera* camera;
    map<std::string, Mesh*> meshes;
    map<std::string, RGBAImage*> textures;
    map<std::string, MeshInstance*> meshInstances;
    map<std::string, Node*> nodes;
    vector<SceneCamera*> cameras;
    ISoundEngine* soundEngine;

public:
    vector<Light> lights;
    GLFWwindow* gWindow = NULL;
    void loadScene(std::string &fileName);
    static void loadFloatsArray(float* floatArray, json11::Json::array jsonArray);
    void loadLights(GLint shaderProgram);
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

    map<string, MeshInstance *> const &getMeshInstances() const {
        return meshInstances;
    }

    void setMeshInstances(map<string, MeshInstance *> const &meshInstances) {
        Scene::meshInstances = meshInstances;
    }

    map<std::string,Node *> getNodes() {
        return nodes;
    }

    void setNodes(map<std::string, Node *> &nodes) {
        Scene::nodes = nodes;
    }

    vector<SceneCamera *> const &getCameras() const {
        return cameras;
    }

    void setCameras(vector<SceneCamera *> const &cameras) {
        Scene::cameras = cameras;
    }

    vector<Light> const &getLights() const {
        return lights;
    }

    void setLights(vector<Light> const &lights) {
        Scene::lights = lights;
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


    ISoundEngine *getSoundEngine() const {
        return soundEngine;
    }

    void setSoundEngine(ISoundEngine *soundEngine) {
        Scene::soundEngine = soundEngine;
    }

    void switchCamera(int camNum);

    void updateLights(void) {
        // Update global lights
        glBindBuffer(GL_UNIFORM_BUFFER, gLightBufferObject);
        //glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Light) * MAX_LIGHTS, gLights);
        glBufferData(GL_UNIFORM_BUFFER, sizeof(Light) * MAX_LIGHTS, gLights, GL_STREAM_DRAW);
        glBindBuffer(GL_UNIFORM_BUFFER, 0); // unbind buffer
    }
    
    void updateNodes(const float dt);
};


#endif// __Scene_H_
