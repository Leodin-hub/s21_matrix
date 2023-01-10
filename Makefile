CFLAGS=-lstdc++ -std=c++17 -Wall -Werror -Wextra 

all: uninstall clean s21_matrix_oop.a test
rebuild: uninstall clean all

s21_matrix_oop.a: build_lib

build_lib: objects
	@ar rc s21_matrix_oop.a s21_*.o
	@ranlib s21_matrix_oop.a

objects:
	@gcc $(CFLAGS) -c s21_*.cpp

test: clean s21_matrix_oop.a tests.cpp
	@gcc $(CFLAGS) -lgtest tests.cpp s21_matrix_oop.a -o test
	@./test 

test_leak: clean s21_matrix_oop.a tests.cpp
	@gcc $(CFLAGS) -lgtest tests.cpp s21_matrix_oop.a -o test
	@leaks -atExit -- ./test

uninstall:
	@rm -rf *a
	@rm -rf s21_matrix_oop

clean:
	@rm -rf ./test CPPLINT.cfg *.gcno *.gcda
	@rm -rf ./test
	@rm -rf *.o

style_check:
	@cp ../materials/linters/.clang-format .
	clang-format -i *.h *.cpp
	@rm -rf .clang-format