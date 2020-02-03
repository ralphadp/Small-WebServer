//
// Created by root on 02-02-20.
//

#include "Result.h"

namespace Model {

    Result::Result(const char* payload) {
        m_content = payload;
        m_length = strlen(m_content);
    }

    Result::~Result() {
        //Need to remove 'content' from static function
        delete [] m_content;
    }

    unsigned int Result::getLength() {
        return m_length;
    }

    const char* Result::getPayload() {
        return m_content;
    }
}