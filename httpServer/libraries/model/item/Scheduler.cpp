//
// Created by root on 02-02-20.
//

#include "Scheduler.h"

namespace Model {

    namespace Item {

        Scheduler::Scheduler() {

        }

        Scheduler::~Scheduler() {

        }

        Result Scheduler::getList(const char *params, const char* templateContent) {
            Logger::getInstance()->info("Scheduler::getList request payload: %s", params);

            char payload[640] = "";

            if (Model::verifyToken()) {
                if (templateContent) {
                    //TODO: call Db, fake response meanwhile
                    sprintf(payload, templateContent,
                            411, 341, 2, "2020-04-01T03:30:00PM");
                } else {
                    strcpy(payload, defaultErrorTemplate);
                }
            } else {
                strcpy(payload, defaultInvalidTemplate);
            }

            Result result(payload, true);
            return result;
        }

        Result Scheduler::getInfo(const char *params, const char* templateContent) {
            Logger::getInstance()->info("Scheduler::getInfo request payload: %s", params);

            char payload[1024] = "";

            if (Model::verifyToken()) {
                if (templateContent) {
                    //TODO: call Db, fake response meanwhile
                    sprintf(payload, templateContent, 3124, 201, 133,
                        "2020-02-02", "03:30:00PM", "04:15:00PM",
                        12, "Maria Zelalla", "7342311",
                        "America 5142", "456342", 1, "Bring the laboratory analisys");
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