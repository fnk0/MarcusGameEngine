//
// Created by Marcus Gabilheri on 9/4/14.
// Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#ifndef __GameEngineNew__MeshInstance__
#define __GameEngineNew__MeshInstance__

#include "Mesh.h"
#include "SceneCamera.h"
#include "Material.h"
#include "Scene.h"

class Scene;

class MeshInstance {

public:
    Mesh *mesh;

    glm::vec3 rotation, translation, scale;

    Transform T;
    Material material;
    Scene *scene;

public:
    MeshInstance(void);

    void setMesh(Mesh *mesh) { MeshInstance::mesh = mesh; }

    void draw(SceneCamera &camera);

    Mesh *getMesh() const {
        return mesh;
    }

    Scene *getScene() const {
        return scene;
    }

    void setScene(Scene *scene) {
        MeshInstance::scene = scene;
    }


    Material const &getMaterial() const {
        return material;
    }

    void setMaterial(Material const &material) {
        MeshInstance::material = material;
    }
};


#endif //__MeshInstance_H_
