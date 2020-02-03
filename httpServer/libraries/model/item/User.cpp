//
// Created by root on 01-02-20.
//

#include "User.h"


namespace Model {

    namespace Item {
        const unsigned int User::MAX_TOKEN_LENGTH = 16;
        const char* User::defaultBadCredentialsTemplate = "{\"sucess\":\"false\",\"message\":\"username or password are not correct\"}";

        bool User::checkCredentials() {
            //TODO: need to connect another server e.g. mysql, redis, to validate credentials
            return true;
        }

        Result User::login(const char *params, const char* templateContent) {
            Logger::getInstance()->info("%s request payload: %s", __func__, params);

            bool passed = checkCredentials();

            if (passed) {
                    char* payload;
                    char token[MAX_TOKEN_LENGTH + 1] = "";
                    const char* success = Util::boolToStr(passed);
                    unsigned int payloadLength = strlen(templateContent) + MAX_TOKEN_LENGTH + strlen(success);
                    payload = new char[payloadLength + 1];

                    Util::generateToken(token, MAX_TOKEN_LENGTH);
                    sprintf(payload, templateContent, token, success);
                    payload[payloadLength] = 0;

                    return Result(payload);
            }

            return Result(defaultBadCredentialsTemplate);
        }
    }
}