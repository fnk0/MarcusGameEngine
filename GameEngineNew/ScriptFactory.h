//
//  ScriptFactory.h
//  GameEngineNew
//
//  Created by Dawkins on 12/4/14.
//  Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#ifndef __GameEngineNew__ScriptFactory__
#define __GameEngineNew__ScriptFactory__

#include <stdio.h>

#include <iostream>
#include "Script.h"
#include "CircleScript.h"
#include "ThirdPersonScript.h"
#include "Node.h"
#include "GameObjectScript.h"
#include "RedObjectScript.h"
#include "VelocityScript.h"

class ScriptFactory {
    
private:
    Node* node;
public:
    ScriptFactory(Node* node) {
        this->node = node;
    };
    
    Script* getScript(std::string scriptName) {
        Script* script = new Script();
        
        if(scriptName == "CircleScript") {
            CircleScript* circleScript = new CircleScript();
            circleScript->setNode(this->node);
            script = circleScript;
        }
        else if(scriptName == "GameObjectScript") {
            GameObjectScript* gameObjectScript = new GameObjectScript();
            gameObjectScript->setNode(this->node);
            script = gameObjectScript;
        }
        else if(scriptName == "ThirdPersonScript") {
            ThirdPersonScript* thirdPersonScript = new ThirdPersonScript();
            thirdPersonScript->setNode(this->node);
            script = thirdPersonScript;
        }
        else if(scriptName == "RedObjectScript") {
            RedObjectScript*  redObjectScript = new RedObjectScript();
            redObjectScript->setNode(this->node);
            script = redObjectScript;
        }
        else if(scriptName == "VelocityScript") {
            VelocityScript* velocityScript = new VelocityScript();
            velocityScript->setNode(this->node);
            script = velocityScript;
        }

        return script;
    };
    
};

#endif /* defined(__GameEngineNew__ScriptFactory__) */
