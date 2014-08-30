//
// Created by Marcus Gabilheri on 8/29/14.
// Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//


#ifndef __WorldSettings_H_
#define __WorldSettings_H_

#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <rapidjson/document.h>

using namespace std;
using namespace rapidjson;

class WorldSettings {

private:

    string windowTitle, backgroundMusic;
    int width, height, spp;
    glm::vec4 backgroundColors;

public:
    
    WorldSettings();
    
    WorldSettings(Document doc);
    
    basic_string<char, char_traits<char>, allocator<char>> const &getWindowTitle() const {
        return windowTitle;
    }

    void setWindowTitle(basic_string<char, char_traits<char>, allocator<char>> const &windowTitle) {
        WorldSettings::windowTitle = windowTitle;
    }

    basic_string<char, char_traits<char>, allocator<char>> const &getBackgroundMusic() const {
        return backgroundMusic;
    }

    void setBackgroundMusic(basic_string<char, char_traits<char>, allocator<char>> const &backgroundMusic) {
        WorldSettings::backgroundMusic = backgroundMusic;
    }

    int getWidth() const {
        return width;
    }

    void setWidth(int width) {
        WorldSettings::width = width;
    }

    int getHeight() const {
        return height;
    }

    void setHeight(int height) {
        WorldSettings::height = height;
    }

    int getSpp() const {
        return spp;
    }

    void setSpp(int spp) {
        WorldSettings::spp = spp;
    }
    
    void setBackgroundColors(float *color);
    
    glm::vec4 getBackgroundColors() {
        return backgroundColors;
    }


};


#endif //__WorldSettings_H_
