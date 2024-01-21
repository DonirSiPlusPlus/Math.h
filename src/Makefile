CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11 -pedantic #-fsanitize=address 

all: s21_math.a cpplint test cppcheck gcov_report
	rm -Rf *.gcno
	rm -Rf *.gcda
	rm -Rf *.o
	rm -Rf *.info

s21_math.a : s21_math.o
	ar -cr s21_math.a s21_math.o

test:
	gcc s21_math_tests.c s21_math.c -o s21_test -lcheck
	./s21_test

leaks: test
	leaks -atExit -- ./s21_test

lcov: test
	lcov -t “test” -o lcov_test.info -c -d .
	genhtml -o report lcov_test.info
	open ./report/index.html

gcov_report: 
	gcc --coverage s21_math_tests.c s21_math.c -o s21_test -lcheck
	./s21_test
	lcov -t s21_test -o test.info -c -d .
	genhtml -o report test.info

clang:
	clang-format -i *.c *.h
	clang-format -n *.c *.h

check:
	cppcheck *.c *.h

val :
	gcc -O0 -g s21_math_tests.c -o vgcheck
	valgrind ./s21_test --leak-check=full

clean:
	rm -Rf *.o
	rm -Rf *.a
	rm -Rf *.gcno
	rm -Rf *.gcda
	rm -Rf s21_test
	rm -Rf *.info
	rm -Rf report

s21_math.o: s21_math.c s21_math.h
	gcc $(CFLAGS) -c s21_math.c