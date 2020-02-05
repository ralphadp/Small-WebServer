//
// Created by root on 02-02-20.
//

#ifndef SERVER_CONTROLLERPAIR_H
#define SERVER_CONTROLLERPAIR_H

#include <string.h>

#include "../model/ModelHandler.h"
#include "../Util.h"
#include "../network/UrlParts.h"

namespace Controller {

    class ControllerPair {
        char *m_key;
        Model::ModelHandler* m_controller;
        Network::UrlParts m_pathParts;

    public:
        ControllerPair();

        virtual ~ControllerPair();

        bool hasKey(const char* key);

        Model::ModelHandler* getValue();

        void setKey(const char* key);

        void setValue(Model::ModelHandler* value);

        Network::UrlParts getPathParts();

        unsigned int getMaxLengthParts();
    };
}


#endif //SERVER_CONTROLLERPAIR_H
