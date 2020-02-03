/*
 * file.cpp
 *
 *  Created on: Jan 02, 2019
 *      Author: ralph
 */

#include "file.h"

File::File(FileAssembler* assembler) {
	m_assembler = assembler;

	m_file_reference = NULL;
	m_file_descriptor_reference = 0;

	buffer_counter = 0;
	buffer_chunks = 0;
	buffer = NULL;

	readBytesCount = 0;
}

File::~File() {
	if (m_file_reference != NULL) {
		fclose(m_file_reference);
	}
	m_file_reference = NULL;

	free(buffer);
}

void File::setFileAssembler(FileAssembler* assembler) {
	m_assembler = assembler;
}

void File::setFileDescriptor(int fileDescriptor) {
	m_file_descriptor_reference = fileDescriptor;
}

FILE* File::open(FileAction type) {

	if (!m_assembler) {

		return NULL;
	}

	char* fileReference = new char[m_assembler->size()];
	m_assembler->assemble(fileReference);

	m_file_reference = fopen(fileReference, type.get());

	if (m_file_reference == NULL) {
		Logger::getInstance()->error("'%s' cannot be opened", fileReference);
		delete [] fileReference;

		return NULL;
	}
	delete [] fileReference;

	return m_file_reference;
}

FILE* File::open(const char* completeFilename, FileAction type) {
    if (!completeFilename) {

        return NULL;
    }

    m_file_reference = fopen(completeFilename, type.get());

    if (m_file_reference == NULL) {
        Logger::getInstance()->error("Filename '%s' cannot be opened. %s", completeFilename, strerror(errno));
        char cwd[PATH_MAX];
        getcwd(cwd, sizeof(cwd));
        Logger::getInstance()->warning("Current path %s", cwd);

        return NULL;
    }

    return m_file_reference;
}

long File::size() {

	fseek (m_file_reference, 0 , SEEK_END);
	long filesize = ftell(m_file_reference);
	rewind (m_file_reference);

	return filesize;
}

char* File::getStart() {
	return &start[0];
}

char* File::getEnd() {
	return &end[0];
}

FileAssembler* File::getFileAssembler() {
	return m_assembler;
}

void File::prepareChunkReading(long range) {

	if (!m_file_reference) {
        Logger::getInstance()->error("Cannot prepare chunk reading for unopened file ..");
		return;
	}

	long fileSize = this->size();

	if (range > 0) {
		sprintf(end, "%ld", fileSize);
		fileSize = fileSize - range;
		sprintf(start, "%ld", range);
		fseek (m_file_reference, range, SEEK_SET);
	}

	buffer_chunks = fileSize / SIZE;

	if (fileSize % SIZE > 0) {
		buffer_chunks++;
	}

	sprintf(contentLength, "%ld", fileSize);

	this->buffer_counter = 0;
	this->buffer = (char*) malloc(sizeof(char) * SIZE);
}

char* File::getBuffer() {
	return this->buffer;
}

const char* File::GetContentLength() {
    return contentLength;
}

/**
 * Write the input_data stream in the file referenced by m_file_descriptor
 */
unsigned int File::write(char* input_data) {
	if (!m_file_descriptor_reference) {

		return 0;
	}

	if (!input_data) {

		return 0;
	}

	return ::write(m_file_descriptor_reference, input_data, strlen(input_data));

}

unsigned int File::writeBuffer() {
	if (!m_file_descriptor_reference) {

		return 0;
	}

	if (!buffer) {

		return 0;
	}

	return ::write(m_file_descriptor_reference, buffer, SIZE);

}

/**
 * Read a big chuck
 */
unsigned int File::read_chunk() {
	if (!m_file_reference) {

		return 0;
	}

	unsigned int countRead = fread (this->buffer, 1, SIZE, m_file_reference);
	this->buffer_counter++;

	//WORKAROUND: This is necessary if called once
	this->buffer[countRead] = '\0';

	readBytesCount = countRead;

	return countRead;
}

unsigned int File::read(unsigned int size) {
    if (!m_file_reference) {

        return 0;
    }

    this->buffer = new char[size];

    unsigned int countRead = fread (this->buffer, sizeof(char), size, m_file_reference);

    this->buffer[countRead] = '\0';
    readBytesCount = countRead;

    return countRead;
}

bool File::read(char* output_data, unsigned int size_data) {
	if (!m_file_descriptor_reference) {

		return false;
	}

	readBytesCount = ::read(m_file_descriptor_reference, output_data, size_data);

	return readBytesCount != -1;
}

long int File::lastReadCount() {
	return readBytesCount;
}

/**
 * Read until end of lines
 */
unsigned int File::readContents(char* output_data) {
	const int INTERNAL_SIZE = 64;
	char internalBuffer[INTERNAL_SIZE];
	unsigned int length = 0;

	if (!m_file_reference) {

		return 0;
	}

	strcpy(output_data, "");
	while (fgets(internalBuffer, INTERNAL_SIZE, m_file_reference) != NULL) {
		strcat(output_data, internalBuffer);
		length += strlen(internalBuffer);
	}
	output_data[length] = '\0';

	readBytesCount = length;

	return length;
}

void File::close() {
	if (m_file_reference == NULL) {

		return;
	}

	fclose(m_file_reference);
	m_file_reference = NULL;
}

void File::closeFD() {
	if (!m_file_descriptor_reference) {

		return;
	}

	::close(m_file_descriptor_reference);
	m_file_descriptor_reference = 0;
}

void File::readChunck() {
	while (this->buffer_counter < buffer_chunks) {
		read_chunk();
	}
}

void File::readWriteChunck() {
	while (this->buffer_counter < buffer_chunks) {
		read_chunk();
		writeBuffer();
	}
}
