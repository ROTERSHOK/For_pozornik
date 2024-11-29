.PHONY: all clean s21_matrix_oop.a test gcov_report 

CC=g++
CFLAGS=-Wall -Werror -Wextra --std=c++17 -g
LDFLAGS=-lgtest -lgtest_main -lpthread -ld_classic

GCOV_FLAGS=-lgcov -fprofile-arcs -ftest-coverage

FILES=sources/*.cpp
TEST_FILES=test/test.cpp

all: test  gcov_report

clean: 
	rm -f s21_gcov
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.info
	rm -rf report
	rm -f *.o
	rm -f test_exe
	rm -f s21_matrix_oop.a

s21_matrix_oop.a: $(FILES)
	$(CC) -c $(CFLAGS) $(FILES)
	ar rcs s21_matrix_oop.a *.o

test: s21_matrix_oop.a $(FILES) $(TEST_FILES)
	$(CC) $(CFLAGS) $(TEST_FILES) -L. s21_matrix_oop.a -o test_exe $(LDFLAGS)
	./test_exe
	$(MAKE) clean

gcov_report: $(TEST_FILES)
	$(CC) $(CFLAGS) $(TEST_FILES) $(FILES) -o test_gcov $(LDFLAGS) $(GCOV_FLAGS)
	./test_gcov
	lcov --ignore-errors mismatch --ignore-errors inconsistent -t test_gcov -c -d ./ -o ./test.info 
	genhtml ./test.info -o ./report/
	open report/index.html
	rm -rf *.gcda *.gcno *.info test_gcov