SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all: $(OBJ)
	@cd handlers && $(MAKE)
	@cd ../

%.o: %.c
	@echo "Compiling" $@
	@$(CC) $(CCOPT) -o $(OBJ_DIR)/$@ -c $< $(INCLUDES) 
