SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all: $(OBJ)
	@cd camera && $(MAKE)
	@cd ../
	@cd encoder && $(MAKE)
	@cd ../
	@cd null_sink && $(MAKE)
	@cd ../

%.o: %.c
	@echo "Compiling" $@
	@$(CC) $(CCOPT) -o $(OBJ_DIR)/$@ -c $< $(INCLUDES) 
