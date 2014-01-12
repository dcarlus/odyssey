CC          = g++
BINARY      = jupiter
CCOPTS      = -Wall -Werror

ifndef NDEBUG
    ECHO_DEBUG = "Compile in DEBUG mode"
    CCOPTS  += -DDEBUG_JUPITER -g3
else
    ECHO_DEBUG = "Compile in RELEASE mode"
    CCOPTS  += -O3
endif


#### PATHS ####
# Path to the root directory of the project
ROOT_DIR = $(realpath ..)

# Executable name and path
BUILD_DIR   = $(ROOT_DIR)/build
OBJ_DIR     = $(BUILD_DIR)/obj
BINARY_DIR  = $(BUILD_DIR)/bin
LIBS_DIR    = $(ROOT_DIR)/lib
# Header files to include
INCLUDE_DIR = $(ROOT_DIR)/include
INCLUDES    = -I$(INCLUDE_DIR)
# Libraries to link
LIBS        = -lpthread -L$(LIBS_DIR) -leasysocket

#### SOURCES ####
SRC         = $(wildcard *.cpp)
OBJ         = $(SRC:.cpp=.o)

# Transmit informations to subfolder Makefiles
export CC
export CCOPTS
export OBJ_DIR
export INCLUDES
export ROOT_DIR


#### RULES ####
all: infoCompilation MakeOBJ
	@echo Compiling $(BINARY)
	$(CC) $(CCOPTS) $(OBJ_DIR)/*.o -o $(BINARY_DIR)/$(BINARY) $(INCLUDES) $(LIBS)

infoCompilation:
	@echo $(ECHO_DEBUG)

%.o: %.cpp
	@echo "Compiling" $@
	@$(CC) $(CCOPT) -o $(OBJ_DIR)/$@ -c $< $(INCLUDES)

MakeOBJ: $(OBJ)
#	@cd structs && $(MAKE)
	@cd ../

clean:
	rm -f $(OBJ_DIR)/*.o $(BINARY_DIR)/$(BINARY) 

.PHONY: all clean
