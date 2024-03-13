UNAME_S := $(shell uname -s)

CC = gcc
FLAGS = -Werror -Wextra -Wall
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

ifeq ($(UNAME_S),Darwin)
	TST_LIBS := -I/opt/homebrew/opt/check/include -L/opt/homebrew/opt/check/lib -lcheck 
	TST_FLAG := -I/opt/homebrew/opt/check/include 
else
	TST_LIBS = $(shell pkg-config --libs check) 
	TST_FLAG = 
endif

DIR_FUNC_C = ./3D_Viewer/c_code
DIR_TEST_C = ./tests

DIR_FUNC_OBJ = obj_func
DIR_FUNC_GCOV_OBJ = obj_func_gcov
DIR_TEST_OBJ = obj_test

FILES_FUNC_C := $(wildcard $(DIR_FUNC_C)/*.c)
FILES_FUNC_H := $(wildcard $(DIR_FUNC_C)/*.h)
FILES_TEST_C := $(wildcard $(DIR_TEST_C)/*.c)
FILES_TEST_H := $(wildcard $(DIR_TEST_C)/*.h)

FILES_FUNC_OBJ := $(patsubst $(DIR_FUNC_C)/%.c, $(DIR_FUNC_OBJ)/%.o, $(FILES_FUNC_C))
FILES_FUNC_GCOV_OBJ := $(patsubst $(DIR_FUNC_C)/%.c, $(DIR_FUNC_GCOV_OBJ)/%.o, $(FILES_FUNC_C))
FILES_TEST_OBJ := $(patsubst $(DIR_TEST_C)/%.c, $(DIR_TEST_OBJ)/%.o, $(FILES_TEST_C))

#DOCKER_IMAGE = my_project_valgrind

all: makedirs gcov_report


test : makedirs $(FILES_FUNC_OBJ) $(FILES_TEST_OBJ)
	$(CC)  $(FILES_FUNC_OBJ) $(FILES_TEST_OBJ) -o test $(TST_LIBS)
	./test

$(DIR_FUNC_OBJ)/%.o: $(DIR_FUNC_C)/%.c
	$(CC) $(FLAGS) -c $< -o $@

$(DIR_TEST_OBJ)/%.o: $(DIR_TEST_C)/%.c
	$(CC) $(FLAGS) -c $< -o $@  $(TST_FLAG)

gcov_report: clean_gcov makedirs $(FILES_TEST_OBJ) $(FILES_FUNC_GCOV_OBJ)
	$(CC) $(GCOV_FLAGS) $(FILES_TEST_OBJ) $(FILES_FUNC_GCOV_OBJ) -o gcov_test $(TST_LIBS)
	-./gcov_test
	gcovr --html --html-details -o ./report/index.html
	#-rm $(DIR_FUNC_GCOV_OBJ)/*gcda $(DIR_FUNC_GCOV_OBJ)/*gcno

$(DIR_FUNC_GCOV_OBJ)/%.o: $(DIR_FUNC_C)/%.c
	$(CC) $(FLAGS) $(GCOV_FLAGS) -c $< -o $@

makedirs:
	mkdir -p obj_func_gcov obj_func obj_test report

clang:
	clang-format -n *.h $(FILES_FUNC_C) $(FILES_FUNC_H) $(FILES_TEST_C) $(FILES_TEST_H)

clangi:
	clang-format -i *.h $(FILES_FUNC_C) $(FILES_FUNC_H) $(FILES_TEST_C) $(FILES_TEST_H)

cpp:
	cppcheck --enable=all --suppress=missingIncludeSystem ../src

clean_gcov:
	-rm -r obj_func_gcov/*

clean:
	-rm s21_test s21_gcov_test *.a
	-rm *.exe
	-rm -r obj_func obj_func_gcov obj_test report
	-rm test-* $(DIR_FUNC_GCOV_OBJ)/*.o

# docker-build:
# 	docker build -t $(DOCKER_IMAGE) .

# valgrind: docker-build
# 	docker run --rm -it my_project_valgrind valgrind ./s21_test
