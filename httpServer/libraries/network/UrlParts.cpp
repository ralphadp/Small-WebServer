//
// Created by root on 04-02-20.
//

#include "UrlParts.h"

namespace Network {

    UrlParts::UrlParts() {
        MAX_URL_PARTS = 0;
        m_urlParts = NULL;
    }

    UrlParts::~UrlParts() {
        delete [] m_urlParts;
    }

    unsigned int UrlParts::getUrlPartsLength(const char *key) {

        if (!key) {
            return 0;
        }

        char *keyIndex = Util::clone(key);
        char *part = strtok(keyIndex, "/");
        unsigned int count = 0;

        while (part) {
            if (strlen(part)) {
                count++;
            }
            part = strtok(NULL, "/");
        }

        delete part;
        delete [] keyIndex;

        return MAX_URL_PARTS = count;
    }

    int UrlParts::storeUrlParts(const char *key) {

        if (!key) {
            return 0;
        }

        char* keyIndex = Util::clone(key);
        m_urlParts = new Structure::StringList(MAX_URL_PARTS);

        char* part = strtok(keyIndex, "/");
        while (part) {
            m_urlParts->add(part);
            part = strtok(NULL, "/");
        }

        delete part;
        delete [] keyIndex;

        return m_urlParts->getLength();
    }

    unsigned int UrlParts::size() {
        if (!m_urlParts) {
            return 0;
        }

        return m_urlParts->getLength();
    }

    const char* UrlParts::operator[](unsigned int index) {

        if (!m_urlParts) {
            return NULL;
        }

        return m_urlParts->operator[](index);
    }

}