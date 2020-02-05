//
// Created by root on 01-02-20.
//

#include "ControllerHandler.h"


namespace Controller {

    ControllerHandler::ControllerHandler() {

    }

    ControllerHandler::~ControllerHandler() {

    }

    Model::ModelHandler* ControllerHandler::fetchModel(Network::RequestBag requestBag) {

        const char* URL_PATH = requestBag.getUrlPath();

        const ControllerMap& controller = getController(requestBag.getVerb());

        Model::ModelHandler* model = controller[URL_PATH];

        if (!model) {

            Controller::ControllerPair* restController = m_rest.process(URL_PATH, controller.getPair());

            if (restController) {
                model = restController->getValue();
                if (model) {
                    requestBag.copyRestParams(m_rest.getParameters());
                } else {
                    Logger::getInstance()->error("The Model attached to %s is empty.", URL_PATH);

                    return NULL;
                }
            } else {
                model = m_post["not-found"];
            }
        }

        return model;
    }

    Model::Result ControllerHandler::deliverProcessing(Network::RequestBag requestBag) {

        if (!requestBag.getUrlPath() || !requestBag.getContents()) {
            Logger::getInstance()->error("The path or the content is NULL, cannot be processed in the Model");

            return Model::Result("{\"success\":\"false\",\"message\":\"Server error 100\"}");
        }

        Model::ModelHandler* model = fetchModel(requestBag);

        if (!model) {
            return Model::Result("{\"success\":\"false\",\"message\":\"Server error 102\"}");
        }

        return model->process(requestBag);
    }

    void  ControllerHandler::configure() {
        addPOST("/config", new Model::ModelHandler(
                Model::Item::Config::init, "./templates/json/init_response.json"
        ));
        addPOST("/login", new Model::ModelHandler(
                Model::Item::User::login, "./templates/json/login_response.json"
        ));
        addPOST("/schedule", new Model::ModelHandler(
                Model::Item::Scheduler::getList, "./templates/json/scheduler-list.json"
        ));
        addPOST("/schedule/:datetime", new Model::ModelHandler(
                Model::Item::Scheduler::getInfo, "./templates/json/scheduler-info.json"
        ));
        addPOST("not-found", new Model::ModelHandler(
                Model::Item::Server::notFound, "./templates/json/not-found.json"
        ));
        //for(int ptr = 0; ptr < 5; ptr++) {
        //    for (int index = 0; index < m_controllerMap[ptr]->getMaxLengthParts(); index++) {
        //        Logger::getInstance()->info("controller[%d]:%s", ptr, m_controllerMap[ptr]->getPathParts()[index]);
        //    }
        //}
        addGET("config", new Model::ModelHandler(
                Model::Item::Server::notFound, "./templates/json/not-found.json"
        ));

    }

    void ControllerHandler::addPOST(const char* path, Model::ModelHandler* handler) {
        m_post.add(new ControllerPair(path, handler));
    }

    void ControllerHandler::addGET(const char* path, Model::ModelHandler* handler) {
        m_get.add(new ControllerPair(path, handler));
    }

    const ControllerMap& ControllerHandler::getController(const char* verb) {
        if (!verb) {
            return m_unknown;
        }

        if (strcmp(verb, "GET") == 0) {
            return m_get;
        } else if (strcmp(verb, "POST") == 0) {
            return m_post;
        }

        return m_unknown;
    }

}
