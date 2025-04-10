CXX := g++
SRC := main.cpp debug.cpp emulator.cpp
OUT := main

CXXFLAGS := -std=c++23 -Wall -Wextra -Werror
LDFLAGS := $(shell sdl2-config --libs)
CPPFLAGS := $(shell sdl2-config --cflags)

.PHONY: all compile run clean

all: compile

compile:
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $(OUT) $(SRC) $(LDFLAGS)

run: compile
	./$(OUT)

clean:
	rm -f $(OUT) run.log
