# folders
INCLUDE = include
BIN		= bin
SRC		= src
OBJ		= obj

# compiler setup
CC		= gcc
CFLAGS	= -O3 -DNDEBUG -std=c11
LDFLAGS	= -lm

# files
SRCS    = $(wildcard $(SRC)/*.c)
OBJS	= $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
TARGET	= $(BIN)/sorts

all:$(TARGET)

$(TARGET): $(OBJS)
	mkdir -p $(BIN)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(OBJ)/%.o: $(SRC)/%.c
	mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDE)

clean:
	rm -f $(OBJ)/* $(BIN)/*
	rm -rf bin obj
