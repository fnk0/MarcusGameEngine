//
// Created by Marcus Gabilheri on 9/4/14.
// Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#include "Scene.h"

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
#define NAME "name"
#define MESH_FILE "file"

// MeshInstance constants
#define MESH_INSTANCES "meshInstances"
#define MESH "mesh"
#define SCALE "scale"
#define VERTEX_SHADER "vertexShader"
#define FRAGMENT_SHADER "fragmentShader"
#define DIFFUSE_TEXTURE "diffuseTexture"

void Scene::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (action == GLFW_PRESS &&
            ((key >= 'A' && key <= 'Z') || (key >= '0' && key <= '9'))) {
        printf("\n%c\n", (char)key);
    }
}

void Scene::loadScene(std::string &fileName) {

    worldSettings = new WorldSettings();
    camera = new SceneCamera();

    ifstream file(fileName);
    string jsonStr((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    string err;
    Json json = Json::parse(jsonStr, err);

    Json::object worldSettingsJson = json[WORLD_SETTINGS].object_items();
    Json::object cameraJson = json[CAMERA].object_items();
    Json::array meshesJson = json[MESHES].array_items();
    Json::array meshInstancesJson = json[MESH_INSTANCES].array_items();

    worldSettings->setWindowTitle(worldSettingsJson[WINDOW_TITLE].string_value());
    worldSettings->setWidth(worldSettingsJson[WIDTH].int_value());
    worldSettings->setHeight(worldSettingsJson[HEIGHT].int_value());
    worldSettings->setSpp(worldSettingsJson[SPP].int_value());

    glm::vec3 backGroundColorVector;
    Json::array backgroundColor = worldSettingsJson[BACKGROUND_COLOR].array_items();
    loadFloatsArray(&backGroundColorVector[0], backgroundColor);
    worldSettings->setBackgroundColors(backGroundColorVector);
    worldSettings->setBackgroundMusic(worldSettingsJson[BACKGROUND_MUSIC].string_value());

    gWindow = createOpenGLWindow(worldSettings->getWidth(), worldSettings->getHeight(), worldSettings->getWindowTitle().c_str(), worldSettings->getSpp());
    glfwSetKeyCallback(gWindow, Scene::keyCallback);

    Json::array eyeJson = cameraJson[EYE].array_items();
    glm::vec3 eyeVector;
    loadFloatsArray(&eyeVector[0], eyeJson);
    camera->setEye(eyeVector);

    Json::array centerJson = cameraJson[CENTER].array_items();
    glm::vec3 centerVector;
    loadFloatsArray(&centerVector[0], centerJson);
    camera->setCenter(centerVector);

    Json::array vupJson = cameraJson[VUP].array_items();
    glm::vec3 vupVector;
    loadFloatsArray(&vupVector[0], vupJson);
    camera->setVup(vupVector);

    camera->setFovy(cameraJson[FOVY].number_value());
    camera->setZfar(cameraJson[ZFAR].number_value());
    camera->setZnear(cameraJson[ZNEAR].number_value());

    cout << "Number of meshes: " << meshesJson.size() << "\n";

    for(int i = 0; i < meshesJson.size(); i++) {
        Mesh* mesh = new Mesh();
        mesh->setMeshName(meshesJson[i][NAME].string_value());
        mesh->setMeshFile(meshesJson[i][MESH_FILE].string_value());

        mesh->readFromPly(mesh->getMeshFile(), false);
        mesh->sendToOpenGL();

        cout << "Mesh Name: " << mesh->getMeshName() << "\n";
        cout << "Mesh File: " << mesh->getMeshFile() << "\n";

        meshes.insert(make_pair(mesh->getMeshName(), mesh));
    }

    GLuint vertexShader = NULL_HANDLE;
    GLuint fragmentShader = NULL_HANDLE;
    GLuint shaderProgram = NULL_HANDLE;

    cout << "Number of mesh instances: " << meshInstancesJson.size() << "\n";

    for(int i = 0; i < meshInstancesJson.size(); i++) {
        MeshInstance *instance = new MeshInstance();

        cout << "Mesh Instance From the map!" << "\n";
        cout << "Mesh Name: " << meshes[meshInstancesJson[i][MESH].string_value()]->getMeshName() << "\n";
        cout << "Mesh File: " << meshes[meshInstancesJson[i][MESH].string_value()]->getMeshFile() << "\n";

        instance->setMesh(meshes[meshInstancesJson[i][MESH].string_value()]);
        vertexShader = loadShader(meshInstancesJson[i][VERTEX_SHADER].string_value(), GL_VERTEX_SHADER);
        fragmentShader = loadShader(meshInstancesJson[i][FRAGMENT_SHADER].string_value(), GL_FRAGMENT_SHADER);
        instance->diffuseTexture.loadPNG(meshInstancesJson[i][DIFFUSE_TEXTURE].string_value());
        instance->diffuseTexture.sendToOpenGL();
        shaderProgram = createShaderProgram(vertexShader, fragmentShader);
        instance->setShader(shaderProgram);

        cout << "Mesh Instance Getters!" << "\n";
        cout << "Mesh Name: " << instance->getMesh()->getMeshName() << "\n";
        cout << "Mesh File: " << instance->getMesh()->getMeshFile() << "\n";
        meshInstances.push_back(instance);

    };


    for(int i = 0; i < backGroundColorVector.length(); i++) {
        std::cout << "Color: " << backGroundColorVector[i] << "\n";
    }

};

void Scene::loadFloatsArray(float* floatArray, Json::array jsonArray) {

    for(int i = 0; i < jsonArray.size(); i++) {
        floatArray[i] = (float) jsonArray[i].number_value();
    }

};
