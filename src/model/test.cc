// #include <vector>
#include "maze_model.h"
#include "gtest/gtest.h"

TEST(ParserTest, ParseImportPositive) {
  s21::Parser &parser = s21::Parser::GetInstance();
  // Provide a valid path to the file for positive test case
  std::string valid_file_path = "maze3x3.txt";
  
  // Call the ParseImport function
  parser.ParseImport(valid_file_path);

  // int rows = parser.GetData().rows;

  // Assert the expected values of the data member variables in the Parser class
  EXPECT_EQ(3, parser.GetData().rows);
  EXPECT_EQ(3, parser.GetData().cols);

  EXPECT_EQ(0, parser.GetData().matrix_right[0][0]);
  EXPECT_EQ(0, parser.GetData().matrix_right[0][1]);
  EXPECT_EQ(1, parser.GetData().matrix_right[0][2]);

  EXPECT_EQ(1, parser.GetData().matrix_right[1][0]);
  EXPECT_EQ(1, parser.GetData().matrix_right[1][1]);
  EXPECT_EQ(0, parser.GetData().matrix_right[1][2]);
  
  EXPECT_EQ(1, parser.GetData().matrix_right[2][0]);
  EXPECT_EQ(1, parser.GetData().matrix_right[2][1]);
  EXPECT_EQ(1, parser.GetData().matrix_right[2][2]);
  
  EXPECT_EQ(0, parser.GetData().matrix_down[0][0]);
  EXPECT_EQ(0, parser.GetData().matrix_down[0][1]);
  EXPECT_EQ(1, parser.GetData().matrix_down[0][2]);
  
  EXPECT_EQ(0, parser.GetData().matrix_down[1][0]);
  EXPECT_EQ(1, parser.GetData().matrix_down[1][1]);
  EXPECT_EQ(0, parser.GetData().matrix_down[1][2]);
  
  EXPECT_EQ(0, parser.GetData().matrix_down[2][0]);
  EXPECT_EQ(0, parser.GetData().matrix_down[2][1]);
  EXPECT_EQ(1, parser.GetData().matrix_down[2][2]);
}

// Negative test case for ParseImport
TEST(ParserTest, ParseImportNegative) {
  s21::Parser &parser = s21::Parser::GetInstance();

  // Assert that an invalid file path throws an exception
  EXPECT_THROW(parser.ParseImport("nonexistent.txt"), std::invalid_argument);
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// g++ -Wall -Wextra -Werror -Wno-unused -pedantic -std=c++17 maze_model.cc test.cc -lgtest -o tests
// ./tests
