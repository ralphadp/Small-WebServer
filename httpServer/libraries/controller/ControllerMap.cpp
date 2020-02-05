//
// Created by root on 05-02-20.
//

#include "ControllerMap.h"

namespace Controller {

    ControllerMap::ControllerMap() {
        m_controllerMap = new ControllerPair*[MAX_ITEMS];
        m_index = 0;
    }

    ControllerMap::~ControllerMap() {
        for(unsigned int index = 0; index < MAX_ITEMS; index++) {
            delete m_controllerMap[index];
        }
        delete m_controllerMap;
    }

    void ControllerMap::add(ControllerPair* item) {
        if (m_index < MAX_ITEMS) {
            m_controllerMap[m_index++] = item;
        }
    }

    Model::ModelHandler* ControllerMap::operator[](const char *key) const {
        if (!key || strlen(key) == 0) {
            Logger::getInstance()->error("key is null");

            return NULL;
        }

        ControllerPair **iterator = m_controllerMap;
        while (*iterator != NULL) {
            if ((*iterator)->hasKey(key)) {
                return (*iterator)->getValue();
            }
            iterator++;
        }

        return NULL;
    }

    bool ControllerMap::getLength() {
        return m_index;
    }

    ControllerPair** ControllerMap::getPair() const {
        return m_controllerMap;
    }
}