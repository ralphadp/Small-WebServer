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
        delete m_message;
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

    void RequestBag::setContents(const char *content) {
        m_message = new char[contentMessageLength + 1];
        strncpy(m_message, content, contentMessageLength);
        m_message[contentMessageLength] = '\0';
    }

    void RequestBag::copyRestParams(const Network::Map& restParameters) {
        m_restParameters = restParameters;
    }

}