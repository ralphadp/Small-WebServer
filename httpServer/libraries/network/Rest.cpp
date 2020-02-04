//
// Created by root on 04-02-20.
//

#include "Rest.h"

namespace Network {

    Rest::Rest() {

    }

    Rest::~Rest() {
        for(unsigned int index = 0; index < MAX_URL_PARTS; index++) {
            delete [] m_urlParts[index];
        }
    }

    unsigned int Rest::getUrlPartsLength(const char* urlPath) {
        char* url = Util::clone(urlPath);

        char* part = strtok(url, "/");
        unsigned int count = 0;

        while(part) {
            if (strlen(part)) {
                count++;
            }
            part = strtok(NULL, "/");
        }

        delete url;
        MAX_URL_PARTS = count;

        return count;
    }

    void Rest::storeUrlParts(const char* urlPath) {
        char* url = Util::clone(urlPath);

        m_urlParts = new char*[MAX_URL_PARTS];
        unsigned int index = 0;

        char* part = strtok(url, "/");
        while(part) {
            unsigned int lengthPart = strlen(part);
            m_urlParts[index] = new char[lengthPart + 1];
            strcpy(m_urlParts[index], part);
            m_urlParts[index][lengthPart] = 0;

            part = strtok(NULL, "/");
            index++;
        }

        delete [] url;
    }

    void Rest::parseParameters(const char* parameters) {

        if (!parameters) {
            return;
        }

        char QUERY[1024];
        strcpy(QUERY, parameters);

        char* pParameter = strtok(QUERY, "&");
        while(pParameter) {

            char PARAM[512];
            strcpy(PARAM, pParameter);
            char* token = strtok(PARAM, "=");
            while(token) {
                Pair* pair = new Pair();
                pair->setKey(token);

                token = strtok(NULL, "=");
                if (token) {
                    pair->setValue(token);
                    m_parameters.add(pair);
                }
            }

            pParameter = strtok(NULL, "&");
        }
    }

    Controller::ControllerPair* Rest::processParams(Controller::ControllerPair** controllerMap)
    {
        if (!m_urlParts) {
            Logger::getInstance()->error("Url part list is empty.");

            return NULL;
        }

        Controller::ControllerPair** iterator = controllerMap;
        char** part = NULL;

        while(*iterator != NULL) {

            if ((*iterator)->getMaxLengthParts() != MAX_URL_PARTS) {
                iterator++;
                continue;
            }

            unsigned int index = 0;
            part = (*iterator)->getPathParts();

            //The first part of th Rest cannot be variable
            if (strcmp(part[index], m_urlParts[index]) == 0) {

                index++;
                bool onTrack = true;
                char* parameters = new char[512];
                strcpy(parameters, "");

                while (index < MAX_URL_PARTS && onTrack) {

                    if (strcmp(part[index], m_urlParts[index]) != 0) {
                        onTrack = false;
                        if (part[index][0] == ':') {
                            //Is a variable part of Rest

                            if (!strlen(parameters)) {
                                sprintf(parameters, "%s=%s", &part[index][1], m_urlParts[index]);
                            } else {
                                sprintf(parameters, "%s&%s=%s", parameters, &part[index][1], m_urlParts[index]);
                            }

                            onTrack = true;
                        }
                    } else {
                        onTrack = true;
                    }

                    index++;
                }

                if (onTrack) {
                    Logger::getInstance()->info("Rest variables tape: '%s'", parameters);

                    parseParameters(parameters);

                    return *iterator;
                }

                delete [] parameters;
            }

            iterator++;
        }

        return NULL;
    }

    Controller::ControllerPair* Rest::process(const char* urlPath, Controller::ControllerPair** controllerMap) {

        if (!urlPath) {
            Logger::getInstance()->warning("No input url path to parse.");

            return NULL;
        }

        if (!controllerMap) {
            Logger::getInstance()->warning("No controller map provided.");

            return NULL;
        }

        getUrlPartsLength(urlPath);
        storeUrlParts(urlPath);

        return processParams(controllerMap);
    }

    const Map& Rest::getParameters() {
        return m_parameters;
    }
}