UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
CXX_COMPILER = -D CMAKE_CXX_COMPILER=clang++
APP_OPEN = @open buildRelease/viewer.app
BROWSER_OPENER = @open
endif

ifeq ($(UNAME), Linux)
CXX_COMPILER = 
APP_OPEN = ./buildRelease/viewer
BROWSER_OPENER = @x-www-browser
endif

OBJ_FILES = models/*.obj
FILES_OUT = $(OBJ_FILES:.obj=.txt)

.PHONY: install uninstall clean dvi dist test gcov_report
install: buildRelease
	@cmake --build buildRelease

all: clean install test gcov_report

uninstall: clean
# END THAT

open: install
	${APP_OPEN}

clean:
	@rm -rf buildRelease 2>/dev/null
	@rm -rf buildDebug 2>/dev/null
	@rm *.tar.gz 2>/dev/null || true

dist: buildRelease
	@cmake --build buildRelease --target package_source
	@cp buildRelease/*.tar.gz .

test: buildRelease
	@cmake --build buildRelease --target test
	@echo "\033[0;32m-----------TESTS------------:\033[0m"
	@./buildRelease/test
	@echo "\033[0;32m----------------------------:\033[0m"
	@echo "\033[0;32m------CHECK FORMATTING------:\033[0m"
	@cmake --build buildRelease --target format-check
	@echo "\033[0;32m----------------------------:\033[0m"

gcov_report: buildDebug
	@cmake --build buildDebug --target test_coverage
	${BROWSER_OPENER} buildDebug/test_coverage/index.html
	
buildRelease:	
	@cmake -S . -B buildRelease -D CMAKE_C_COMPILER=gcc $(CXX_COMPILER) -D CMAKE_BUILD_TYPE=Release
buildDebug:
	@cmake -S . -B buildDebug -D CMAKE_C_COMPILER=gcc $(CXX_COMPILER) -D CMAKE_BUILD_TYPE=Debug

simple_example: buildRelease
	@cmake --build buildRelease --target simple_example
	@./buildRelease/simple_example

valgrind_test: buildRelease
	@cmake --build buildRelease --target test
	CK_FORK=no valgrind --leak-check=full ./buildRelease/test

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem c/*.c c/*.h

format:
	@cmake --build buildRelease --target format

change_format:
	chmod +x change_to_obj.sh && ./change_to_obj.sh

dvi:
	open documentation.md
