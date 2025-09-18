# Compiler and flags
CC = gcc
CFLAGS = -Wall -std=c11

#Input file
INPUT = input.txt
# Source file
SRCS = lab3.c
# Output
TARGET = lab3.out

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)


convert: $(INPUT)
	dos2unix $(INPUT)

# Rule to run the program
run: $(TARGET)
	./$(TARGET) $(INPUT)

# Rule to clean generated files
clean:
	rm -f $(TARGET)
