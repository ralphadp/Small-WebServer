//
// Created by root on 02-02-20.
//

#include "Server.h"

namespace Model {

    namespace Item {

        Server::Server() {

        }

        Server::~Server() {

        }

        Result Server::notFound(const char *params, const char* templateContent) {
            Logger::getInstance()->info("Server::notFound request payload: %s", params);

            char payload[512] = "";

            if (Model::verifyToken()) {
                if (templateContent) {
                    //TODO: call Db, fake response meanwhile
                    strcpy(payload, templateContent);
                } else {
                    strcpy(payload, defaultErrorTemplate);
                }
            } else {
                strcpy(payload, defaultInvalidTemplate);
            }

            Result result(payload, true);
            return result;
        }
    }
}