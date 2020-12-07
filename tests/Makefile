CC=cc
CPP=g++
FILES=test.c
FLAGS=-g -Wextra -Wall -Wformat-security -Wno-format-truncation
EXE=test
EXAMPLEFILE=new_game.pgn
TESTFILE_01=tmp_test_01.pgn
TESTFILE_02=tmp_test_02.pgn
TESTFILE_03=tmp_test_03.pgn
TESTFILE_04=tmp_test_04.pgn
TESTFILE_05=tmp_test_05.pgn
TESTFILE_06=tmp_test_06.pgn
TESTFILE_07=tmp_test_07.pgn

all:
	$(CC) $(FLAGS) -std=c99 $(FILES) -o $(EXE)

clean:
	rm -f $(EXE) $(EXAMPLEFILE) $(TESTFILE_01) $(TESTFILE_02) $(TESTFILE_03) $(TESTFILE_04) $(TESTFILE_05) $(TESTFILE_06)

cpp:
	$(CPP) $(FLAGS) $(FILES) -o $(EXE)

check: cpp
check: all
check:
	cp files/replace_before.pgn $(TESTFILE_03)
	valgrind -q --leak-check=full --track-origins=yes ./$(EXE)
	diff $(TESTFILE_01) files/complex.pgn
	diff $(TESTFILE_02) files/equal_variations.pgn
	diff $(TESTFILE_03) files/replace_after.pgn
	diff $(TESTFILE_04) $(TESTFILE_01)
	diff $(TESTFILE_05) files/complex_less.pgn
	diff $(TESTFILE_06) files/escaped_doublequote.pgn
	diff $(TESTFILE_07) files/delete_next_moves_after.pgn
