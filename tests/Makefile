CC=cc
CPP=g++
FILES=test.c
FLAGS=-g -std=c99 -Wextra -Wall
EXE=test
TESTFILE_01=tmp_test_01.pgn
TESTFILE_02=tmp_test_02.pgn

all:
	$(CC) $(FLAGS) $(FILES) -o $(EXE)

clean:
	rm -f $(EXE) $(TESTFILE_01) $(TESTFILE_02)

cpp:
	$(CPP) -Wextra -Wall $(FILES) -o $(EXE)

check: cpp
check: all
check:
	valgrind -q --leak-check=full --track-origins=yes ./$(EXE)
	diff $(TESTFILE_01) files/complex.pgn
	diff $(TESTFILE_02) files/equal_variations.pgn
