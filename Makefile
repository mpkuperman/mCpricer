CC = clang
CFLAGS = -Wall -Wextra
LDFLAGS = -lm
DEBUG_FLAGS = -g -DDEBUG
RELEASE_FLAGS = -O2

TARGET = main

SRC = main.c
OBJ = $(SRC:.c=.o)

.PHONY: all clean debug release

all: release

debug: CFLAGS += $(DEBUG_FLAGS)
debug: clean $(TARGET)

release: CFLAGS += $(RELEASE_FLAGS)
release: clean $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(TARGET)
