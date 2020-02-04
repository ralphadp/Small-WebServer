//
// Created by root on 02-02-20.
//

#include "ControllerPair.h"

namespace Controller {

    ControllerPair::ControllerPair() {
        m_key = new char[24];
        m_controller = NULL;
        m_pathParts = NULL;
    }

    ControllerPair::~ControllerPair() {
        delete[] m_key;
        delete m_controller;
        delete [] m_pathParts;
    }

    bool ControllerPair::hasKey(const char *key) {
        return strcmp(this->m_key, key) == 0;
    }

    Model::ModelHandler* ControllerPair::getValue() {
        return m_controller;
    }

    unsigned int ControllerPair::getPathPartsLength(const char* key) {
        char* keyIndex = Util::clone(key);
        char* part = strtok(keyIndex, "/");
        unsigned int count = 0;

        while(part) {
            if (strlen(part)) {
                count++;
            }
            part = strtok(NULL, "/");
        }

        delete [] keyIndex;
        return count;
    }

    void ControllerPair::storePathParts(const char* key) {
        char* keyIndex = Util::clone(key);
        m_pathParts = new char*[MAX_URL_PARTS];
        unsigned int index = 0;

        char* part = strtok(keyIndex, "/");
        while(part) {
            unsigned int length = strlen(part);
            m_pathParts[index] = new char[length + 1];
            strcpy(m_pathParts[index], part);
            m_pathParts[index][length] = 0;

            part = strtok(NULL, "/");
            index++;
        }

        delete [] keyIndex;
    }

    void ControllerPair::setKey(const char *key) {
        strcpy(this->m_key, key);

        MAX_URL_PARTS = getPathPartsLength(key);
        storePathParts(key);
    }

    void ControllerPair::setValue(Model::ModelHandler* value) {
        this->m_controller = value;
    }

    char** ControllerPair::getPathParts() {
        return this->m_pathParts;
    }

    unsigned int ControllerPair::getMaxLengthParts() {
        return MAX_URL_PARTS;
    }
}