//
// Created by root on 12-02-20.
//

#include "Url.h"

namespace Structure {
    Url::Url() : String(0) {}

    Url::Url(const char* input) : String(input) {
        split();
    }

    Url::Url(const Url& object) : String(object.m_value) {
        unsigned int index = 0;
        while(index < object.m_parts.getLength()) {
            m_parts.add(object.m_parts[index++]);
        }
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
            //since it is a const char* list, is going to store a copy of the string
            m_parts.add(strdup(part));
            part = strtok(NULL, "/");
        }

        delete [] key;
    }

    Template::List<const char*>& Url::parts() {
        return m_parts;
    }

    Url &Url::operator=(const Url &object) {
        unsigned int index = 0;
        while(index < object.m_parts.getLength()) {
            m_parts.add(object.m_parts[index++]);
        }
        assign(object.value());

        return *this;
    }
}