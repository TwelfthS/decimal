FLAGS = -Wall -Werror -Wextra -std=c11
LIB_FLAGS = -lcheck -lgcov
CODE_FILES = s21_*.c
TEST_FILES = test.c

all: test clean

style:
	clang-format -n *.c *.h
	clang-format -i *.c *.h

checks: style
	gcc $(FLAGS) $(CODE_FILES) $(TEST_FILES) -lcheck
	cppcheck *.c *.h

clean:
	rm -rf report *.a *.o *.gcda *.gcno *.gcov *.info test ./a.out

test: 
	gcc s21_*.c test.c -lcheck -o test
	# gcc $(TEST_FILES) -o test s21_decimal.a -lcheck
	./test
	rm ./test

s21_decimal.a:
	gcc -c $(CODE_FILES)
	ar rcs s21_decimal.a s21_*.o
	ranlib s21_decimal.a

gcov_report:
	gcc --coverage $(CODE_FILES) $(TEST_FILES) $(LIB_FLAGS) -o test
	-./test
	lcov -o test.info -c -d .
	genhtml -o report test.info
	open ./report/index.html
