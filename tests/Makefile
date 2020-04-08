CC=cc
CPP=g++
FILES=test.c
FLAGS=-g -std=c99 -Wextra -Wall
EXE=test
EXAMPLEFILE=new_game.pgn
TESTFILE_01=tmp_test_01.pgn
TESTFILE_02=tmp_test_02.pgn
TESTFILE_03=tmp_test_03.pgn

all:
	$(CC) $(FLAGS) $(FILES) -o $(EXE)

clean:
	rm -f $(EXE) $(EXAMPLEFILE) $(TESTFILE_01) $(TESTFILE_02) $(TESTFILE_03)

cpp:
	$(CPP) -Wextra -Wall $(FILES) -o $(EXE)

check: cpp
check: all
check:
	cp files/replace_before.pgn $(TESTFILE_03)
	valgrind -q --leak-check=full --track-origins=yes ./$(EXE)
	diff $(TESTFILE_01) files/complex.pgn
	diff $(TESTFILE_02) files/equal_variations.pgn
	diff $(TESTFILE_03) files/replace_after.pgn
