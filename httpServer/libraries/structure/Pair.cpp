//
// Created by root on 30-01-20.
//

#include "Pair.h"

namespace Structure {

    Pair::Pair() {
        m_key = new char[24];
        m_value = new char[72];
    }

    Pair::~Pair() {
        delete [] m_key;
        delete [] m_value;
    }

    bool Pair::hasKey(const char *key) {
        return strcmp(m_key, key) == 0;
    }

    const char *Pair::getValue() {
        return m_value;
    }

    void Pair::setKey(const char *key) {
        strcpy(m_key, key);
    }

    void Pair::setValue(const char *value) {
        strcpy(m_value, value);
    }
}