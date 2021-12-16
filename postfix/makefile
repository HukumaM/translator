CXX				= g++
CXXFLAGS		= -Wall -Wextra -ggdb -O0 -std=c++17 -I./include/

BIN_DIR     	= ./bin/
BUILD_DIR		= ./build/
SOURCE_DIR  	= ./source/

EXECUTABLE  	:= postfix_translator

SOURCES			= $(wildcard $(SOURCE_DIR)*.cpp)

SUBSTITUTIONS 	:= $(SOURCES)
SUBSTITUTIONS 	:= $(subst $(SOURCE_DIR), $(BUILD_DIR), $(SUBSTITUTIONS))

OBJECTS		   	= $(SUBSTITUTIONS:.cpp=.o)
DEPENDENCIES	= $(SUBSTITUTIONS:.cpp=.d)

include $(DEPENDENCIES)

.PHONY:	all
all: $(OBJECTS)
	@if [ ! -d $(BIN_DIR) ]; then \
		echo "Сreating a directory for storing the translator executable file."; \
		mkdir -p $(BIN_DIR); \
	fi
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(BIN_DIR)$(EXECUTABLE)

$(BUILD_DIR)%.o: $(SOURCE_DIR)%.cpp
	$(CXX) $(CXXFLAGS) $< -c -o $@

$(BUILD_DIR)%.d: $(SOURCE_DIR)%.cpp
	@if [ ! -d $(BUILD_DIR) ]; then \
		echo "Сreating a directory for storing object files."; \
		mkdir -p $(BUILD_DIR); \
	fi
	@echo "Collecting dependencies for $<: $@"
	$(CXX) -E $(CXXFLAGS) $< -MM -MT $(@:.d=.o) > $@

.PHONY:	clean
clean:
	rm -f $(BIN_DIR)$(EXECUTABLE) $(OBJECTS) $(DEPENDENCIES)