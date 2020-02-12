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
    void RequestBag::setVerb(const char* verb) {
        strcpy(m_verb, verb);
    }

    void RequestBag::setUrlPath(const char* url) {
        strcpy(m_urlPath, url);
    }

    void RequestBag::setVersion(const char* version) {
        strcpy(m_version, version);
    }

    void RequestBag::setMessageLength(unsigned int length) {
        contentMessageLength = length;
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

    const char* RequestBag::getVerb() const {
        return m_verb;
    }

    const char* RequestBag::getContents() const {
        return m_message;
    }

    unsigned int RequestBag::getContentLength() const {
        return contentMessageLength;
    }

    const char* RequestBag::getUrlPath() const {
        return m_urlPath;
    }

    const char* RequestBag::getVersion() const {
        return m_version;
    }

    void RequestBag::copyRestParams(const Template::Map<Structure::String, Structure::String>& restParameters) {
        m_restParameters = restParameters;
    }

    Template::Map<Structure::String, Structure::String>& RequestBag::getRestParameters() {
        return m_restParameters;
    }

    void RequestBag::copyQueryParams(const Template::Map<Structure::String, Structure::String>& restParameters) {
        m_queryParameters = restParameters;
    }

    Template::Map<Structure::String, Structure::String>& RequestBag::getQueryParameters() {
        return m_queryParameters;
    }

    /**
     * Does the url has a query part
     * @param path
     * @return
     */
    bool RequestBag::hasQuery() {
        return strchr(m_urlPath, '?') != NULL;
    }

    /**
     * Removes the query from path
     * @param path
     * @return
     */
    char* RequestBag::removeQueryFromUrl() {
        return strtok(m_urlPath, "?");
    }

}