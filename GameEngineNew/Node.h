//
//  Node.h
//  GameEngineNew
//
//  Created by Marcus Gabilheri on 10/14/14.
//  Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#ifndef __GameEngineNew__Node__
#define __GameEngineNew__Node__

#include <stdio.h>
#include "EngineUtil.h"
#include "MeshInstance.h"
#include "Script.h"

class MeshInstance;
class Transform;
class Scene;
class Script;

class Node {

// Has a TRS -> Translation Rotation Scale
// Childs also has a TRS, etc..1
public:
    Transform T;
    std::string name;
    std::string parent;
    MeshInstance *meshInstance;
    vector<std::string> nodes;
    ISound *sound;
    Scene* scene;
    bool isBillboard = true;
    std::vector<Script*> scripts;
    glm::vec3 velocity;
    float mass;

    Node() {
    };
    
    void setScript(Script* script) {
        this->scripts.push_back(script);
    };

    Scene *getScene() {
        return scene;
    }

    void setScene(Scene *scene) {
        Node::scene = scene;
    }

    void refreshTransforms();

    Transform getT() {
        return T;
    }

    void setT(Transform const &T) {
        Node::T = T;
    }
    
    glm::vec3 getVelocity() {
        return velocity;
    }
    
    void setVelocity(const glm::vec3 &v) {
        Node::velocity = v;
    }
    
    void accelerate(const glm::vec3 &acceleration, const float dt) {
        Node::velocity = velocity + acceleration * dt;
    }

    std::string getParent() {
        return parent;
    }

    void setParent(std::string parent) {
        Node::parent = parent;
    }

    MeshInstance *getMeshInstance() const {
        return meshInstance;
    }

    void setMeshInstance(MeshInstance *meshInstance) {
        Node::meshInstance = meshInstance;
    }

    vector<std::string> getNodes() {
        return nodes;
    }

    void setNodes(vector<std::string> &nodes) {
        Node::nodes = nodes;
    }

    ISound *getSound() const {
        return sound;
    }

    void setSound(ISound *sound) {
        Node::sound = sound;
    }

    std::string getName() {
        return name;
    }

    void setName(std::string name) {
        Node::name = name;
    }

    vector<Script *> const &getScripts() const {
        return scripts;
    }

    void setScripts(vector<Script *> const &scripts) {
        Node::scripts = scripts;
    }

    void translateLocal(glm::vec3 &translation);
    
    void update(const float dt) {
        Node::T.translation = T.translation + velocity * dt;
        Node::T.refreshTransform();
    }
    
    float getMass() const {
        return mass;
    }
    
    void setMass(const float m) {
        Node::mass = m;
    }
    
    // Look at the camera and see which direction is looking to (Easy way)
    // Hard eay is related to the World location of the Billboard. 
    //void draw(glm::mat4x4 &mat, glm::mat4x4 &matInverse, SceneCamera &cam);
    void draw(SceneCamera &cam);
};

#endif /* defined(__GameEngineNew__Node__) */
