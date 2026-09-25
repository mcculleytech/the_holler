# TODO
# - [ ] add windows build
# - [ ] add linux build

# project location vars
SRC_DIR := src
BIN_DIR := bin
TARGET := $(BIN_DIR)/the_holler

# compile vars
CC 			:= cc
CFLAGS 	:= $(shell pkg-config --cflags raylib)
LDLIBS	:= $(shell pkg-config --libs raylib)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC_DIR)/main.c | $(BIN_DIR)
	$(CC) $(CFLAGS) $< -o $@ $(LDLIBS)

$(BIN_DIR):
	mkdir -p $@

clean:
	 rm -f $(BIN_DIR)/*
