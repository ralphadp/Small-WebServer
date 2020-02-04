//
// Created by root on 01-02-20.
//

#include "ControllerHandler.h"


namespace Controller {

    ControllerHandler::ControllerHandler() {
        m_controllerMap = new ControllerPair*[MAX];
        m_index = 0;
    }

    ControllerHandler::~ControllerHandler() {

        for(unsigned int index = 0; index < MAX; index++) {
            delete m_controllerMap[index];
        }
        delete m_controllerMap;
    }

    Model::Result ControllerHandler::deliverProcessing(Network::RequestBag requestBag) {
        const char* urlPath = requestBag.getUrlPath();

        if (!urlPath || !requestBag.getContents()) {
            Logger::getInstance()->error("The path or the content is NULL, cannot be processed in the Model");

            return Model::Result("{\"success\":\"false\",\"message\":\"Server error 100\"}");
        }

        Model::ModelHandler* model = this->operator[](urlPath);

        if (!model) {

            Controller::ControllerPair* controllerSelected = m_rest.process(urlPath, m_controllerMap);

            if (controllerSelected) {
                model = controllerSelected->getValue();
                if (model) {
                    requestBag.copyRestParams(m_rest.getParameters());
                } else {
                    Logger::getInstance()->error("The Model attached to %s is empty.", urlPath);

                    return Model::Result("{\"success\":\"false\",\"message\":\"Server error 102\"}");
                }
            } else {
                model = this->operator[]("not-found");
            }
        }

        return model->process(requestBag);
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

}
