//
// Created by root on 05-02-20.
//

#ifndef SERVER_CONTROLLER_MAP_H
#define SERVER_CONTROLLER_MAP_H

#include "ControllerPair.h"

namespace Controller {

    class ControllerMap {
        unsigned int MAX_ITEMS = 6;
        ControllerPair** m_controllerMap;
        unsigned int m_index;
    public:
        ControllerMap();
        virtual ~ControllerMap();

        void add(ControllerPair* item);
        Model::ModelHandler* operator[](const char *key) const;
        bool getLength();
        ControllerPair** getPair() const;
    };

}

#endif //SERVER_CONTROLLER_MAP_H
