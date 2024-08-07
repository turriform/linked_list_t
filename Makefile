CC:=gcc
FLAGS:= -std=c17 -Wall -Wextra -Wpedantic -g 

INCLUDE:= -I./include

C_SRC:= $(wildcard ./src/*.c ./src/*/*.c)
TARGET:=prog

all:
	$(CC) $(FLAGS) $(C_SRC) $(INCLUDE) -o ./bin/$(TARGET) && ./bin/$(TARGET)