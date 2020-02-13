//
// Created by root on 01-02-20.
//

#ifndef SERVER_CONTROLLER_HANDLER_H
#define SERVER_CONTROLLER_HANDLER_H


#include "../Logger.h"
#include "../model/ModelHandler.h"
#include "../model/Result.h"

#include "../model/item/User.h"
#include "../model/item/Scheduler.h"
#include "../model/item/Config.h"
#include "../model/item/Server.h"

#include "../network/RequestBag.h"
#include "../network/Rest.h"
#include "../structure/String.h"
#include "../structure/template/Map.h"

namespace Controller {

    class ControllerHandler {

        Template::Map<Structure::String, Model::ModelHandler*> m_post;
        Template::Map<Structure::String, Model::ModelHandler*> m_get;
        Template::Map<Structure::String, Model::ModelHandler*> m_unknown;

        Network::Rest m_rest;
    protected:
        Model::ModelHandler* fetchModel(Network::RequestBag& requestBag);
        const Template::Map<Structure::String, Model::ModelHandler*>& getController(const char* verb);
    public:
        explicit ControllerHandler();
        virtual ~ControllerHandler();

        void POST(const char* path, Model::ModelHandler* handler);
        void GET(const char* path, Model::ModelHandler* handler);

        Model::Result deliverProcessing(Network::RequestBag requestBag);
        void configure();

    };

}


#endif //SERVER_CONTROLLER_HANDLER_H
