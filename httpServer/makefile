RED   = '\033[0;31m'
GREEN = '\033[0;32m'
NC    = '\033[0m'

CXXFLAGS = -O3 -ggdb -m64 -std=c++11 -Wall
LDFLAGS  = -m64
RM = rm -rf

OBJECTS_DIR = obj
BINARIES_DIR = bin
TARGET = server


OBJS = main.o \
Util.o \
Logger.o \
InternalDirectory.o \
filesHandler.o \
Filename.o \
FileAssembler.o \
FileAction.o \
file.o \
DisplayMessages.o \
Directory.o \
Model.o \
ModelHandler.o \
Result.o \
Config.o \
Scheduler.o \
Server.o \
User.o \
ControllerHandler.o \
ControllerPair.o \
Pair.o \
Configuration.o \
GetRequest.o \
HttpRequestHandler.o \
PostRequest.o \
Request.o

OBJ_FILES = $(addprefix $(OBJECTS_DIR)/, $(OBJS))

.PHONY: all clean initialize clean_objects
.PRECIOUS: $(BINARIES_DIR)/$(TARGET) $(OBJ_FILES)

#Building binaries
##################
all: initialize $(BINARIES_DIR)/$(TARGET)

$(BINARIES_DIR)/$(TARGET): $(OBJ_FILES)
	@echo -e $(GREEN)Building binary $@...$(NC)
	$(CXX) $^ -o $@ $(LDFLAGS)


#Compiling cpp files
####################
$(OBJECTS_DIR)/%.o: %.cpp
	@echo -e $(GREEN)Compiling $<$(NC)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(OBJECTS_DIR)/%.o: libraries/%.cpp
	@echo -e $(GREEN)Compiling $<$(NC)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(OBJECTS_DIR)/%.o: libraries/model/%.cpp
	@echo -e $(GREEN)Compiling $<$(NC)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(OBJECTS_DIR)/%.o: libraries/model/item/%.cpp
	@echo -e $(GREEN)Compiling $<$(NC)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(OBJECTS_DIR)/%.o: libraries/controller/%.cpp
	@echo -e $(GREEN)Compiling $<$(NC)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(OBJECTS_DIR)/%.o: libraries/network/%.cpp
	@echo -e $(GREEN)Compiling $<$(NC)
	$(CXX) -c $< -o $@ $(CXXFLAGS)


#Cleaning all
clean:
	@echo  -e $(RED)Removing objs and binaries...$(NC)
	$(RM) $(OBJECTS_DIR)/*.o $(BINARIES_DIR)/$(TARGET)

#Creating necesary directories
initialize:
	@echo -e $(GREEN)Creating directories...$(NC)
	mkdir -p $(OBJECTS_DIR)
	mkdir -p $(BINARIES_DIR)

#Cleaning objects only
cleanobj:
	@echo -e $(RED)Removing objs...$(NC)
	$(RM) $(OBJECTS_DIR)/*.o