//
// Created by root on 04-02-20.
//

#ifndef SERVER_REST_H
#define SERVER_REST_H

#include <string.h>

#include "../Logger.h"
#include "../controller/ControllerPair.h"
#include "Map.h"

namespace Network {

    class Rest {
        unsigned int MAX_URL_PARTS;
        char** m_urlParts;
    protected:
        Map m_parameters;

        unsigned int getUrlPartsLength(const char* url);
        void storeUrlParts(const char* url);
        void parseParameters(const char* parameters);
        Controller::ControllerPair* processParams(Controller::ControllerPair** controllerMap);
    public:
        Rest();
        virtual ~Rest();

        Controller::ControllerPair* process(const char* urlPath, Controller::ControllerPair** controllerMap);
        const Map& getParameters();
    };
}


#endif //SERVER_REST_H
