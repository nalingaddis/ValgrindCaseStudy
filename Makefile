all: instructors students

## INSTRUCTOR REQUIREMENTS
CC = gcc
FLAGS = -c

BIN = bin
WRAPPERS = wrappers

_OBJ = v1_wrapper.o v2_wrapper.o v3_wrapper.o # edit here 
OBJ = $(patsubst %,$(BIN)/%,$(_OBJ))

instructors: $(OBJ)

$(BIN)/%.o: $(WRAPPERS)/%.c 
	$(CC) $(FLAGS) $^ -o $@

## STUDENT VIEW
### assume we provide wrapper object files for them
SRC = src
DEPS = $(SRC)/v2/*.h #edit here

_EXEC = v1 v2 v3 # edit here
EXEC = $(patsubst %,$(BIN)/%,$(_EXEC))

students: $(EXEC)

$(BIN)/%: $(SRC)/%/*.c $(DEPS) $(BIN)/%_wrapper.o
	$(CC) $^ -o $@ -pthread

## ALL
.PHONY: clean
clean:
	rm -rf bin/*