//
// Created by root on 02-02-20.
//

#include "Model.h"

namespace Model {

    const char* Model::defaultInvalidTemplate = "{\"sucess\":false,\"message\":\"No access allowed\"}";
    const char* Model::defaultErrorTemplate = "{\"sucess\":false,\"message\":\"Server Error 104\"}";

    bool Model::verifyToken(const char* parameters) {
        //TODO: verify the token

        return true;
    }

    const char* Model::getErrorTemplate() {
        return defaultErrorTemplate;
    }

    const char* Model::getInvalidTokenTemplate() {
        return defaultInvalidTemplate;
    }
}
