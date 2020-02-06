//
// Created by root on 02-02-20.
//

#include "Result.h"

namespace Model {

    Result::Result(const char* payload, bool success = true) {
        m_content = payload;
        m_length = payload ? strlen(m_content) : 0;
        m_success = success;
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

    bool Result::isSucess() {
        return m_success;
    }
}