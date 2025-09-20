# Makefile
# Compiler and flags
CC = gcc
CFLAGS = -Wall -std=c11

# Output
TARGETS = pro1.out pro2.out pro3.out pro4.out

all: $(TARGETS)

pro1: project1.c
	$(CC) $(CFLAGS) -o $@.out $<

pro2: project2.c
	$(CC) $(CFLAGS) -o $@.out $<

pro3: project3.c
	$(CC) $(CFLAGS) -o $@.out $<

pro4: project4.c
	$(CC) $(CFLAGS) -o $@.out $<

# Run targets
run1: pro1
	./pro1.out

run2: pro2
	./pro2.out

run3: pro3
	./pro3.out

run4: pro4
	./pro4.out

clean:
	rm -f $(TARGETS)
