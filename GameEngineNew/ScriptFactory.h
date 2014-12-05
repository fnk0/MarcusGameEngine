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

class ScriptFactory {
    
private:
    Node* node;
public:
    ScriptFactory(Node* node) {
        this->node = node;
    };
    
    Script* getScript(std::string scriptName) {
        Script* script = new Script();
        
        if(scriptName.compare("CircleScript") == 0) {
            CircleScript* circleScript = new CircleScript();
            circleScript->setNode(this->node);
            script = circleScript;
        }
        else if(scriptName.compare("ThirdPersonScript") == 0) {
            ThirdPersonScript* thirdPersonScript = new ThirdPersonScript();
            thirdPersonScript->setNode(this->node);
            script = thirdPersonScript;
        }
        
        return script;
    };
    
};

#endif /* defined(__GameEngineNew__ScriptFactory__) */
