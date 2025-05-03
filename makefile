# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17

# Directories
BACKEND_DIR := src/backend
ANTLR_DIR := src/antlr4
BIN_DIR := bin
OBJ_DIR := obj

# ANTLR4 runtime paths and sources
ANTLR_RUNTIME_DIR := lib/antlr4/runtime/src
ANTLR_INCDIR := $(ANTLR_RUNTIME_DIR)
ANTLR_RUNTIME_SRCS := $(shell find $(ANTLR_RUNTIME_DIR) -name "*.cpp" -not -path "*/build/*")
ANTLR_RUNTIME_OBJS := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(ANTLR_RUNTIME_SRCS))

# Source files
BACKEND_SRCS := $(wildcard $(BACKEND_DIR)/*.cpp)
ANTLR_SRCS := $(ANTLR_DIR)/ExprTree.cpp \
              $(ANTLR_DIR)/CalcLexer.cpp \
              $(ANTLR_DIR)/CalcParser.cpp

# Object files
BACKEND_OBJS := $(patsubst $(BACKEND_DIR)/%.cpp,$(OBJ_DIR)/backend/%.o,$(BACKEND_SRCS))
ANTLR_OBJS := $(patsubst $(ANTLR_DIR)/%.cpp,$(OBJ_DIR)/antlr4/%.o,$(ANTLR_SRCS))
OBJS := $(BACKEND_OBJS) $(ANTLR_OBJS) $(ANTLR_RUNTIME_OBJS)

# Include paths
INCLUDES := -I$(ANTLR_INCDIR) \
           -I$(ANTLR_RUNTIME_DIR)/atn \
           -I$(ANTLR_RUNTIME_DIR)/dfa \
           -I$(ANTLR_RUNTIME_DIR)/misc \
           -I$(ANTLR_RUNTIME_DIR)/support

# Target
TARGET := $(BIN_DIR)/test

.PHONY: all clean

all: directories $(TARGET)

docu:
	doxygen doc/doxyfile

directories:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)/backend
	@mkdir -p $(OBJ_DIR)/antlr4
	@mkdir -p $(dir $(ANTLR_RUNTIME_OBJS))

# Linking
$(TARGET): $(OBJS)
	$(CXX) $^ -o $@

# Compilation rules
$(OBJ_DIR)/backend/%.o: $(BACKEND_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/antlr4/%.o: $(ANTLR_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/lib/antlr4/runtime/src/%.o: $(ANTLR_RUNTIME_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(TARGET)
	rm -rf doc/html