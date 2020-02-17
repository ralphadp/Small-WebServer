/*
 * Logger.h
 *
 *  Created on: Jan 23, 2019
 *      Author: ralph
 */

#ifndef LIBRARIES_LOGGER_H_
#define LIBRARIES_LOGGER_H_

#include "stdio.h"
#include "stdarg.h"
#include "string.h"
#include "time.h"
#include <sys/time.h>

class Logger {

public:
	static Logger* m_logger;
	static Logger* getInstance();
	void info(const char* message, ...);
	void error(const char* message, ...);
	void warning(const char* message, ...);

	int flush();
private:

	static const char* RED;
	static const char* GREEN;
	static const char* YELLOW;

	enum Context {
		eERROR,
		eINFO,
		eWARNING
	};

	struct ContextFields {
		const char* color;
		const char* name;
	};

	static ContextFields context[];

	void print(Context color, const char* message, __gnuc_va_list arg);
	void getTimestamp(char* time);
	void getTimestampExtended(char* currentTimestamp);

private:
	Logger();
	virtual ~Logger();
};

#endif /* LIBRARIES_LOGGER_H_ */
