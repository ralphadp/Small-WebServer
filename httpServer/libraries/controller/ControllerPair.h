//
// Created by root on 02-02-20.
//

#ifndef SERVER_CONTROLLERPAIR_H
#define SERVER_CONTROLLERPAIR_H

#include <string.h>

#include "../model/ModelHandler.h"

namespace Controller {

    class ControllerPair {
        char *key;
        Model::ModelHandler* controller;

    public:
        ControllerPair();

        virtual ~ControllerPair();

        bool hasKey(const char* key);

        Model::ModelHandler* getValue();

        void setKey(const char* key);

        void setValue(Model::ModelHandler* value);
    };
}


#endif //SERVER_CONTROLLERPAIR_H
