//
// Created by root on 01-02-20.
//

#include "ControllerHandler.h"


namespace Controller {

    ControllerHandler::ControllerHandler() {
        m_controllerMap = new ControllerPair*[MAX];
        m_index = 0;
        m_pSelectedModel = NULL;
    }

    ControllerHandler::~ControllerHandler() {

        for(unsigned int index = 0; index < MAX; index++) {
            delete m_controllerMap[index];
        }
        delete m_controllerMap;
    }

    Model::Result ControllerHandler::deliver(Network::RequestBag requestBag) {
        const char* urlPath = requestBag.getUrlPath();
        if (!urlPath || !requestBag.getContents()) {
            Logger::getInstance()->error("The path or the content is NULL, cannot be processed in the Model");

            return Model::Result("{\"success\":\"false\",\"message\":\"Server error 100\"}");
        }

        Model::ModelHandler* model = this->operator[](urlPath);

        if (!model) {

            model = m_pSelectedModel;

            if (!model) {
                model = this->operator[]("not-found");
            }
        }

        return model->process(requestBag.getContents());
    }

    void  ControllerHandler::load() {
        add("/config", new Model::ModelHandler(
                Model::Item::Config::init, "./templates/json/init_response.json"
        ));
        add("/login", new Model::ModelHandler(
                Model::Item::User::login, "./templates/json/login_response.json"
        ));
        add("/schedule", new Model::ModelHandler(
                Model::Item::Scheduler::getList, "./templates/json/scheduler-list.json"
        ));
        add("/schedule/:datetime", new Model::ModelHandler(
                Model::Item::Scheduler::getInfo, "./templates/json/scheduler-info.json"
        ));
        add("not-found", new Model::ModelHandler(
                Model::Item::Server::notFound, "./templates/json/not-found.json"
        ));
        //for(int ptr = 0; ptr < 5; ptr++) {
        //    for (int index = 0; index < m_controllerMap[ptr]->getMaxLengthParts(); index++) {
        //        Logger::getInstance()->info("controller[%d]:%s", ptr, m_controllerMap[ptr]->getPathParts()[index]);
        //    }
        //}
    }

    void ControllerHandler::add(const char* path, Model::ModelHandler* handler) {
        m_controllerMap[m_index] = new ControllerPair;
        m_controllerMap[m_index]->setKey(path);
        m_controllerMap[m_index]->setValue(handler);

        m_controllerMap[++m_index] = NULL;
    }

    Model::ModelHandler* ControllerHandler::operator[](const char* indexKey)
    {
        if (!indexKey || strlen(indexKey) == 0)
        {
            Logger::getInstance()->error("key is null");

            return NULL;
        }

        ControllerPair** iterator = m_controllerMap;
        while(*iterator != NULL) {
            if ((*iterator)->hasKey(indexKey)) {
                return (*iterator)->getValue();
            }
            iterator++;
        }

        return NULL;
    }

    const char* ControllerHandler::paramsChecker(char** url, unsigned int maxParts)
    {
        if (!url) {
            Logger::getInstance()->error("Url part list is empty.");

            return NULL;
        }

        m_pSelectedModel = NULL;
        ControllerPair** iterator = m_controllerMap;
        char** part = NULL;

        while(*iterator != NULL) {

            if ((*iterator)->getMaxLengthParts() != maxParts) {
                iterator++;
                continue;
            }

            unsigned int index = 0;
            part = (*iterator)->getPathParts();

            //The first part of th Rest cannot be variable
            if (strcmp(part[index], url[index]) == 0) {

                index++;
                bool onTrack = true;
                char* parameters = new char[512];
                strcpy(parameters, "");

                while (index < maxParts && onTrack) {

                    if (strcmp(part[index], url[index]) != 0) {
                        onTrack = false;
                        if (part[index][0] == ':') {
                            //Is a variable part of the Rest

                            if (!strlen(parameters)) {
                                sprintf(parameters, "%s=%s", &part[index][1], url[index]);
                            } else {
                                sprintf(parameters, "%s&%s=%s", parameters, &part[index][1], url[index]);
                            }

                            onTrack = true;
                        }
                    } else {
                        onTrack = true;
                    }

                    index++;
                }

                if (onTrack) {
                    m_pSelectedModel = (*iterator)->getValue();
                    Logger::getInstance()->info("Path variables: '%s'", parameters);
                    return parameters;
                }

                delete [] parameters;
            }

            iterator++;
        }

        return NULL;
    }

}
