CXX = g++
CXXFLAGS = -std=c++17 -Iheaders

SRC_DIR = src
HEADER_DIR = headers
OBJ_DIR = obj
BIN_DIR = bin

SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/vm.cpp $(SRC_DIR)/vm_exception_handling.cpp
OBJS = $(OBJ_DIR)/main.o $(OBJ_DIR)/vm.o
TARGET = $(BIN_DIR)/vm

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(HEADER_DIR)/Bytecode.hpp $(HEADER_DIR)/vm.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/vm.o: $(SRC_DIR)/vm.cpp $(HEADER_DIR)/vm.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
