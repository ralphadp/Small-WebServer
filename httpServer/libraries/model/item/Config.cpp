//
// Created by root on 02-02-20.
//

#include "Config.h"


namespace Model {

    namespace Item {

        Result Config::init(Network::RequestBag params, const char* templateContent) {
            Logger::getInstance()->info("::%s request rest params: %d", __func__, params.m_restParameters.getLength());

            char* payload = new char[strlen(templateContent) + 24];

            //TODO: call Db, fake response meanwhile
            sprintf(payload, templateContent, "#d3d3d3", "#6a6a6a", true, true);

            return Result (payload);
        }
    }
}