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

    Model::Result ControllerHandler::deliver(const char* path, const char* content) {
        if (!path || !content) {
            Logger::getInstance()->error("The path or the content is NULL, cannot be processed in the Model");

            return Model::Result("{\"success\":\"false\",\"message\":\"Server error 100\"}");
        }

        Model::ModelHandler* model = this->operator[](path);

        if (!model) {
            model = this->operator[]("not-found");
        }

        return model->process(content);
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
