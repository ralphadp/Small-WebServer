/*
 * PostRequest.cpp
 *
 *  Created on: Mar 24, 2019
 *      Author: root
 */

#include "PostRequest.h"

namespace Network {

    namespace Verbs {

        PostRequest::PostRequest(
                File *file,
                Configuration *config,
                Controller::ControllerHandler *controller
        ) : Request(file, config, controller) {
            strcpy(VERB, "POST");
        }

        PostRequest::~PostRequest() {

        }

        bool PostRequest::parseContent(const char *line) {

            if (!line) {
                return false;
            }

            char content[strlen(line)];
            strcpy(content, line);

            if (m_bag.getContents()) {
                //The message was already read
                return false;
            }

            const char *contentType = headers["content-type:"].value();
            if (!m_bag.getContentLength()) {
                m_bag.setMessageLength(atoi(headers["Content-Length:"].value()));
            }

            if (strcmp(contentType, "application/json") == 0
                || strcmp(contentType, "application/x-www-form-urlencoded") == 0) {

                m_bag.setContents(content);

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

                if (strlen(bufferContent) >= m_bag.getContentLength()) {
                    m_bag.setContents(bufferContent);
                }

                return true;
            }

            Logger::getInstance()->warning("Cannot parse unknown content-type: %s", contentType);

            return false;
        }

        void PostRequest::prepare(char *message) {

            if (!message) {
                Logger::getInstance()->warning("No message to process.");

                return;
            }

            Logger::getInstance()->info("POST message:\n%s", message);

            postLine = strtok(message, "\n\r");

            while (postLine) {
                //Logger::getInstance()->info("[%d] %s", (int)strlen(postLine), postLine);

                if (parsePath(postLine)) {

                    if (m_bag.hasQuery()) {
                        m_bag.removeQueryFromUrl();
                    }

                } else if (parseHeader(postLine)) {

                } else if (parseContent(postLine)) {

                }

                postLine = strtok(postLine + strlen(postLine) + 1, "\n\r");
            }
        }

        void PostRequest::process() {

            Model::Result result;

            if (!m_bag.getContents()) {
                Logger::getInstance()->error("The content is empty, cannot be processed in the Model");
                result = Model::Result("{\"success\":false,\"message\":\"Server error 101\"}", false);
            } else {
                result = pController->deliverProcessing(m_bag);
            }

            sprintf(length, "%ld", (long) result.getLength());

            //create response header
            strcpy(sent, "HTTP/1.1 200 OK\n");
            strcat(sent, "Server: httpd 0.3.1\n");
            strcat(sent, "Content-Length: ");
            strcat(sent, length);
            strcat(sent, "\nConnection: close\n");
            strcat(sent, "Content-Type: application/json;charset=");
            strcat(sent, pConfig->config("CHARSET"));
            strcat(sent, "\n\n");
            Logger::getInstance()->info("Deliver header:\n%s", sent);
            pfile->write(sent);

            //create response payload
            strcpy(sent, result.getPayload());
            //Note.- The header and the payload are sent separately
            Logger::getInstance()->info("Deliver payload:\n%s", sent);
            pfile->write(sent);

            //close the new_fd Copy
            pfile->closeFD();
        }

    } /* namespace Verbs */

} /* namespace network */
