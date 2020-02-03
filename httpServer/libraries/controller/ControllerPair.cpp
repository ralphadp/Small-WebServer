//
// Created by root on 02-02-20.
//

#include "ControllerPair.h"

namespace Controller {

    ControllerPair::ControllerPair() {
        key = new char[24];
        controller = NULL;
    }

    ControllerPair::~ControllerPair() {
        delete[] key;
        delete controller;
    }

    bool ControllerPair::hasKey(const char *key) {
        return strcmp(this->key, key) == 0;
    }

    Model::ModelHandler* ControllerPair::getValue() {
        return controller;
    }

    void ControllerPair::setKey(const char *key) {
        strcpy(this->key, key);
    }

    void ControllerPair::setValue(Model::ModelHandler* value) {
        this->controller = value;
    }
}