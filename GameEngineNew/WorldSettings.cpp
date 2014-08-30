//
// Created by Marcus Gabilheri on 8/29/14.
// Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#include "WorldSettings.h"

WorldSettings::WorldSettings() {
    
};

void WorldSettings::init() {
    
    if(getJson() == nullptr) {
        cout << "Failed to initialize JSON object!\n";
        exit(0);
    }
    
    this->setWindowTitle(getJson()["worldSettings"]["windowTitle"].string_value());
    this->setBackgroundMusic(getJson()["worldSettings"]["backgroundMusic"].string_value());
    this->setWidth(getJson()["worldSettings"]["width"].number_value());
    this->setHeight(getJson()["worldSettings"]["height"].number_value());
    this->setSpp(getJson()["worldSettings"]["spp"].number_value());
    
    glm::vec4 background = getBackgroundColors();
    this->setBackgroundColors(&background[0]);
    
    cout << "Window Title: " << getWindowTitle() << "\n";
    
    cout << "width: " << getWidth() << "\n";
    cout << "height: " << getHeight() << "\n";
    cout << "spp: " << getSpp() << "\n";
    
    cout << "backgroundMusic" << getBackgroundMusic() << "\n";
    
    cout << "Color red: " << background[0] << "\n";
    cout << "Color blue: " << background[1] << "\n";
    cout << "Color green: " << background[2] << "\n";
}

void WorldSettings::setBackgroundColors(float *colors) {
    colors[0] = getJson()["worldSettings"]["backgroundColor"]["r"].number_value();
    colors[1] = getJson()["worldSettings"]["backgroundColor"]["g"].number_value();
    colors[2] = getJson()["worldSettings"]["backgroundColor"]["b"].number_value();
}
