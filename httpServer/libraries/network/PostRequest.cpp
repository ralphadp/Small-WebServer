/*
 * PostRequest.cpp
 *
 *  Created on: Mar 24, 2019
 *      Author: root
 */

#include "PostRequest.h"

namespace Network {

    PostRequest::PostRequest(File* file, Configuration* config) : Request(file, config)  {
        lines = NULL;
        postLine = NULL;
        message = NULL;
        contentMessageLength = 0;
        headers = new Pair*[MAX];
        headerIndex = 0;
        strcpy(bufferContent, "");
    }

    PostRequest::~PostRequest() {
        delete [] lines;
        delete [] postLine;
        delete [] message;

        for(unsigned int index = 0; index < MAX; index++) {
            delete headers[index];
        }
        delete [] headers;
    }

    bool PostRequest::getPath(const char* line) {

        if (!line) {
            return false;
        }

        char headerLine[strlen(line)];
        strcpy(headerLine, line);

        char* pToken = strtok(headerLine, " ");
        if (strcmp(pToken, "POST") == 0) {
            pToken = strtok(NULL, " ");
            strcpy(urlPath, pToken);

            pToken = strtok(NULL, " ");
            strcpy(version, pToken);

            return true;
        }

        return false;
    }

    bool PostRequest::getHeader(const char* line) {

        if (!line) {
            return false;
        }

        char headerLine[strlen(line)];
        strcpy(headerLine, line);

        char* pToken = strtok(headerLine, " ");
        if (strstr(this->headerList, pToken)) {

            headers[headerIndex] = new Pair;
            headers[headerIndex]->setKey(pToken);
            pToken = strtok(NULL, " ");

            headers[headerIndex]->setValue(pToken);
            headerIndex++;
            headers[headerIndex] = NULL;

            return true;
        }

        return false;
    }

    const char* PostRequest::operator[](const char* indexKey)
    {
        if (!indexKey || strlen(indexKey) == 0)
        {
            Logger::getInstance()->warning("key is null");

            return NULL;
        }

        Pair** iterator = headers;
        while(*iterator != NULL) {
            if ((*iterator)->hasKey(indexKey)) {
                return (*iterator)->getValue();
            }
            iterator++;
        }

        return NULL;
    }


    bool PostRequest::getContent(const char* line) {

        if (!line) {
            return false;
        }

        char content[strlen(line)];
        strcpy(content, line);

        if (this->message) {
            //The message was already read
            return false;
        }

        const char* contentType = this->operator[]("content-type:");
        if (!contentMessageLength) {
            contentMessageLength = atoi(this->operator[]("Content-Length:"));
        }

        if (strcmp(contentType, "application/json") == 0
        || strcmp(contentType, "application/x-www-form-urlencoded") == 0) {

            this->message = new char[contentMessageLength + 1];
            strncpy(this->message, content, contentMessageLength);
            this->message[contentMessageLength] = '\0';

            return true;
        } else if (strcmp(contentType, "multipart/form-data") == 0) {
            if (strlen(bufferContent)) {
                strcat(bufferContent, "\n\r");
                strcat(bufferContent, content);
                if (strstr(content, "Content-Disposition")) {
                    strcat(bufferContent, "\n\r");
                }
            } else {
                strcpy(bufferContent, "\n\r");
                strcat(bufferContent, content);
            }

            if (strlen(bufferContent) >= contentMessageLength) {
                this->message = new char[contentMessageLength + 1];
                strncpy(this->message, bufferContent, contentMessageLength);
                this->message[contentMessageLength] = '\0';
            }

            return true;
        }

        Logger::getInstance()->warning("Cannot parse unknown content-type: %s", contentType);

        return false;
    }

    void PostRequest::prepare(char* message) {

        if (!message) {
            Logger::getInstance()->warning("No message to process.");

            return;
        }

        Logger::getInstance()->info("POST message:\n%s", message);

        postLine = strtok(message, "\n\r");

        while (postLine) {
            //Logger::getInstance()->info("[%d] %s\n\r", (int)strlen(postLine), postLine);

            if (getPath(postLine)) {

            } else if (getHeader(postLine)) {

            } else if (getContent(postLine)) {

            }

            postLine = strtok(postLine + strlen (postLine) + 1, "\n\r");
        };
    }

    void PostRequest::process() {

        const char* response = verifyMessage(this->message)?"true":"false";

        //Note.- The header and the payload are sent separately
        sprintf(payload,
                "{\n"
                "\"key\":\"%s\"\n"
                "\"result\":\"%s\"\n"
                "}"
                , "ki90kid-w3eqwq"
                , response);

        sprintf(length, "%ld", (long)strlen(payload));

        Logger::getInstance()->info("payload:%s", this->message);

        //create response header
        strcpy(sent, "HTTP/1.1 200 OK");
        strcat(sent, "\nServer: httpd 0.3.1\n");
        strcat(sent, "Content-Length: ");
        strcat(sent, length);
        strcat(sent, "\nConnection: close\nContent-Type: ");
        strcat(sent, "application/json");
        strcat(sent, ";charset=");
        strcat(sent, (*pConfig)["CHARSET"]);
        strcat(sent, "\n\n");
        printf("%s", sent);
        pfile->write(sent);

        //create response payload
        strcpy(sent, payload);
        Logger::getInstance()->info("%s", sent);

        pfile->write(sent);

        //close the new_fd Copy
        pfile->closeFD();
    }

} /* namespace network */
