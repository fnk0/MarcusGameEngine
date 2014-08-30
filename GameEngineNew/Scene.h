//
//  Scene.h
//  GameEngineNew
//
//  Created by Marcus Gabilheri on 8/29/14.
//  Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#ifndef __GameEngineNew__Scene__
#define __GameEngineNew__Scene__

#include <iostream>

#endif /* defined(__GameEngineNew__Scene__) */

#include <vector>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <fstream>
#include <streambuf>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/document.h>
#include "WorldSettings.h"

using namespace std;
using namespace rapidjson;

class Scene {

    private:
        WorldSettings worldSettings;
    
    public:
        Scene(string fileName);
    
        void setWorldSettings(WorldSettings worldSettings) {
            this->worldSettings = worldSettings;
        }
    
        WorldSettings getWorldSettings() {
            return worldSettings;
        }
};



