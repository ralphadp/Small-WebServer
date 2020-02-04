//
// Created by root on 01-02-20.
//

#ifndef SERVER_CONTROLLER_HANDLER_H
#define SERVER_CONTROLLER_HANDLER_H


#include "../Logger.h"
#include "ControllerPair.h"
#include "../model/ModelHandler.h"
#include "../model/Result.h"

#include "../model/item/User.h"
#include "../model/item/Scheduler.h"
#include "../model/item/Config.h"
#include "../model/item/Server.h"

#include "../network/RequestBag.h"

namespace Controller {

    class ControllerHandler {

        const unsigned int MAX = 6;

        ControllerPair** m_controllerMap;
        unsigned int m_index;
        Model::ModelHandler* m_pSelectedModel;

        void add(const char* path, Model::ModelHandler* handler);
    public:
        explicit ControllerHandler();
        virtual ~ControllerHandler();

        Model::Result deliver(Network::RequestBag request);
        void load();

        Model::ModelHandler* operator[](const char* indexKey);
        const char* paramsChecker(char** url, unsigned int maxParts);
    };

}


#endif //SERVER_CONTROLLER_HANDLER_H
