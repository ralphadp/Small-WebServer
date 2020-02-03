//
// Created by root on 02-02-20.
//

#include "Config.h"


namespace Model {

    namespace Item {

        Result Config::init(const char *params, const char* templateContent) {
            Logger::getInstance()->info("Config::init request payload: %s", params);

            char* payload = new char[strlen(templateContent) + 24];

            //TODO: call Db, fake response meanwhile
            sprintf(payload, templateContent, "#d3d3d3", "#6a6a6a", true, true);

            return Result (payload);
        }
    }
}