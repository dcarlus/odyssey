####################################################
##                 JUPITER MAKEFILE                #
####################################################
##                                                 #
## Use the "make" command in the current directory #
## to compile the project and its dependencies.    #
##                                                 #
## The binary file is located in the               #
## Jupiter_Vision/build/bin directory.             #
####################################################
###################################################

LIB_FILES			= 
EASYSOCKET_DIR		= Easy_Socket
JUPITER_VISION_DIR 	= Jupiter_Vision

all: EasySocket JupiterVision

EasySocket:
	cd $(EASYSOCKET_DIR)/src/ && make
	cp $(EASYSOCKET_DIR)/build/libeasysocket.a $(JUPITER_VISION_DIR)/lib/
	cp $(EASYSOCKET_DIR)/build/libeasysocket.so $(JUPITER_VISION_DIR)/lib/
	cp -r $(EASYSOCKET_DIR)/include/* $(JUPITER_VISION_DIR)/include/easysocket/

JupiterVision:
	cd $(JUPITER_VISION_DIR)/src/ && make

clean:
	cd $(EASYSOCKET_DIR)/src/ && make clean
	cd $(JUPITER_VISION_DIR)/src/ && make clean
