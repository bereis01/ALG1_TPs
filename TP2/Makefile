CXX = g++
CXXFLAGS = -g -Wall
MAKE = make

OBJ_DIR = ./obj
SRC_DIR = ./src
INCLUDE_DIR = ./include

TARGET = ./tp02
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))
INCLUDE_FILES = $(wildcard $(INCLUDE_DIR)/*.hpp)

all : main

main : $(TARGET)

$(TARGET) : $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp $(INCLUDE_FILES)
	$(CXX) $(CXXFLAGS) -I $(INCLUDE_DIR) -c $< -o $@

clean:
	rm $(OBJ_FILES) $(TARGET)