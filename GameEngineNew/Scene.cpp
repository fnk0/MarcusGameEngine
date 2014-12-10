//
// Created by Marcus Gabilheri on 9/4/14.
// Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#include "Scene.h"
#include "CircleScript.h"
#include "VelocityScript.h"
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

    ifstream file(fileName);
    string jsonStr((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    string err;
    Json json = Json::parse(jsonStr, err);

    Json::object worldSettingsJson = json[WORLD_SETTINGS].object_items();
    Json::array meshesJson = json[MESHES].array_items();
    Json::array meshInstancesJson = json[MESH_INSTANCES].array_items();
    Json::array texturesJson = json[TEXTURES].array_items();
    Json::array lightsJson = json[LIGHTS].array_items();
    Json::array camerasJson = json[CAMERAS].array_items();
    Json::array nodesJson = json[NODES].array_items();

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

    // loading sound engine stuff
    this->setSoundEngine(createIrrKlangDevice());
    // Start sound engine
    //soundEngine = createIrrKlangDevice();
    if (!this->getSoundEngine()) ERROR("Error initializing sound engine!!");
    this->getSoundEngine()->setListenerPosition(vec3df(0, 0, 0), vec3df(0, 0, 1));
    this->getSoundEngine()->setSoundVolume(0.25f); // master volume control

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

    for(int i = 0; i < camerasJson.size(); i++) {
        SceneCamera* cam = new SceneCamera();
        Json::array eyeJson = camerasJson[i][EYE].array_items();
        glm::vec3 eyeVector;
        loadFloatsArray(&eyeVector[0], eyeJson);
        cam->setEye(eyeVector);

        Json::array centerJson = camerasJson[i][CENTER].array_items();
        glm::vec3 centerVector;
        loadFloatsArray(&centerVector[0], centerJson);
        cam->setCenter(centerVector);

        Json::array vupJson = camerasJson[i][VUP].array_items();
        glm::vec3 vupVector;
        loadFloatsArray(&vupVector[0], vupJson);
        cam->setVup(vupVector);

        cam->setFovy(camerasJson[i][FOVY].number_value());
        cam->setZfar(camerasJson[i][ZFAR].number_value());
        cam->setZnear(camerasJson[i][ZNEAR].number_value());

        cameras.push_back(cam);

        if(i == 0) {
            camera = cameras[0];
        }
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
        shaderProgram = createShaderProgram(vertexShader, fragmentShader);
        material.setShaderProgram(shaderProgram);
        instance->setMaterial(material);
        instance->setScene(this);
        meshInstances.insert(make_pair(meshInstancesJson[i][NAME].string_value(), instance));
    };

    for(int i = 0; i < nodesJson.size(); i++) {
        Node* node = new Node();
        
        std::string scriptName = nodesJson[i][SCRIPT].string_value();
        Script *script;
        if(scriptName.compare("VelocityScript") == 0) {
            script = new VelocityScript();
            node->script = script;
            node->script->setNode(node);
        }
        else if(scriptName.compare("CircleScript") == 0) {
            script = new CircleScript();
            node->script = script;
            node->script->setNode(node);
        }
        
        glm::vec3 scale;
        loadFloatsArray(&scale[0], nodesJson[i][SCALE].array_items());

        glm::vec3 translation;
        loadFloatsArray(&translation[0], nodesJson[i][TRANSLATION].array_items());

        glm::vec4 rotationVector;
        loadFloatsArray(&rotationVector[0], nodesJson[i][ROTATION].array_items());
        glm::vec3 vecRot(rotationVector.x, rotationVector.y, rotationVector.z);
        glm::quat rotation(rotationVector.w, vecRot);
        
        glm::vec3 velocityVector;
        loadFloatsArray(&velocityVector[0], nodesJson[i][VELOCITY].array_items());

        node->T.scale = scale;
        node->T.translation = translation;
        node->T.rotation = rotation;
        node->setVelocity(velocityVector);
        MeshInstance* inst = this->meshInstances[nodesJson[i][MESH_INSTANCE].string_value()];
        node->setMeshInstance(inst);

        Transform t = node->getT();
        glm::vec4 _temp = glm::vec4(0,0,0,1) * t.transform;
        string soundFileName = nodesJson[i][BACKGROUND_MUSIC].string_value();
        ISound* music = this->getSoundEngine()->play3D(soundFileName.c_str(), vec3df(_temp.x, _temp.y, _temp.z), true); // position and looping
        if (music) music->setMinDistance(5.0f); // distance of full volume

        node->setParent(nodesJson[i][PARENT].string_value());
        node->isBillboard = nodesJson[i][IS_BILLBOARD].bool_value();
        node->setScene(this);

        for(int j = 0; j < nodesJson[i][CHILDREN].array_items().size(); j++) {
            std::string childNode = nodesJson[i][CHILDREN].array_items()[j].string_value();
            node->getNodes().push_back(childNode);
        }

        node->setSound(music);
        nodes.insert(make_pair(nodesJson[i][NAME].string_value(), node));
    }
    
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

void Scene::updateNodes(const float dt) {
    for(auto outer_iter=nodes.begin(); outer_iter!=nodes.end(); ++outer_iter) {
        outer_iter->second->update(dt);
    }
}

void Scene::switchCamera(int camNum) {
    camera = cameras[camNum - 1];
}

