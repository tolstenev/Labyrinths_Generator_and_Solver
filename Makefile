NAME			:= Maze

CC				:= gcc
CPP_FLAGS		:= -std=c++17 -pedantic -lstdc++
MAIN			:= ./src/main.cc
VIEW_HDR		:= ./src/view/maze_window.h
VIEW_SRC		:= ./src/view/maze_window.cc
CONTROLLER_HDR	:=
MODEL_HDR		:= ./src/model/maze_model.h
MODEL_SRC		:= ./src/model/maze_model.cc
HELPER_HDR		:= ./src/helpers/data_objects.h
TEST_PATH		:= ./src/google_tests/tests.cc

INSTALL_DIR 	:= $(HOME)/Desktop

SRCS			:= $(VIEW_HDR)       \
			   	   $(VIEW_SRC)       \
			   	   $(CONTROLLER_HDR) \
			   	   $(MODEL_HDR)      \
			   	   $(MODEL_SRC)      \
			   	   $(HELPER_HDR)     \
			   	   $(MAIN)           \
				   $(TEST_PATH)

ifeq ($(OS), Darwin)
	LIBFLAGS = -lm -lgtest -lgtest_main -lstdc++
else
	LIBFLAGS=-lgtest -lgtest_main -lm -lpthread -fprofile-arcs -ftest-coverage -lstdc++
endif

all: clean install open

install: clean
	mkdir build
	cd build && cmake ../CMakeLists.txt && make
	mv ./build/$(NAME).app "$(INSTALL_DIR)/$(NAME).app"

open:
	open $(INSTALL_DIR)/$(NAME).app

uninstall:
	rm -rf ./build
	rm -rf $(INSTALL_DIR)/$(NAME).app

tests: clean
	$(CC) $(CPP_FLAGS) $(TEST_PATH) $(MODEL_SRC) -o test $(LIBFLAGS)
	./test	

lint: .clang-format
	@clear
	clang-format -i $(SRCS)

check: .clang-format
	@clear
	clang-format -n $(SRCS)

clean:
	@clear
	rm -rf build
	rm -rf $(NAME)\
	*.o \
	*.info \
	*.gcda \
	*.gcno \
	*.gcov \
	*.gch  \
	report \
	test   \
	*.out    