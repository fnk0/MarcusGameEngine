//
// Created by Marcus Gabilheri on 8/29/14.
// Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#include "WorldSettings.h"

Document doc;

WorldSettings::WorldSettings(Document doc) {
    
    setWindowTitle(doc["worldSettings"]["windowTitle"].GetString());
    
    glm::vec4 background = getBackgroundColors();
    this->setBackgroundColors(&background[0]);
    
    cout << "Window Title: " << getWindowTitle() << "\n";
    
    cout << "Color red: " << background[0] << "\n";
    cout << "Color blue: " << background[1] << "\n";
    cout << "Color green: " << background[2] << "\n";
    
};

void WorldSettings::setBackgroundColors(float *colors) {
    colors[0] = (float) doc["worldSettings"]["backgroundColor"]["r"].GetDouble();
    colors[1] = (float) doc["worldSettings"]["backgroundColor"]["g"].GetDouble();
    colors[2] = (float) doc["worldSettings"]["backgroundColor"]["b"].GetDouble();
}
