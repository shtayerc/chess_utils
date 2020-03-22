CC=cc
CPP=g++
FILES=test.c
FLAGS=-g -std=c99 -Wextra -Wall
EXE=test
TESTFILE=tmp_test.pgn

all:
	$(CC) $(FLAGS) $(FILES) -o $(EXE)

clean:
	rm -f $(EXE) $(TESTFILE)

cpp:
	$(CPP) -Wextra -Wall $(FILES) -o $(EXE)

check: cpp
check: all
check:
	valgrind -q --leak-check=full --track-origins=yes ./$(EXE)
	diff $(TESTFILE) files/complex.pgn
