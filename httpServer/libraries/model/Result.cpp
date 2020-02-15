//
// Created by root on 02-02-20.
//

#include "Result.h"

namespace Model {

    Result::Result() {
        m_content = 0;
        m_length = 0;
        m_success = false;
        m_code = 200;
    }

    Result::Result(const Result& result) {
        m_content = Util::clone(result.m_content);
        m_length = result.m_length;
        m_success = result.m_success;
        m_code = result.m_code;
    }

    Result::Result(const char* payload, bool success, unsigned int code) {
        m_content = Util::clone(payload);
        m_length = payload ? strlen(m_content) : 0;
        m_success = success;
        m_code = code;
    }

    Result::~Result() {
        //Need to remove 'content' from static function
        delete [] m_content;
    }

    Result& Result::operator=(const Result& result) {
        this->m_content = Util::clone(result.m_content);
        this->m_length = result.m_length;
        this->m_success = result.m_success;
        this->m_code = result.m_code;

        return *this;
    }
}