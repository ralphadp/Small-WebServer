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
            result = NULL;
            hostname = NULL;
            hostnamef = NULL;
            ext = NULL;
            extf = NULL;
            postLine = NULL;

            lines = NULL;

            rangetmp = NULL;
            range = 0;
            strcpy(code, "");
        }

        GetRequest::~GetRequest() {
            delete[] lines;
            delete[] postLine;
        }

        bool GetRequest::parseQuery(const char* path) {
            char* query = strchr(const_cast<char*>(path), '?');

            if (strlen(query) <= 1) {
                return false;
            }

            query++;

            char QUERY[1024];
            strcpy(QUERY, query);

            char* pParameter = strtok(QUERY, "&");
            while(pParameter) {

                char PARAM[512];
                strcpy(PARAM, pParameter);
                char* token = strtok(PARAM, "=");
                while(token) {
                    Pair* pair = new Pair();
                    pair->setKey(token);

                    token = strtok(NULL, "=");
                    if (token) {
                        pair->setValue(token);
                        m_query.add(pair);
                    }
                }

                pParameter = strtok(NULL, "&");
            }

            return true;
        }

        void GetRequest::prepare(char *message) {

            if (!message) {
                Logger::getInstance()->warning("No message to process.");

                return;
            }

            Logger::getInstance()->info("GET message:\n%s", message);
            char *lines = strtok(message, "\n\r");

            do {
                hostname = strtok(NULL, "\n\r");
                hostnamef = strtok(hostname, " ");

                if (strcmp(hostnamef, "Range:") == 0) {
                    rangetmp = hostname;
                    strcpy(code, "206 Partial Content");
                }
            } while (strcmp(hostnamef, "Host:") != 0);

            hostnamef = strtok(NULL, " ");

            result = strtok(lines, " ");
            result = strtok(NULL, " ");

            if (strcmp(code, "206 Partial Content") == 0) {
                rangetmp = strtok(strpbrk(rangetmp, "="), "=-");
                range = atoi(rangetmp);
            }

            if (hasQuery(result)) {
                parseQuery(result);
                depreciateQuery(result);
            }

            strcpy(file, result);
            Directory dir(result);
            Filename fileNotFound("404.html");

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
                        strcat(file, fileNotFound.get());
                        dir.set("/");

                        FileAssembler assembler(&dir, &fileNotFound);
                        pfile->setFileAssembler(&assembler);
                        pfile->open(FileAction::Type::READ);
                        strcpy(code, "404 Not Found");
                    }
                } else {
                    strcpy(code, "301 Moved Permanently");
                    strcpy(moved, "Location: http://");
                    strcat(moved, hostnamef);
                    strcat(moved, result);
                    strcat(moved, "/");
                }
            } else {
                //get file descriptor for founded file
                if (pfile->open(result, FileAction::Type::READ)) {
                    if (strlen(code) < 1) {
                        strcpy(code, "200 OK");
                    }
                } else {

                    strcpy(file, fileNotFound.get());
                    dir.set("/");

                    FileAssembler assembler(&dir, &fileNotFound);
                    pfile->setFileAssembler(&assembler);
                    pfile->open(FileAction::Type::READ);
                    strcpy(code, "404 Not Found");
                }
            }
        }

        void GetRequest::process() {

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
            strcat(sent, (*pConfig)["CHARSET"]);
            strcat(sent, "\n\n");

            Logger::getInstance()->info("RESPONSE:\n%s", sent);

            pfile->write(sent);

            //send file contents
            pfile->readWriteChunck();

            pfile->closeFD();//close the new_fd Copy
        }

    } /* namespace Verbs */

} /* namespace network */
