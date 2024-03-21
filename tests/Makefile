CC=cc
CPP=g++
FILES=test.c
FLAGS=-g -Wextra -Wall -Wformat-security -Wno-format-truncation #-Wconstant-logical-operand -Wconditional-uninitialized
EXE=test
VALGRIND=
EXAMPLEFILE=new_game.pgn
TESTFILE_01=tmp_test_01.pgn
TESTFILE_02=tmp_test_02.pgn
TESTFILE_03=tmp_test_03.pgn
TESTFILE_04=tmp_test_04.pgn
TESTFILE_05=tmp_test_05.pgn
TESTFILE_06=tmp_test_06.pgn
TESTFILE_07=tmp_test_07.pgn
TESTFILE_08=tmp_test_08.pgn

all:
	$(CC) $(FLAGS) -std=c99 $(FILES) -o $(EXE)

clean:
	rm -f $(EXE) $(EXAMPLEFILE) tmp_test_*

cpp:
	$(CPP) $(FLAGS) $(FILES) -o $(EXE)

check: cpp
check: all
check:
	cp files/replace_before.pgn $(TESTFILE_03)
	$(VALGRIND) ./$(EXE)
	diff $(TESTFILE_01) files/complex.pgn
	diff $(TESTFILE_02) files/equal_variations.pgn
	diff $(TESTFILE_03) files/replace_after.pgn
	diff $(TESTFILE_04) $(TESTFILE_01)
	diff $(TESTFILE_05) files/complex_less.pgn
	diff $(TESTFILE_06) files/escaped_doublequote.pgn
	diff $(TESTFILE_07) files/delete_next_moves_after.pgn
	diff $(TESTFILE_08) files/variation_insert_after.pgn

valgrind: VALGRIND = valgrind -q --leak-check=full --track-origins=yes
valgrind: check
