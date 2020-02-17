/*
 * GetRequest.cpp
 *
 *  Created on: Mar 24, 2019
 *      Author: root
 */

#include "GetRequest.h"

namespace Network {

    namespace Verbs {

        GetRequest::GetRequest(
                File *file,
                Controller::ControllerHandler *controller
        ) : Request(file, controller) {
            resultPath = NULL;

            hostnamef = NULL;

            rangetmp = NULL;
            range = 0;

            strcpy(VERB, "GET");
        }

        GetRequest::~GetRequest() {
        }

        bool GetRequest::parseQuery(const char* path) {
            char* query = strchr(const_cast<char*>(path), '?');

            if (strlen(query) <= 1) {
                return false;
            }

            query++;

            char* QUERY = strdup(query);
            char* index = QUERY;
            char* ptr = strsep (&index, "&");

            while (ptr) {
                Structure::String key(strtok(ptr, "="));
                m_query[key] = strtok (NULL, "=");
                ptr = strsep (&index, "&");
            }

            free(QUERY);

            return true;
        }

        void GetRequest::setNotFound() {
            Filename fileNotFound("404.html");
            strcat(file, fileNotFound.get());
            Directory dir("/");

            FileAssembler assembler(&dir, &fileNotFound);
            pfile->setFileAssembler(&assembler);
            pfile->open(FileAction::Type::READ);
            code = 404;
        }

        void GetRequest::prepare(char *message) {

            if (!message) {
                Logger::getInstance()->warning("No message to process.");

                return;
            }

            Logger::getInstance()->info("GET message:\n%s", message);
            postLine = strtok(message, "\n\r");

            while (postLine) {
                if (parsePath(postLine)) {

                    if (m_bag.hasQuery()) {
                        if(parseQuery(m_bag.getUrlPath())) {
                            m_bag.copyQueryParams(m_query);
                        }
                        resultPath = m_bag.removeQueryFromUrl();
                    } else {
                        resultPath = const_cast<char*>(m_bag.getUrlPath());
                    }

                } else {
                    parseHeader(postLine);
                }

                postLine = strtok(postLine + strlen(postLine) + 1, "\n\r");
            }

            hostnamef = const_cast<char*>(headers["Host:"].value());

            if (headers.exist("Range:")) {
                rangetmp= const_cast<char*>(headers["Range:"].value());
                code = 206;
                rangetmp = strtok(strpbrk(rangetmp, "="), "=-");
                range = atoi(rangetmp);
            }

            strcpy(file, resultPath);
            Directory dir(resultPath);

            if (dir.exists()) {
                if (file[strlen(file) - 1] == '/') {
                    strcat(file, "index.html");
                    Filename filename(file);
                    FileAssembler assembler(&dir, &filename);
                    pfile->setFileAssembler(&assembler);

                    if (pfile->open(FileAction::Type::READ)) {
                        code = 200;
                    } else {
                        //Here should be some kind of directory listing
                        setNotFound();
                    }
                } else {
                    code = 301;
                    sprintf(movedHeaderResponse, "\nLocation: http://%s%s/", hostnamef, resultPath);
                    strcpy(file, "");
                }
            } else {
                //get file descriptor for founded file
                if (pfile->open(resultPath, FileAction::Type::READ)) {
                    code = 200;
                } else {
                    setNotFound();
                }
            }
        }

        void GetRequest::process() {

            if (code == 404) {
                Model::Result result = pController->deliverProcessing(m_bag);

                if (result.isSuccess()) {
                    sprintf(length, "%ld", (long) result.getLength());
                    code = result.getCode();

                    createResponseHeader(length, "result.json");
                    Logger::getInstance()->info("Response header:\n%s", sent);
                    pfile->write(sent);

                    //deliver response payload
                    strcpy(sent, result.getPayload());
                    //Note.- The header and the payload are sent separately
                    Logger::getInstance()->info("Response payload:\n%s", sent);
                    pfile->write(sent);
                    //close the new_fd Copy
                    pfile->closeFD();

                    return;
                }
            }

            if (code != 301) {
                //prepare buffer for the file requested
                pfile->prepareChunkReading(range);
            }

            createResponseHeader(pfile->GetContentLength(), file);
            Logger::getInstance()->info("Response header:\n%s", sent);
            pfile->write(sent);

            //send file contents
            pfile->readWriteChunk();
            //close the new_fd Copy
            pfile->closeFD();
        }

    } /* namespace Verbs */

} /* namespace network */
