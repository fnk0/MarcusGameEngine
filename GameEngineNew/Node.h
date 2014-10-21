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

class Node {

// Has a TRS -> Translation Rotation Scale
// Childs also has a TRS, etc..1
public:
    Transform T;
    Node *parent;
    MeshInstance *meshInstance;
    vector<Node*> nodes;
    ISound *sound;

    void refreshTransforms();

    Transform const &getT() const {
        return T;
    }

    void setT(Transform const &T) {
        Node::T = T;
    }

    Node *getParent() const {
        return parent;
    }

    void setParent(Node *parent) {
        Node::parent = parent;
    }

    MeshInstance *getMeshInstance() const {
        return meshInstance;
    }

    void setMeshInstance(MeshInstance *meshInstance) {
        Node::meshInstance = meshInstance;
    }

    vector<Node *> const &getNodes() const {
        return nodes;
    }

    void setNodes(vector<Node *> const &nodes) {
        Node::nodes = nodes;
    }

    ISound *getSound() const {
        return sound;
    }

    void setSound(ISound *sound) {
        Node::sound = sound;
    }
    
    // Look at the camera and see which direction is looking to (Easy way)
    // Hard eay is related to the World location of the Billboard. 
    void draw(glm::mat4x4 &mat, glm::mat4x4 &matInverse, SceneCamera &cam);
};

#endif /* defined(__GameEngineNew__Node__) */
