//
// Created by root on 02-02-20.
//

#include "ModelHandler.h"

namespace Model {

    ModelHandler::ModelHandler(Result (*pActionFunction)(Network::RequestBag, const char*), const char *templateFilename) {
        m_pAction = pActionFunction;

        char* complete = new char[strlen(Global::TEMPLATE_JSON_DIRECTORY) + strlen(templateFilename) + 1];
        strcpy(complete, Global::TEMPLATE_JSON_DIRECTORY);
        strcat(complete, templateFilename);
        complete[strlen(Global::TEMPLATE_JSON_DIRECTORY) + strlen(templateFilename)] = 0;

        m_templateFilename = complete;

        m_templateFile = new File(NULL);
    }

    ModelHandler::~ModelHandler() {
        delete m_templateFilename;
        delete m_templateFile;
    }

    const char *ModelHandler::fetchTemplate() {

        if (!m_templateFile->open(m_templateFilename, FileAction::Type::READ)) {

            return NULL;
        }

        m_templateFile->read(m_templateFile->size());

        return m_templateFile->getBuffer();
    }

    Result ModelHandler::process(Network::RequestBag parameters) {
        const char* templateContent = fetchTemplate();

        if (!templateContent) {

            return Result(Model::getErrorTemplate(), false);
        }

        if (Model::verifyToken(parameters.getContents())) {

            return this->m_pAction(parameters, templateContent);
        }

        return Result(Model::getInvalidTokenTemplate(), false);
    }
}