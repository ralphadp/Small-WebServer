//
// Created by root on 02-02-20.
//

#include "ModelHandler.h"

namespace Model {

    ModelHandler::ModelHandler(Result (*pActionFunction)(const char*, const char*), const char *templateFilename) {
        m_pAction = pActionFunction;
        m_templateFilename = templateFilename;
        m_templateFile = new File(NULL);
    }

    ModelHandler::~ModelHandler() {
        delete m_templateFile;
    }

    const char *ModelHandler::fetchTemplate() {

        if (!m_templateFile->open(m_templateFilename, FileAction::Type::READ)) {

            return NULL;
        }

        m_templateFile->read(m_templateFile->size());

        return m_templateFile->getBuffer();
    }

    Result ModelHandler::process(const char *parameters) {

        return this->m_pAction(parameters, fetchTemplate());
    }
}