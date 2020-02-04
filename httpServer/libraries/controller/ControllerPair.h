//
// Created by root on 02-02-20.
//

#ifndef SERVER_CONTROLLERPAIR_H
#define SERVER_CONTROLLERPAIR_H

#include <string.h>

#include "../model/ModelHandler.h"
#include "../Util.h"

namespace Controller {

    class ControllerPair {
        char *m_key;
        Model::ModelHandler* m_controller;
        char** m_pathParts;
        unsigned int MAX_URL_PARTS;

        unsigned int getPathPartsLength(const char* key);
        void storePathParts(const char* key);

    public:
        ControllerPair();

        virtual ~ControllerPair();

        bool hasKey(const char* key);

        Model::ModelHandler* getValue();

        void setKey(const char* key);

        void setValue(Model::ModelHandler* value);

        char** getPathParts();

        unsigned int getMaxLengthParts();
    };
}


#endif //SERVER_CONTROLLERPAIR_H
