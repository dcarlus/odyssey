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
LIB_NAME= libeasysocket

all: dynamic static

dynamic:
	$(CC) $(CCOPTS) $(SRC) -o $(BIN_DIR)/$(LIB_NAME).so $(LIBS)

static:
	$(AR) rs $(BIN_DIR)/$(LIB_NAME).a $(SRC)

clean:
	rm $(BIN_DIR)/$(LIB_NAME).so
	rm $(BIN_DIR)/$(LIB_NAME).a
