//
// Created by root on 02-02-20.
//

#include "Result.h"

namespace Model {

    Result::Result(const char* payload, bool result) {
        m_content = payload;
        m_length = strlen(m_content);
        m_success = result;
    }

    Result::~Result() {
        //nothing to do here
    }

    unsigned int Result::getLength() {
        return m_length;
    }

    const char* Result::getPayload() {
        return m_content;
    }

    const char* Result::getSuccess() {
        return m_success ? "true" : "false";
    }

    bool Result::isSuccessful() {
        return m_success;
    }
}