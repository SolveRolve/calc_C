CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
LIBS =  -lcheck
LINUX = -lrt -lpthread -lm 
LFLAGS = -fprofile-arcs -ftest-coverage
OS = $(shell uname -s)

all: clean dvi test gcov_report install dist

stack.a:
	$(CC) -c $(CFLAGS) stack.c 
	ar rcs stack.a stack.o 

unit_tests.o:
	$(CC) -I$(brew --prefix check)/include -c $(CFLAGS) unit_tests.c

valgrind: test
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all -s ./unit_tests

test: clean stack.a unit_tests.o
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) unit_tests.o stack.a -o unit_tests $(LIBS)
else
	$(CC) unit_tests.o stack.a -o unit_tests $(LIBS) $(LINUX)
endif
	./unit_tests

gcov_report:
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) $(LFLAGS) unit_tests.c stack.c -o test.out $(LIBS)
else
	$(CC) $(CFLAGS) $(LFLAGS) unit_tests.c stack.c -o test.out $(LIBS) $(LINUX)
endif
	./test.out
	lcov -t "test" -o test.info -c -d .
	genhtml -o ./report test.info
	open ./report/index.html

install: uninstall clean
	mkdir build
	cd calc2/ && qmake && make && make clean && rm Makefile && mv ../calc2/*.app ../build

uninstall:
	rm -rf build*

dist:
	rm -rf Archive_SmartCalc_v1.0/
	mkdir Archive_SmartCalc_v1.0/
	mkdir Archive_SmartCalc_v1.0/src
	cp -R build/ Archive_SmartCalc_v1.0/src/
	tar cvzf Archive_SmartCalc_v1.0.tgz Archive_SmartCalc_v1.0/
	rm -rf Archive_SmartCalc_v1.0/


rebuild: clean
	make

dvi: dvi/dvi.html
	open dvi/dvi.html


style:
	cp ../materials/linters/.clang-format ./.clang-format
	clang-format -i ./*.c ./*.h
	clang-format -n ./*.c ./*.h

clean: uninstall
	
	rm -rf unit_tests *.o *.a
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf report
	rm -rf gcov_test
	rm -rf test.out

open_app: 
	open build/calc2.app