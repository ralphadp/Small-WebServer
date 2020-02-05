//
// Created by root on 02-02-20.
//

#include "ControllerPair.h"

namespace Controller {

    ControllerPair::ControllerPair() {
        m_key = new char[24];
        m_controller = NULL;
    }

    ControllerPair::ControllerPair(const char* key, Model::ModelHandler* value) {
        m_key = new char[24];
        setKey(key);
        setValue(value);
    }

    ControllerPair::~ControllerPair() {
        delete[] m_key;
        delete m_controller;
    }

    bool ControllerPair::hasKey(const char *key) {
        return strcmp(m_key, key) == 0;
    }

    Model::ModelHandler* ControllerPair::getValue() {
        return m_controller;
    }

    void ControllerPair::setKey(const char *key) {
        strcpy(m_key, key);

        m_pathParts.getUrlPartsLength(key);
        m_pathParts.storeUrlParts(key);
    }

    void ControllerPair::setValue(Model::ModelHandler* value) {
        this->m_controller = value;
    }

    Network::UrlParts ControllerPair::getPathParts() {
        return m_pathParts;
    }

    unsigned int ControllerPair::getMaxLengthParts() {
        return m_pathParts.size();
    }
}