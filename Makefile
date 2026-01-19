# Directories
SRC = src/
OBJ = obj/
TEST = test/

# Complier
CXX = g++

# Flags for the complier
CXXFLAGS = -Wall -g

# Target executable
TARGET = $(SRC)main

# Deletes target
TARGET_DEL = $(SRC)main.exe

# Target test executable
TARGET_TEST = $(TEST)test

# Sources files
SRCS = $(wildcard $(SRC)*.cpp) # wildcard function finds all .cpp files in src directory

# Object files
OBJS = $(patsubst $(SRC)%.cpp, $(OBJ)%.o, $(SRCS))
# Explanation of above line:
# 	$(pathsubst <pattern>,<replacement>,<text>)
# 	pathsubst = pattern substitution
# 	Within <text>, it will replace anything matching <pattern> with <replacement>
# 	It transforms a list of .cpp files in src/ into a list of .o files in obj/

# Test source files
TEST_SRCS = $(wildcard $(TEST)*.cpp) $(SRC)functions.cpp

# Test object files
TEST_OBJS = $(patsubst $(TEST)%.cpp, $(OBJ)%.o, $(TEST_SRCS))

# Default rule to build and run executable
all: $(TARGET) run

# Rule to link object files into the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile .cpp files into .o files
$(OBJ)%.o: $(SRC)%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to run the executable
run: $(TARGET)
	$(TARGET)

test: $(TARGET_TEST)
	$(TARGET_TEST)

$(TARGET_TEST): $(OBJS) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET_TEST) $(TEST_OBJS)

$(OBJ)%.o: $(TEST)%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean by removing generated files
clean:
	del $(TARGET_DEL) $(OBJS)