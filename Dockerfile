# GCC support can be specified at major, minor, or micro version
# (e.g. 8, 8.2 or 8.2.0).
# See https://hub.docker.com/r/library/gcc/ for all supported GCC
# tags from Docker Hub.
# See https://docs.docker.com/samples/library/gcc/ for more on how to use this image
FROM gcc:latest

# Update to use gdb
RUN apt-get -y update
RUN apt-get -y install gdb gdbserver

# These commands copy your files into the specified directory in the image
# and set that as the working location
RUN mkdir -p /usr/src/httpServer
COPY ./httpServer /usr/src/httpServer
WORKDIR /usr/src/httpServer

# This command compiles your app using GCC, adjust for your source code
RUN g++ -std=c++11 -Wall -o server main.cpp \
./libraries/model/Model.cpp \
./libraries/model/ModelHandler.cpp \
./libraries/model/Result.cpp \
./libraries/model/item/Config.cpp \
./libraries/model/item/Scheduler.cpp \
./libraries/model/item/Server.cpp \
./libraries/model/item/User.cpp \
./libraries/controller/ControllerHandler.cpp \
./libraries/controller/ControllerPair.cpp \
./libraries/network/Pair.cpp \
./libraries/network/Configuration.cpp \
./libraries/network/GetRequest.cpp \
./libraries/network/HttpRequestHandler.cpp \
./libraries/network/PostRequest.cpp \
./libraries/network/Request.cpp \
./libraries/Directory.cpp \
./libraries/DisplayMessages.cpp \
./libraries/file.cpp \
./libraries/FileAction.cpp \
./libraries/FileAssembler.cpp \
./libraries/Filename.cpp \
./libraries/filesHandler.cpp \
./libraries/InternalDirectory.cpp \
./libraries/Logger.cpp \
./libraries/Util.cpp

# Open port to access the http service
EXPOSE 12222

# This command runs your application, comment out this line to compile only
#CMD ["./server"]

LABEL Name=c++webserver Version=0.1.1
