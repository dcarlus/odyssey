CC          = gcc
BINARY      = polyphemus
CCOPTS      = -fPIC -ftree-vectorize -pipe -Wall -Werror

ifndef NDEBUG
    ECHO_DEBUG = "Compile in DEBUG mode"
    CCOPTS += -DDEBUG -g3
else
    ECHO_DEBUG = "Compile in RELEASE mode"
    CCOPTS += -O3
endif

CCOPTS      += -DSTANDALONE -D__STDC_CONSTANT_MACROS -D__STDC_LIMIT_MACROS \
              -DTARGET_POSIX -D_LINUX -DPIC -D_REENTRANT -D_LARGEFILE64_SOURCE \
              -D_FILE_OFFSET_BITS=64 -U_FORTIFY_SOURCE -DHAVE_LIBOPENMAX=2 \
              -DOMX -DOMX_SKIP64BIT -ftree-vectorize -pipe -DUSE_EXTERNAL_OMX \
              -DHAVE_LIBBCM_HOST -DUSE_EXTERNAL_LIBBCM_HOST -DUSE_VCHIQ_ARM


#### PATHS ####
# Path to the root directory of the project
ROOT_DIR = $(realpath ..)

# Executable name and path
BUILD_DIR = $(ROOT_DIR)/build
OBJ_DIR = $(BUILD_DIR)/obj
BINARY_DIR = $(BUILD_DIR)/bin
# Header files to include
INCLUDE_DIR = $(ROOT_DIR)/include
INCLUDES    = -I/opt/vc/include -I/opt/vc/include/interface/vcos/pthreads -I/opt/vc/include/interface/vmcs_host/linux
# Libraries to link
LIBS        = -pthread -L/opt/vc/lib -lopenmaxil

#### SOURCES ####
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

# Transmit informations to subfolder Makefiles
export CC
export CCOPTS
export OBJ_DIR
export INCLUDES
export ROOT_DIR


#### RULES ####
all: infoCompilation MakeOBJ
	@echo Compiling $(BINARY)
	$(CC) $(CCOPTS) $(INCLUDES) $(LIBS) $(OBJ_DIR)/*.o -o $(BINARY_DIR)/$(BINARY)

infoCompilation:
	@echo $(ECHO_DEBUG)

%.o: %.c
	@echo "Compiling" $@
	@$(CC) $(CCOPT) -o $(OBJ_DIR)/$@ -c $< $(INCLUDES)

MakeOBJ: $(OBJ)
	@cd structs && $(MAKE)
	@cd ../

clean:
	rm -f $(OBJ_DIR)/*.o $(BINARY_DIR)/$(BINARY) 

.PHONY: all clean
