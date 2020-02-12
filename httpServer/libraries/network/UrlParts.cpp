//
// Created by root on 04-02-20.
//

#include "UrlParts.h"

namespace Network {

    int UrlParts::storeUrlParts(const char *key) {

        if (!key) {
            return 0;
        }

        char* keyIndex = Util::clone(key);
        char* part = strtok(keyIndex, "/");
        while (part) {
            m_urlParts.add(part);
            part = strtok(NULL, "/");
        }

        delete part;
        delete [] keyIndex;

        return m_urlParts.getLength();
    }

    unsigned int UrlParts::size() {
        return m_urlParts.getLength();
    }

    const char* UrlParts::operator[](unsigned int index) {
        return m_urlParts[index].value();
    }

}