CC          = g++
BINARY      = jupiter
CCOPT       = -Wall -Werror

ifndef NDEBUG
    ECHO_DEBUG = "Compile in DEBUG mode"
    CCOPT  += -DDEBUG_JUPITER -g3
else
    ECHO_DEBUG = "Compile in RELEASE mode"
    CCOPT  += -O3
endif

ifdef WIFI
    CCOPT += -DWIFI_NETWORK
endif


#### PATHS ####
# Path to the root directory of the project
ROOT_DIR = $(realpath ..)
NETWORK_CONTROL_DIR = $(realpath $(ROOT_DIR)/../../polyphemus/Network_Control)

# Executable name and path
BUILD_DIR   = $(ROOT_DIR)/build
OBJ_DIR     = $(BUILD_DIR)/obj
BINARY_DIR  = $(BUILD_DIR)/bin
LIBS_DIR    = $(ROOT_DIR)/lib
# Header files to include
INCLUDE_DIR = $(ROOT_DIR)/include
INCLUDES    = -I$(INCLUDE_DIR) -I$(NETWORK_CONTROL_DIR)/Sources/ -I$(NETWORK_CONTROL_DIR)/Sources/Crypto
# Libraries to link
CV_LIBS     = -lopencv_core -lopencv_imgproc -lopencv_highgui
FFMPEG_LIBS = -lavcodec -lavutil -lswscale
ALLEGRO_LIBS= -lallegro -lallegro_image -lallegro_primitives -lallegro_font \
              -lallegro_ttf
OPENGL_LIBS = -lGLEW -lGL -lGLU
SECURITY_LIBS = -lgmp -lssl -lcrypto
OTHER_LIBS  = -lpthread -lm -lopenjpeg -L$(LIBS_DIR) -leasysocket
LIBS        = $(FFMPEG_LIBS) $(CV_LIBS) $(ALLEGRO_LIBS) $(OPENGL_LIBS) $(SECURITY_LIBS) $(OTHER_LIBS)

#### SOURCES ####
SRC         = $(wildcard *.cpp)
OBJ         = $(SRC:.cpp=.o)

# Transmit informations to subfolder Makefiles
export CC
export CCOPT
export OBJ_DIR
export INCLUDES
export ROOT_DIR


#### RULES ####
all: infoCompilation MakeOBJ
	@echo Compiling $(BINARY)
	$(CC) $(CCOPT) $(OBJ_DIR)/*.o -o $(BINARY_DIR)/$(BINARY) $(INCLUDES) $(LIBS)

infoCompilation:
	@echo $(ECHO_DEBUG)

%.o: %.cpp
	@echo "Compiling" $@
	@$(CC) $(CCOPT) -o $(OBJ_DIR)/$@ -c $< $(INCLUDES)

MakeOBJ: $(OBJ)
	@cd $(NETWORK_CONTROL_DIR) && $(MAKE) JUPITER_COMPILING=1
	@cp $(NETWORK_CONTROL_DIR)/Objects/*.o $(OBJ_DIR)
	@cd clients && $(MAKE)
	@cd ../
	@cd gui && $(MAKE)
	@cd ../
	@cd picture && $(MAKE)
	@cd ../

clean:
	@cd $(NETWORK_CONTROL_DIR) && make clean
	rm -f $(OBJ_DIR)/*.o $(BINARY_DIR)/$(BINARY) 

.PHONY: all clean
