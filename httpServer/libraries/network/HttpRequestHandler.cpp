/*
 * HttpRequestHandler.cpp
 *
 *  Created on: Feb 17, 2019
 *      Author: ralph
 */

#include "HttpRequestHandler.h"

namespace Network {

HttpRequestHandler::HttpRequestHandler(
        FilesHandler* fileHandler,
        Controller::ControllerHandler* controller
    ) {

	this->fileHandler = fileHandler;
	this->controller = controller;
	pfile = new File(NULL);
	request = NULL;

	sockfd = 0;
	new_fd = 0;
	sin_size = 0;
	optionValue = SOL_SOCKET;
}

HttpRequestHandler::~HttpRequestHandler() {
	if (pfile) {
		delete pfile;
	}

	clean();
}

void HttpRequestHandler::create() {

	sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if (sockfd == SOCKET_ERROR) {
		Logger::getInstance()->error("Cannot create socket.");
		exit(1);
	}

	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optionValue, sizeof(int)) == -1) {
		Logger::getInstance()->error("Cannot set options for socket.");
		exit(1);
	}

	m_address.sin_family      = AF_INET;
	m_address.sin_port        = htons(Network::Configuration::get()->getPort());
	m_address.sin_addr.s_addr = INADDR_ANY;

	memset(&(m_address.sin_zero), '\0', 8);
}

bool HttpRequestHandler::isAddressFine() {
	return
		m_address.sin_family != PF_UNSPEC &&
		m_address.sin_port != 0 &&
		m_address.sin_addr.s_addr != INADDR_NONE
	;
}

void HttpRequestHandler::bind() {
	if (!isAddressFine() || sockfd == 0) {
		Logger::getInstance()->error("Need to initialized socket and address.");
		exit(1);
	}

	if (::bind(sockfd, (struct sockaddr *)&m_address, sizeof(struct sockaddr)) == -1) {
		Logger::getInstance()->error("Cannot bind.");
		exit(1);
	}

    Network::Configuration::get()->dropPrivileges();

	if (::listen(sockfd, BACKLOG) == -1) {
		Logger::getInstance()->error("Cannot Listen.");
		exit(1);
	}

	sa.sa_handler = HttpRequestHandler::sigchld_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;

	if (sigaction(SIGCHLD, &sa, NULL) == -1) {
		Logger::getInstance()->error("Error at signal action");
		exit(1);
	}
}

void HttpRequestHandler::sigchld_handler(int s)
{
    //wait for zombie-children if they exist
    while(waitpid(-1, NULL, WNOHANG) > 0);
}

bool HttpRequestHandler::isGet(const char* type) {
    return strcmp(type, "GET") == 0;
}

bool HttpRequestHandler::isPost(const char* type) {
    return strcmp(type, "POST") == 0;
}

bool HttpRequestHandler::isPut(const char* type) {
    return strcmp(type, "PUT") == 0;
}

bool HttpRequestHandler::isDelete(const char* type) {
    return strcmp(type, "DELETE") == 0;
}

Network::Request* HttpRequestHandler::buildRequest(char* message) {
	if (!message || strlen(message) == 0) {
		Logger::getInstance()->warning("Remote Message:'%s'. No message to verify the verb or type", message);

		return NULL;
	}

    char messageCopy[3000];
    strcpy(messageCopy, message);

    char* requestType = strtok(messageCopy, " ");

	if (isGet(requestType)) {
		return new Network::Verbs::GetRequest(pfile, controller);
	} else if (isPost(requestType)) {
		return new Network::Verbs::PostRequest(pfile, controller);
	} else if (isPut(requestType)) {
		//return new network::PutRequest(pfile);//TODO: need to implement
	} else if (isDelete(requestType)) {
		//return new network::DeleteRequest(pfile); //TODO: need to implement
	}
	//OPTIONS
	//HEAD
	//TRACE
	//CONNECT

    Logger::getInstance()->error("Unknown request: %s", requestType);

	return NULL; //TODO: change to a generic request handler
}

void HttpRequestHandler::clean() {
	if (request) {
		delete request;
		request = NULL;
	}

    delete [] m_message;
}

bool HttpRequestHandler::readRemoteMessage() {
    m_message = new char[MESSAGE_LENGTH + 1]();

    if (!pfile->read(m_message, MESSAGE_LENGTH)) {
        Logger::getInstance()->error("Receive remote message with error");

        return false;
    }

    m_message[MESSAGE_LENGTH] = 0;

    return true;
}

void HttpRequestHandler::listen() {
	Logger::getInstance()->info("Starting to listen in Port: %d", Network::Configuration::get()->getPort());

	while(true) {
		sin_size = sizeof(struct sockaddr_in);
		if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1) {
			Logger::getInstance()->error("Cannot accept remote stream input");
			continue;
		}
		pfile->setFileDescriptor(new_fd);

		if (!fork()) {
			/*child process*/
			close(sockfd); //close the sockfd Copy

			if (readRemoteMessage()) {
				request = buildRequest(m_message);
				if (request) {
					request->prepare(m_message);
					request->process();
				}
			}
            clean();
			exit(0);
		} /*child process end*/
		close(new_fd); //close the new_fd
	} /*while end*/
}

} /* namespace Network */
