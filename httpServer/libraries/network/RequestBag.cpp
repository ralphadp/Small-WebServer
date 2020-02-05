//
// Created by root on 04-02-20.
//

#include "RequestBag.h"

namespace Network {

    RequestBag::RequestBag() {
        m_message = NULL;
        contentMessageLength = 0;
    }

    RequestBag::~RequestBag() {
        delete [] m_message;
    }

    const char* RequestBag::getContents() {
        return m_message;
    }

    const char* RequestBag::getUrlPath() {
        return m_urlPath;
    }

    const char* RequestBag::getVersion() {
        return m_version;
    }

    bool RequestBag::setContents(const char *content) {
        unsigned int length = strlen(content);

        if (!content) {
            return false;
        }

        if (!length) {
            return false;
        }

        m_message = new char[length + 1];
        strncpy(m_message, content, length);
        m_message[length] = '\0';

        return true;
    }

    void RequestBag::copyRestParams(const Structure::Map& restParameters) {
        m_restParameters = restParameters;
    }

}