BIN     := ./bin
SRC     := ./src

CC      := g++
INCLUDE := -Iinclude
CFLAGS  := -Wall -std=gnu++14 -g

GAMEDIR := src/game
GAME    := $(shell find $(GAMEDIR) -name '*.cpp')

MAIN    := $(shell find $(SRC) -name '*.cpp')

SRCS    := $(GAME) $(MAIN)
OBJS    := $(SRCS)

DEPS := $(OBJS:%.cpp=%.d)
OBJS := $(OBJS:%.cpp=%.o)

EXE     := $(BIN)/dungeon.exe

.PHONY: all run clean

all: $(EXE)

$(EXE): $(OBJS) | $(BIN)
	$(CC) $^ -o $@ 

%.o: %.cpp
	$(CC) -o $@ $(CFLAGS) $(INCLUDE) -c -MMD $<

$(BIN) $(OBJ):
	$(MKDIR) $@

run: $(EXE)
	$<

clean:
	$(RM) $(DEPS) $(OBJS) $(EXE)