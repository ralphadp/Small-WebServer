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
                Configuration *config,
                Controller::ControllerHandler *controller
        ) : Request(file, config, controller) {
            resultPath = NULL;

            hostnamef = NULL;
            ext = NULL;
            extf = NULL;

            rangetmp = NULL;
            range = 0;
            strcpy(code, "");
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

            char* QUERY = Util::clone(query);

            char* pParameter = strtok(QUERY, "&");
            while(pParameter) {

                char* PARAM = Util::clone(pParameter);
                char* token = strtok(PARAM, "=");

                while(token) {

                    Structure::String key(token);
                    token = strtok(NULL, "=");
                    if (token) {
                        m_query[key] = token;
                    }
                    token = strtok(NULL, "=");
                }

                delete [] PARAM;

                pParameter = strtok(pParameter + strlen(pParameter) + 1, "&");

            }

            delete [] QUERY;

            return true;
        }

        void GetRequest::setNotFound() {
            Filename fileNotFound("404.html");
            strcat(file, fileNotFound.get());
            Directory dir("/");

            FileAssembler assembler(&dir, &fileNotFound);
            pfile->setFileAssembler(&assembler);
            pfile->open(FileAction::Type::READ);
            strcpy(code, "404 Not Found");
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
                strcpy(code, "206 Partial Content");

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
                        strcpy(code, "200 OK");
                    } else {
                        //Here should be some kind of directory listing
                        setNotFound();
                    }
                } else {
                    strcpy(code, "301 Moved Permanently");
                    strcpy(moved, "Location: http://");
                    strcat(moved, hostnamef);
                    strcat(moved, resultPath);
                    strcat(moved, "/");
                }
            } else {
                //get file descriptor for founded file
                if (pfile->open(resultPath, FileAction::Type::READ)) {
                    strcpy(code, "200 OK");
                } else {
                    setNotFound();
                }
            }
        }

        void GetRequest::process() {

            if (strcmp(code, "404 Not Found") == 0) {
                Model::Result result = pController->deliverProcessing(m_bag);

                if (result.isSuccess()) {
                    sprintf(length, "%ld", (long) result.getLength());

                    //create response header
                    strcpy(sent, "HTTP/1.1 200 OK");
                    strcat(sent, "\nServer: httpd 0.3.1\n");
                    strcat(sent, "Content-Length: ");
                    strcat(sent, length);
                    strcat(sent, "\nConnection: close\nContent-Type: ");
                    strcat(sent, "application/json");
                    strcat(sent, ";charset=");
                    strcat(sent, pConfig->config("CHARSET"));
                    strcat(sent, "\n\n");
                    printf("%s", sent);
                    pfile->write(sent);

                    //create response payload
                    strcpy(sent, result.getPayload());
                    //Note.- The header and the payload are sent separately
                    Logger::getInstance()->info("Deliver payload: %s", sent);

                    pfile->write(sent);

                    //close the new_fd Copy
                    pfile->closeFD();

                    return;
                }
            }

            if (!strlen(code)) {
                Logger::getInstance()->warning("No code to check.");

                return;
            }

            if (strcmp(code, "301 Moved Permanently") != 0) {
                //prepare buffer for the file requested
                pfile->prepareChunkReading(range);
            }

            if (strcmp(code, "404 Not Found") != 0 && strcmp(code, "301 Moved Permanently") != 0) {
                ext = strtok(file, ".");
                while (ext != NULL) {
                    ext = strtok(NULL, ".");
                    if (ext != NULL) {
                        extf = ext;
                    }
                }

                /* TODO: Mapping is needed here*/
                if (strcmp(extf, "html") == 0) {
                    strcpy(mime, "text/html");
                } else if (strcmp(extf, "jpg") == 0) {
                    strcpy(mime, "image/jpeg");
                } else if (strcmp(extf, "gif") == 0) {
                    strcpy(mime, "image/gif");
                } else if (strcmp(extf, "png") == 0) {
                    strcpy(mime, "image/png");
                } else if (strcmp(extf, "css") == 0) {
                    strcpy(mime, "text/css");
                } else {
                    strcpy(mime, "application/octet-stream");
                }
            } else {
                //default mime
                strcpy(mime, "text/html");
            }

            //create response header
            strcpy(sent, "HTTP/1.1 ");
            strcat(sent, code);
            strcat(sent, "\nServer: httpd 0.1.1\n");

            if (strcmp(code, "301 Moved Permanently") == 0) {
                strcat(sent, moved);
                strcat(sent, "\n");
            }

            strcat(sent, "Content-Length: ");
            if (strcmp(code, "301 Moved Permanently") != 0) {
                strcat(sent, pfile->GetContentLength());
            } else {
                strcat(sent, "0");
            }

            if (strcmp(code, "206 Partial Content") == 0) {
                strcat(sent, "\nContent-Range: bytes ");
                strcat(sent, pfile->getStart());
                strcat(sent, "-");
                strcat(sent, pfile->getEnd());
                strcat(sent, "/");
                strcat(sent, pfile->getEnd());
            }

            strcat(sent, "\nConnection: close\nContent-Type: ");
            strcat(sent, mime);
            strcat(sent, "; charset=");
            strcat(sent, pConfig->config("CHARSET"));
            strcat(sent, "\n\n");

            Logger::getInstance()->info("RESPONSE:\n%s", sent);

            pfile->write(sent);

            //send file contents
            pfile->readWriteChunck();

            pfile->closeFD();//close the new_fd Copy
        }

    } /* namespace Verbs */

} /* namespace network */
