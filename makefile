CC = gcc
CFLAGS = -std=gnu17 -Wall -Werror -Wextra -Wpedantic

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
OUT = pal

.PHONY: all clean delete help

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	$(RM) $(OBJ)

delete: clean
	$(RM) $(OUT)

help:
	@echo "usage: make [targets]"
	@echo "\ttargets:"
	@echo "\t\tall: build the program"
	@echo "\t\tclean: remove object files"
	@echo "\t\tdelete: remove object files and the program"
	@echo "\t\thelp: display this usage message"