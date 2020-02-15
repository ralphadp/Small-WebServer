//
// Created by root on 12-02-20.
//

#include "Url.h"

namespace Structure {
    Url::Url() : String(0) {}

    Url::Url(const char* input) : String(input) {
        split();
    }

    Url::Url(const String& object) : String(object) {
        split();
    }

    Url::~Url() {
    }

    void Url::split() {

        if (!m_value) {
            return;
        }

        char* key = Util::clone(m_value);

        char* part = strtok(key, "/");
        while (part) {
            m_parts.add(part);
            part = strtok(NULL, "/");
        }

        delete [] key;
    }

    Template::List<const char*>& Url::parts() {
        return m_parts;
    }
}