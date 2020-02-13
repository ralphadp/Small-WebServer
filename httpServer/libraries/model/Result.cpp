//
// Created by root on 02-02-20.
//

#include "Result.h"

namespace Model {

    Result::Result() {
        m_content = 0;
        m_length = 0;
        m_success = false;
    }

    Result::Result(const Result& result) {
        m_content = Util::clone(result.m_content);
        m_length = result.m_length;
        m_success = result.m_success;
    }

    Result::Result(const char* payload, bool success = true) {
        m_content = Util::clone(payload);
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

    bool Result::isSuccess() {
        return m_success;
    }

    Result& Result::operator=(const Result& result) {
        this->m_content = Util::clone(result.m_content);
        this->m_length = result.m_length;
        this->m_success = result.m_success;

        return *this;
    }
}