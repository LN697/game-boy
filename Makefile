CXX := g++
OUT := build/main

SRC_DIR := src
INC_DIR := incl
SRC := $(SRC_DIR)/main.cpp $(SRC_DIR)/debug.cpp $(SRC_DIR)/emulator.cpp

CXXFLAGS := -std=c++23 -Wall -Wextra -Werror
CPPFLAGS := -I$(INC_DIR) $(shell sdl2-config --cflags)
LDFLAGS := $(shell sdl2-config --libs)

.PHONY: all compile run clean

all: compile

compile:
	@mkdir -p build
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $(OUT) $(SRC) $(LDFLAGS)

run: compile
	./$(OUT) rom/Pokémon\ Red\ Version.gb > logs/run.log

clean:
	rm -f $(OUT) logs/run.log