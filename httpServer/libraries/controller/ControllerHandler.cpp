//
// Created by root on 01-02-20.
//

#include "ControllerHandler.h"


namespace Controller {

    ControllerHandler::ControllerHandler() {

    }

    ControllerHandler::~ControllerHandler() {

    }

    Model::ModelHandler* ControllerHandler::fetchModel(Network::RequestBag& requestBag) {

        const char* URL_PATH = requestBag.getUrlPath();
        const Template::Map<Structure::String, Model::ModelHandler*>& controller = getController(requestBag.getVerb());

        if (controller.exist(URL_PATH)) {
            return controller[URL_PATH];
        }

        const char* REST_URL_PATH = m_rest.process(requestBag);

        if (!REST_URL_PATH) {
            return m_post["not-found"];
        }

        if (controller.exist(REST_URL_PATH)) {
            return controller[REST_URL_PATH];
        }

        Logger::getInstance()->error("The Model attached to %s is empty.", REST_URL_PATH);

        return NULL;
    }

    Model::Result ControllerHandler::deliverProcessing(Network::RequestBag requestBag) {

        if (!requestBag.getUrlPath()) {
            Logger::getInstance()->error("The path is empty, cannot be processed in the Model");

            return Model::Result("{\"success\":\"false\",\"message\":\"Server error 102\"}", false);
        }

        Model::ModelHandler* model = fetchModel(requestBag);
        if (!model) {
            return Model::Result("{\"success\":\"false\",\"message\":\"Server error 103\"}", false);
        }

        return model->process(requestBag);
    }

    void ControllerHandler::configure() {
        POST("/login", new Model::ModelHandler(
                Model::Item::User::login, "login_response.json"
        ));
        POST("/schedule", new Model::ModelHandler(
                Model::Item::Scheduler::getList, "scheduler-list.json"
        ));
        POST("/schedule/:datetime", new Model::ModelHandler(
                Model::Item::Scheduler::getInfo, "scheduler-info.json"
        ));
        POST("not-found", new Model::ModelHandler(
                Model::Item::Server::notFound, "not-found.json"
        ));
        GET("/config", new Model::ModelHandler(
                Model::Item::Config::init, "init_response.json"
        ));
    }

    void ControllerHandler::POST(const char* path, Model::ModelHandler* handler) {
        m_rest.addPostUrl(path);
        m_post[path] = handler;
    }

    void ControllerHandler::GET(const char* path, Model::ModelHandler* handler) {
        m_rest.addGetUrl(path);
        m_get[path] = handler;
    }

    const Template::Map<Structure::String, Model::ModelHandler*>& ControllerHandler::getController(const char* verb) {
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
