//
// Created by root on 01-02-20.
//

#include "User.h"


namespace Model {

    namespace Item {

        User::User() {

        }

        User::~User() {

        }

        bool User::checkCredentials() {
            //TODO: need to connect another server e.g. mysql, redis, to validate credentials
            return true;
        }

        /*TODO: Change insecure token generator , use a library instead*/
        void User::generateToken(char *token, unsigned int length) {
            static const char alphanumeric[] =
                    "0123456789"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "abcdefghijklmnopqrstuvwxyz";

            srand(time(NULL));

            for (unsigned int index = 0; index < length; index++) {
                token[index] = alphanumeric[rand() % (sizeof(alphanumeric) - 1)];
            }

            token[length] = 0;
        }

        Result User::login(const char *params, const char* templateContent) {
            Logger::getInstance()->info("User:verify request payload: %s", params);

            char token[17] = "";
            char payload[512] = "";
            bool passed = checkCredentials();

            if (passed) {
                if (templateContent) {
                    generateToken(token, 16);
                    sprintf(payload, templateContent, token, "true");
                } else {
                    strcpy(payload, defaultErrorTemplate);
                }
            } else {
                strcpy(payload, defaultInvalidTemplate);
            }

            Result result(payload, passed);
            return result;
        }
    }
}