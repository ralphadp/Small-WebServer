//
// Created by root on 30-01-20.
//

#include "Pair.h"

namespace Network {

    Pair::Pair() {
        key = new char[24];
        value = new char[72];
    }

    Pair::~Pair() {
        delete [] key;
        delete [] value;
    }

    bool Pair::hasKey(const char *key) {
        return strcmp(this->key, key) == 0;
    }

    const char *Pair::getValue() {
        return value;
    }

    void Pair::setKey(const char *key) {
        strcpy(this->key, key);
    }

    void Pair::setValue(const char *value) {
        strcpy(this->value, value);
    }
}