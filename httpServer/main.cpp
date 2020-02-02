//============================================================================
// Name        : main.cpp
// Author      : ralph
// Version     : 0.1.1
// Copyright   : asendeteufrer
// Description : Light Web server in C++, Ansi-style
//============================================================================

#include "libraries/filesHandler.h"
#include "libraries/network/Configuration.h"
#include "libraries/network/HttpRequestHandler.h"
#include "libraries/DisplayMessages.h"
#include "libraries/Logger.h"

int main(int argc, char const *argv[]) {

	Network::Configuration config;
	FilesHandler filesHandler;
	Network::HttpRequestHandler http(&config, &filesHandler);

	if (!config.read()) {
		Logger::getInstance()->error("Something is wrong with configuration's options.");
		exit(0);
	}

	http.create();
	http.bind();

	Libraries::DisplayMessages::initialDisplay();

	//start to listen in the config port.
	http.listen();

	return 0;
}
