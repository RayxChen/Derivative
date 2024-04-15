# Compiler settings
CXX = g++
CXXFLAGS = -IHeaders -std=c++11 -Wall
LDFLAGS = 

# Directories
SRC_DIR = Source
OBJ_DIR = Objects
DEP_DIR = $(OBJ_DIR)/deps

# Source files
LIB_SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
MAIN_SOURCE = main.cpp

# Object files
LIB_OBJECTS = $(LIB_SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
MAIN_OBJECT = $(OBJ_DIR)/main.o

# Executable
EXECUTABLE = OptionPrice

# Default target
all: $(EXECUTABLE)

# Linking the executable
$(EXECUTABLE): $(MAIN_OBJECT) $(LIB_OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^

# Compiling the main source file
$(MAIN_OBJECT): $(MAIN_SOURCE)
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compiling library sources
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(DEP_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ -MMD -MP -MF $(DEP_DIR)/$*.d

# Include dependency files
-include $(LIB_SOURCES:$(SRC_DIR)/%.cpp=$(DEP_DIR)/%.d)

# Clean up build files
clean:
	rm -f $(EXECUTABLE) $(MAIN_OBJECT) $(LIB_OBJECTS)
	rm -rf $(DEP_DIR)

# Phony targets
.PHONY: all clean
