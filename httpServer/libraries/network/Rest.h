//
// Created by root on 04-02-20.
//

#ifndef SERVER_REST_H
#define SERVER_REST_H

#include <string.h>

#include "../Logger.h"
#include "../controller/ControllerPair.h"

#include "UrlParts.h"
#include "../structure/String.h"
#include "../structure/template/Map.h"

namespace Network {

    class Rest {
        UrlParts m_urlParts;
    protected:
        Template::Map<Structure::String, Structure::String> m_parameters;

        void parseParameters(const char* parameters);
        Controller::ControllerPair* processParams(Controller::ControllerPair** controllerMap);
    public:
        Rest();
        virtual ~Rest();

        Controller::ControllerPair* process(const char* urlPath, Controller::ControllerPair** controllerMap);
        Template::Map<Structure::String, Structure::String>& getParameters();
    };
}

#endif //SERVER_REST_H
