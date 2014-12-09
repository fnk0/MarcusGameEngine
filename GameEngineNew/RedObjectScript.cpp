//
// Created by Marcus Gabilheri on 12/8/14.
// Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#include "RedObjectScript.h"

void RedObjectScript::run() {
    GameObjectScript::run();
}

void RedObjectScript::doAction() {
    this->scene->deleteNode(this->getNode()->getName());
}
