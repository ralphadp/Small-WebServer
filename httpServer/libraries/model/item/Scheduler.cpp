//
// Created by root on 02-02-20.
//

#include "Scheduler.h"

namespace Model {

    namespace Item {

        Result Scheduler::getList(Network::RequestBag params, const char* templateContent) {
            Logger::getInstance()->info("::%s request rest params: %d", __func__, params.m_restParameters.getLength());

            char* payload = new char[strlen(templateContent) + 40];

            //TODO: call Db, fake response meanwhile
            sprintf(payload, templateContent, 411, 341, 2, "2020-04-01T03:30:00PM");

            return Result(payload);
        }

        Result Scheduler::getInfo(Network::RequestBag params, const char* templateContent) {
            Logger::getInstance()->info("::%s request rest params: %d", __func__, params.m_restParameters.getLength());

            char* payload = new char[strlen(templateContent) + 256];

            //TODO: call Db, fake response meanwhile
            sprintf(payload, templateContent, 3124, 201, 133, "2020-02-02",
                "03:30:00PM", "04:15:00PM", 12, "Maria Zelalla",
                "7342311", "America 5142", "456342", 1, "Bring the laboratory analisys");

            return Result(payload);
        }
    }
}