//
// Created by root on 02-02-20.
//

#include "Server.h"

namespace Model {

    namespace Item {

        Result Server::notFound(Network::RequestBag& params, const char* templateContent) {
            Logger::getInstance()->info("::%s request rest params: %d", __func__, params.getRestParameters().length());

            return Result(templateContent, false);
        }
    }
}