//
// Created by root on 04-02-20.
//

#include "Rest.h"

namespace Network {

    Rest::Rest() {
    }

    Rest::~Rest() {
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
                Structure::String key(token);
                token = strtok(NULL, "=");
                if (token) {
                    m_parameters[key] = token;
                }
            }

            pParameter = strtok(NULL, "&");
        }
    }

    Controller::ControllerPair* Rest::processParams(Controller::ControllerPair** controllerMap)
    {
        if (!m_urlParts.size()) {
            Logger::getInstance()->error("Url part list is empty.");

            return NULL;
        }

        Controller::ControllerPair** iterator = controllerMap;

        while(*iterator != NULL) {

            if ((*iterator)->getMaxLengthParts() != m_urlParts.size()) {
                iterator++;
                continue;
            }

            unsigned int index = 0;
            UrlParts part = (*iterator)->getPathParts();

            //The first part of th Rest cannot be variable
            if (strcmp(part[index], m_urlParts[index]) == 0) {

                index++;
                bool onTrack = true;
                char* parametersTape = new char[512];
                strcpy(parametersTape, "");

                while (index < m_urlParts.size() && onTrack) {

                    if (strcmp(part[index], m_urlParts[index]) != 0) {
                        onTrack = false;

                        if (part[index][0] == ':') {
                            //Is a variable for Rest parameters

                            if (!strlen(parametersTape)) {
                                sprintf(parametersTape, "%s=%s", &part[index][1], m_urlParts[index]);
                            } else {
                                sprintf(parametersTape, "%s&%s=%s", parametersTape, &part[index][1], m_urlParts[index]);
                            }
                            onTrack = true;
                        }
                    } else {
                        onTrack = true;
                    }

                    index++;
                }

                if (onTrack) {
                    Logger::getInstance()->info("Rest variables tape: '%s'", parametersTape);

                    parseParameters(parametersTape);
                    delete [] parametersTape;

                    return *iterator;
                }

                delete [] parametersTape;
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

        m_urlParts.getUrlPartsLength(urlPath);
        m_urlParts.storeUrlParts(urlPath);

        return processParams(controllerMap);
    }

    Template::Map<Structure::String, Structure::String>& Rest::getParameters() {
        return m_parameters;
    }
}