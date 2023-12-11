#include "../model/maze_model.h"
#include "gtest/gtest.h"



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// g++ -Wall -Wextra -Werror -Wno-unused -pedantic -std=c++17 maze_model.cc test.cc -lgtest -o tests
// ./tests
