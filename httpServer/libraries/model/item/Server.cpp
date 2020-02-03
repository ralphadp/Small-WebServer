//
// Created by root on 02-02-20.
//

#include "Server.h"

namespace Model {

    namespace Item {

        Result Server::notFound(const char *params, const char* templateContent) {
            Logger::getInstance()->info("%s request payload: %s", __func__, params);

            return Result(templateContent);
        }
    }
}