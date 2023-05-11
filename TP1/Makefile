CXX = gcc
CXXFLAGS = -g -Wall
MAKE = make

OBJ_DIR = ./obj
SRC_DIR = ./src
INCLUDE_DIR = ./include

TARGET = ./tp01
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
INCLUDE_FILES = $(wildcard $(INCLUDE_DIR)/*.h)

all : main

main : $(TARGET)

$(TARGET) : $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INCLUDE_FILES)
	$(CXX) $(CXXFLAGS) -I $(INCLUDE_DIR) -c $< -o $@

clean:
	rm $(OBJ_FILES) $(TARGET)