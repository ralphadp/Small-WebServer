/*
 * Logger.cpp
 *
 *  Created on: Jan 23, 2019
 *      Author: ralph
 */

#include "Logger.h"

Logger* Logger::m_logger = NULL;

const char* Logger::RED    = "\x1B[31m";
const char* Logger::GREEN  = "\x1B[32m";
const char* Logger::YELLOW = "\x1B[33m";

Logger::ContextFields Logger::context[] = {
	[Logger::eERROR]   = {.color = Logger::RED, .name = "ERROR"},
	[Logger::eINFO]    = {.color = Logger::GREEN, .name = "INFO"},
	[Logger::eWARNING] = {.color = Logger::YELLOW, .name = "WARNING"},
};

Logger::Logger() {
}

Logger::~Logger() {
	// TODO Auto-generated destructor stub
}

Logger* Logger::getInstance() {
	if (!m_logger) {
		m_logger = new Logger();
	}

	return m_logger;
}

void Logger::info(const char* message, ...) {
	va_list arguments;
	va_start (arguments, message);
	print(eINFO, message, arguments);
	va_end (arguments);
}

void Logger::error(const char* message, ...) {
	va_list arguments;
	va_start (arguments, message);
	print(eERROR, message, arguments);
	va_end (arguments);
}

void Logger::warning(const char* message, ...) {
	va_list arguments;
	va_start (arguments, message);
	print(eWARNING, message, arguments);
	va_end (arguments);
}

int Logger::flush() {
	return fflush(stdin);
}

void Logger::print(Context contextColor, const char* message, va_list arguments) {
	const int MESSAGE_MAX = strlen(context[contextColor].color)
				+ strlen(context[contextColor].name)
				+ strlen(message)
				+ 26 + 10;
	char* formattedMessage = new char[MESSAGE_MAX];

	char datetime[32] = "";
	getTimestampExtended(datetime);

	sprintf(formattedMessage, "%s[%s][%s]: %s\n",
				context[contextColor].color,
				datetime,
				context[contextColor].name,
				message
			);
	vprintf(formattedMessage, arguments);

	delete [] formattedMessage;

}

void Logger::getTimestamp(char* currentTimestamp) {
	time_t currentTime = time(NULL);

	struct tm* localtimer = localtime(&currentTime);

	if (!localtimer) {
		sprintf(currentTimestamp, "%d", 0);
	}

	strftime(currentTimestamp, 24, "%Y-%m-%d %H:%M:%S", localtimer);
}

void Logger::getTimestampExtended(char* currentTimestamp) {
	char datetime[24] = "";
	timeval currentTime;
	gettimeofday(&currentTime, NULL);
	int milliseconds = currentTime.tv_usec / 1000;

	strftime(datetime, 24, "%Y-%m-%d %H:%M:%S", localtime(&currentTime.tv_sec));
	sprintf(currentTimestamp, "%s.%03d", datetime, milliseconds);
}