//
// Created by root on 04-02-20.
//

#include "StringList.h"

namespace Structure {

    StringList::StringList(unsigned int max) {
        MAX_ITEMS = max;
        m_list = new char *[MAX_ITEMS];
        m_index = 0;
    }

    StringList::~StringList() {
        delete [] m_list;
    }

    int StringList::add(const char *value) {

        if (!value) {
            return -1;
        }

        unsigned int length = strlen(value);
        m_list[m_index] = new char[length + 1];

        strcpy(m_list[m_index], value);
        m_list[m_index][length] = 0;

        return m_index++;
    }

    const char* StringList::operator[](unsigned int index) {
        if (index < 0 || index > m_index) {
            return NULL;
        }

        return m_list[index];
    }

    const int StringList::getLength() {
        return m_index;
    }
}