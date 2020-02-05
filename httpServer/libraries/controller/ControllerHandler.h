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
#include "../network/Rest.h"
#include "ControllerMap.h"

namespace Controller {

    class ControllerHandler {

        ControllerMap m_post;
        ControllerMap m_get;
        ControllerMap m_unknown;

        Network::Rest m_rest;
    protected:
        void addPOST(const char* path, Model::ModelHandler* handler);
        void addGET(const char* path, Model::ModelHandler* handler);
        Model::ModelHandler* fetchModel(Network::RequestBag requestBag);
        const ControllerMap& getController(const char* verb);
    public:
        explicit ControllerHandler();
        virtual ~ControllerHandler();

        Model::Result deliverProcessing(Network::RequestBag requestBag);
        void configure();


    };

}


#endif //SERVER_CONTROLLER_HANDLER_H
