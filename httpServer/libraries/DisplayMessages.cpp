/*
 * DisplayMessages.cpp
 *
 *  Created on: Mar 18, 2019
 *      Author: ralph
 */

#include "DisplayMessages.h"

namespace Libraries {

DisplayMessages::DisplayMessages() {
	// TODO Auto-generated constructor stub
}

DisplayMessages::~DisplayMessages() {
	// TODO Auto-generated destructor stub
}

void DisplayMessages::initialDisplay() {
	Logger::getInstance()->info("");
	Logger::getInstance()->info("**********************");
	Logger::getInstance()->info("*                    *");
	Logger::getInstance()->info("*   Version: 0.1.4   *");
	Logger::getInstance()->info("*   Copyright 2018   *");
	Logger::getInstance()->info("*                    *");
	Logger::getInstance()->info("**********************");
	Logger::getInstance()->info("");
}

} /* namespace Libraries */
