//
// Created by Marcus Gabilheri on 9/4/14.
// Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//


#ifndef __GameEngineNew__WorldSettings_H_
#define __GameEngineNew__WorldSettings_H_

#include <iostream>
#include <glm/glm.hpp>

class WorldSettings {

private:
    std::string windowTitle;
    int width;
    int height;
    int spp;
    glm::vec3 backgroundColors;
    std::string backgroundMusic;

public:

    std::string getWindowTitle() const {
        return windowTitle;
    }

    void setWindowTitle(std::string windowTitle) {
        WorldSettings::windowTitle = windowTitle;
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

    glm::vec3 getBackgroundColors() const {
        return backgroundColors;
    }

    void setBackgroundColors(glm::vec3 backgroundColors) {
        WorldSettings::backgroundColors = backgroundColors;
    }

    std::string getBackgroundMusic() const {
        return backgroundMusic;
    }

    void setBackgroundMusic(std::string backgroundMusic) {
        WorldSettings::backgroundMusic = backgroundMusic;
    }
};


#endif //__WorldSettings_H_
