//
// Created by root on 08-02-20.
//

#include "String.h"

namespace Structure {

    String::String() : m_value(0) {
    }

    String::String(const char *value) : m_value(0) {
        assign(value);
    }

    String::String(const String &object) : m_value(0) {
        assign(object.m_value);
    }

    String::~String() {
        clear();
    }

    void String::assign(const char *value) {
        if (value) {
            m_value = new char[strlen(value) + 1];
            strcpy(m_value, value);
            m_value[strlen(value)] = 0;
        }
    }

    std::ostream &operator<<(std::ostream &out, const String &object) {
        out << object.m_value;
        return out;
    }

    String &String::operator=(const char *value) {
        assign(value);
        return *this;
    }

    String &String::operator=(const String &object) {
        assign(object.value());
        return *this;
    }

    inline void String::clear() {
        delete[] m_value;
    }

    const char *String::value() const {
        return m_value;
    }

    bool String::operator==(const char *value) {
        return strcmp(this->m_value, value) == 0;
    }

    bool String::operator==(const String &string) {
        return strcmp(this->m_value, string.m_value) == 0;
    }

    unsigned int String::getHash(unsigned int MAX) const {
        unsigned int hash = 101;//Any prime number

        unsigned int index = 0;
        while (m_value[index] != '\0') {
            hash = hash << 4;
            hash = hash + static_cast<unsigned int>(m_value[index]);
            hash = hash % MAX;
            index++;
        }

        return hash;
    }
}