//
// Created by Marcus Gabilheri on 9/4/14.
// Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#include "Scene.h"


GLuint gLightBufferObject = NULL_HANDLE;
int gNumLights = 0;
Light gLights[MAX_LIGHTS];

void initLightBuffer() {
    
    if (gLightBufferObject != NULL_HANDLE) return;
    glGenBuffers(LIGHT_BUFFER_ID, &gLightBufferObject); // create a new buffer id
    
    glBindBuffer(GL_UNIFORM_BUFFER, gLightBufferObject); // bind the new buffer
    glBufferData(GL_UNIFORM_BUFFER, sizeof(Light) * MAX_LIGHTS, gLights, GL_STREAM_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0); // unbind buffer
}


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
    Json::array texturesJson = json[TEXTURES].array_items();
    Json::array lightsJson = json[LIGHTS].array_items();

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
        mesh->setMeshFile(meshesJson[i][IN_FILE].string_value());

        mesh->readFromPly(mesh->getMeshFile(), false);
        mesh->sendToOpenGL();

        cout << "Mesh Name: " << mesh->getMeshName() << "\n";
        cout << "Mesh File: " << mesh->getMeshFile() << "\n";

        meshes.insert(make_pair(mesh->getMeshName(), mesh));
    }
    
    for(int i = 0; i < lightsJson.size(); i++) {
        Light light;
        Scene::loadFloatsArray(&light.color[0], lightsJson[i][LIGHT_COLOR].array_items());
        Scene::loadFloatsArray(&light.direction[0], lightsJson[i][LIGHT_DIRECTION].array_items());
        Scene::loadFloatsArray(&light.position[0], lightsJson[i][LIGHT_POSITION].array_items());
        Scene::loadFloatsArray(&light.attenuation[0], lightsJson[i][ATTENUATION].array_items());
        Scene::loadFloatsArray(&light.coneAngles[0], lightsJson[i][CONE_ANGLE].array_items());
        light.direction = glm::normalize(light.direction);
        
        light.coneAngles[0] = cos(light.coneAngles[0]);
        light.coneAngles[1] = cos(light.coneAngles[1]);
        
    
        if(lightsJson[i][TYPE] == TYPE_DIRECTIONAL_LIGHT) {
            // Found a Directional Light
            cout << "Found a Directional Light" << endl;
            light.attenuation.w = DIRECTIONAL_LIGHT;
        } else if(lightsJson[i][TYPE] == TYPE_POINT_LIGHT) {
            // Found a Point Light
            cout << "Found a Point Light" << endl;
            light.attenuation.w = POINT_LIGHT;
        } else if(lightsJson[i][TYPE] == TYPE_SPOT_LIGHT) {
            // Found a Spot Light
            cout << "Found a Spot Light" << endl;
            light.attenuation.w = SPOT_LIGHT;
        }
        gLights[i] = light;
        gNumLights++;
        lights.push_back(light);
        
        if(i >= MAX_LIGHTS) {
            ERROR("Too mahy lights!", false);
            break;
        }
    }
    
    initLightBuffer();
    
    for(int i = 0; i < texturesJson.size(); i++) {
        RGBAImage* texture = new RGBAImage();
        cout << "Texture Name: " << texturesJson[i][NAME].string_value() << "\n";
        cout << "Texture File: " << texturesJson[i][IN_FILE].string_value() << "\n";
        texture->loadPNG(texturesJson[i][IN_FILE].string_value());
        texture->sendToOpenGL();
        textures.insert(make_pair(texturesJson[i][NAME].string_value(), texture));
    }

    GLuint vertexShader = NULL_HANDLE;
    GLuint fragmentShader = NULL_HANDLE;
    GLuint shaderProgram = NULL_HANDLE;

    cout << "Number of mesh instances: " << meshInstancesJson.size() << "\n";

    for(int i = 0; i < meshInstancesJson.size(); i++) {
        MeshInstance *instance = new MeshInstance();
        Material material;

        Json::array uniforms = meshInstancesJson[i][UNIFORM_LOCATIONS].array_items();
        Json::array colors = meshInstancesJson[i][COLORS].array_items();
        Json::array meshTextures = meshInstancesJson[i][TEXTURES].array_items();
        vector<std::string> uniformVector;

        for(int i = 0; i < uniforms.size(); i++) {
            uniformVector.push_back(uniforms[i].string_value());
        }

        glm::vec3 scale;
        loadFloatsArray(&scale[0], meshInstancesJson[i][SCALE].array_items());

        glm::vec3 translation;
        loadFloatsArray(&translation[0], meshInstancesJson[i][TRANSLATION].array_items());
        
        glm::vec3 rotationVector;
        loadFloatsArray(&rotationVector[0], meshInstancesJson[i][ROTATION].array_items());
        
        glm::quat rotation(rotationVector);

        for(int k = 0; k < colors.size(); k++) {
            NameIdVal<glm::vec4> color;
            color.name = colors[k][TYPE].string_value();
            glm::vec4 colorValues;
            Scene::loadFloatsArray(&colorValues[0], colors[k][VALUE].array_items());
            color.val = colorValues;
            material.addColor(color);
        }

        for(int j = 0; j < meshTextures.size(); j++) {
            NameIdVal<RGBAImage*> tex;
            tex.name = meshTextures[j][TYPE].string_value();
            std::string s = meshTextures[j][NAME].string_value();
            tex.val = textures[s];
            material.addTexture(tex);
        }
        
        std::string meshName = meshInstancesJson[i][MESH].string_value();
        instance->setMesh(meshes[meshName]);
        vertexShader = loadShader(meshInstancesJson[i][VERTEX_SHADER].string_value(), GL_VERTEX_SHADER);
        fragmentShader = loadShader(meshInstancesJson[i][FRAGMENT_SHADER].string_value(), GL_FRAGMENT_SHADER);
        instance->setScale(scale);
        instance->setTranslation(translation);
        instance->setRotation(rotation);
        shaderProgram = createShaderProgram(vertexShader, fragmentShader);
        material.setShaderProgram(shaderProgram);
        instance->setMaterial(material);
        instance->setScene(this);
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

void Scene::loadLights(GLint shaderProgram) {

    GLint loc = glGetUniformLocation(shaderProgram, "lightTest");

    if(loc != -1) {
        glUniform4fv(loc, MAX_LIGHTS * sizeof(lights) / 4, (float*) &lights[0]);
    }

}

