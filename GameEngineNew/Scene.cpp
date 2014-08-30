//
//  Scene.cpp
//  GameEngineNew
//
//  Created by Marcus Gabilheri on 8/29/14.
//  Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#include "Scene.h"

Document doc;

Scene::Scene(string fileName) {

    ifstream file(fileName.c_str());

    string jsonStr((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    doc.Parse(jsonStr.c_str());
    
    WorldSettings worldSettings(doc);
};

