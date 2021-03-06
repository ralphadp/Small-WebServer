/*
 * HttpRequestHandler.h
 *
 *  Created on: Feb 17, 2019
 *      Author: ralph
 */

#ifndef LIBRARIES_HTTPREQUESTHANDLER_H_
#define LIBRARIES_HTTPREQUESTHANDLER_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>

#include "Verbs/GetRequest.h"
#include "Verbs/PostRequest.h"

#include "../controller/ControllerHandler.h"
#include "Configuration.h"
#include "../filesHandler.h"
#include "../file.h"
#include "../Logger.h"

namespace Network {

class HttpRequestHandler {
	const int SOCKET_ERROR = -1;

	//Sockets stuff
	int sockfd;
	int new_fd;
	struct sockaddr_in their_addr;
	socklen_t sin_size;
	struct sigaction sa;
	int optionValue;
	struct sockaddr_in m_address;

	const int BACKLOG = 10;

	char* m_message;
	size_t MESSAGE_LENGTH = 3000;

	FilesHandler* fileHandler;
    Controller::ControllerHandler* controller;
	File* pfile;
	Network::Request* request;

public:
	HttpRequestHandler(FilesHandler* fileHandler, Controller::ControllerHandler* controller);
	virtual ~HttpRequestHandler();
	void create();
	void bind();
	void listen();
private:
    bool readRemoteMessage();
	bool isGet(const char* type);
	bool isPost(const char* type);
	bool isPut(const char* type);
	bool isDelete(const char* type);
	Network::Request* buildRequest(char* in);
	void clean();
	bool isAddressFine();
	static void sigchld_handler(int s);
};

} /* namespace Network */

#endif /* LIBRARIES_HTTPREQUESTHANDLER_H_ */
