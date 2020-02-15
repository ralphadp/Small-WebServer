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
            code = 0;
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
                    sprintf(moved, "Location: http://%s%s/", hostnamef, resultPath);
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

                    //create response header
                    strcpy(sent, "HTTP/1.1 ");
                    strcat(sent, responseCode(result.getCode()));
                    strcat(sent, "\nServer: httpd 0.3.1\n");
                    strcat(sent, "Content-Length: ");
                    strcat(sent, length);
                    strcat(sent, "\nConnection: close\n");
                    strcat(sent, "Content-Type: application/json;charset=");
                    strcat(sent, Network::Configuration::get()->config("CHARSET"));
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

                    return;
                }
            }

            if (!code) {
                Logger::getInstance()->warning("No code to check.");

                return;
            }

            if (code != 301) {
                //prepare buffer for the file requested
                pfile->prepareChunkReading(range);
            }

            if (code != 404 && code != 301) {
                strcpy(mime, getMime(file));
            } else {
                strcpy(mime, "text/html");
            }

            //create response header
            strcpy(sent, "HTTP/1.1 ");
            strcat(sent, responseCode(code));
            strcat(sent, "\nServer: httpd 0.1.1\n");

            if (code == 301) {
                strcat(sent, moved);
                strcat(sent, "\n");
            }

            strcat(sent, "Content-Length: ");
            if (code != 301) {
                strcat(sent, pfile->GetContentLength());
            } else {
                strcat(sent, "0");
            }

            if (code == 206) {
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
            strcat(sent, Network::Configuration::get()->config("CHARSET"));
            strcat(sent, "\n\n");

            Logger::getInstance()->info("RESPONSE:\n%s", sent);

            pfile->write(sent);

            //send file contents
            pfile->readWriteChunk();

            pfile->closeFD();//close the new_fd Copy
        }

    } /* namespace Verbs */

} /* namespace network */
