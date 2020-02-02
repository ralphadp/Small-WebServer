/*
 * FileAction.h
 *
 *  Created on: Mar 9, 2019
 *      Author: ralph
 */

#ifndef SRC_LIBRARIES_FILEACTION_H_
#define SRC_LIBRARIES_FILEACTION_H_

class FileAction {
public:
	enum Type {
		WRITE = 0,
		READ
	};
	const char* types[READ + 1] = {
			"w",
			"r"
	};

private:
	Type m_type;
public:
	FileAction(Type type);
	const char* get();
};

#endif /* SRC_LIBRARIES_FILEACTION_H_ */
