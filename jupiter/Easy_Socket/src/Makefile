CC = g++
CCOPTS = -fPIC -shared -std=c++0x -O3

COMM_DIR = comm
SOCKET_DIR = $(COMM_DIR)/sockets
TOOLS_DIR = tools

COMM_SRC = $(COMM_DIR)/Client.cpp $(COMM_DIR)/Server.cpp $(SOCKET_DIR)/InternetSocket.cpp
TOOLS_SRC = $(TOOLS_DIR)/Logger.cpp
SRC = $(COMM_SRC) $(TOOLS_SRC)
LIBS = -lpthread

BIN_DIR = ../build
PROG = libeasysocket.so
OUTPUT = $(BIN_DIR)/$(PROG)

all:
	$(CC) $(CCOPTS) $(SRC) -o $(OUTPUT) $(LIBS) 
