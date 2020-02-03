//
// Created by root on 02-02-20.
//

#include "Config.h"


namespace Model {

    namespace Item {

        Config::Config() {

        }

        Config::~Config() {

        }

        Result Config::init(const char *params, const char* templateContent) {
            Logger::getInstance()->info("Config::init request payload: %s", params);

            char payload[512] = "";

            if (Model::verifyToken()) {
                if (templateContent) {
                    //TODO: call Db, fake response meanwhile
                    sprintf(payload, templateContent,
                            "#d3d3d3", "#6a6a6a", true, true);
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