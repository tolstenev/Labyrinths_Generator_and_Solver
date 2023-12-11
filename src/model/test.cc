#include "maze_model.h"
#include "gtest/gtest.h"

TEST(ParserTest, ParseImportPositive) {
  s21::MazeModel model;

  std::string valid_file_path = "maze3x3.txt";

  int result = model.Import(valid_file_path);

  EXPECT_EQ(3, model.GetData().rows);
  EXPECT_EQ(3, model.GetData().cols);
  EXPECT_EQ(0, model.GetData().matrix_right[0][0]);
  EXPECT_EQ(0, model.GetData().matrix_right[0][1]);
  EXPECT_EQ(1, model.GetData().matrix_right[0][2]);
  EXPECT_EQ(1, model.GetData().matrix_right[1][0]);
  EXPECT_EQ(0, model.GetData().matrix_right[1][1]);
  EXPECT_EQ(1, model.GetData().matrix_right[1][2]);
  EXPECT_EQ(1, model.GetData().matrix_right[2][0]);
  EXPECT_EQ(0, model.GetData().matrix_right[2][1]);
  EXPECT_EQ(1, model.GetData().matrix_right[2][2]);
  EXPECT_EQ(0, model.GetData().matrix_down[0][0]);
  EXPECT_EQ(0, model.GetData().matrix_down[0][1]);
  EXPECT_EQ(1, model.GetData().matrix_down[0][2]);
  EXPECT_EQ(0, model.GetData().matrix_down[1][0]);
  EXPECT_EQ(1, model.GetData().matrix_down[1][1]);
  EXPECT_EQ(0, model.GetData().matrix_down[1][2]);
  EXPECT_EQ(1, model.GetData().matrix_down[2][0]);
  EXPECT_EQ(1, model.GetData().matrix_down[2][1]);
  EXPECT_EQ(1, model.GetData().matrix_down[2][2]);

}

TEST(ParserTest, ParseExportPositive) {

  s21::MazeModel model;
  std::string valid_file_path = "maze3x3.txt";
  model.Import(valid_file_path);

  std::vector<bool>& second_column = model.GetData().matrix_down[1];

  EXPECT_EQ(3, model.GetData().rows);
  EXPECT_EQ(3, model.GetData().cols);
  EXPECT_EQ(0, model.GetData().matrix_right[0][0]);
  EXPECT_EQ(0, model.GetData().matrix_right[0][1]);
  EXPECT_EQ(1, model.GetData().matrix_right[0][2]);
  EXPECT_EQ(1, model.GetData().matrix_right[1][0]);
  EXPECT_EQ(0, model.GetData().matrix_right[1][1]);
  EXPECT_EQ(1, model.GetData().matrix_right[1][2]);
  EXPECT_EQ(1, model.GetData().matrix_right[2][0]);
  EXPECT_EQ(0, model.GetData().matrix_right[2][1]);
  EXPECT_EQ(1, model.GetData().matrix_right[2][2]);
  EXPECT_EQ(0, model.GetData().matrix_down[0][0]);
  EXPECT_EQ(0, model.GetData().matrix_down[0][1]);
  EXPECT_EQ(1, model.GetData().matrix_down[0][2]);
  EXPECT_EQ(0, model.GetData().matrix_down[1][0]);
  EXPECT_EQ(1, model.GetData().matrix_down[1][1]);
  EXPECT_EQ(0, model.GetData().matrix_down[1][2]);
  EXPECT_EQ(1, model.GetData().matrix_down[2][0]);
  EXPECT_EQ(1, model.GetData().matrix_down[2][1]);
  EXPECT_EQ(1, model.GetData().matrix_down[2][2]);
}



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// g++ -Wall -Wextra -Werror -Wno-unused -pedantic -std=c++17 maze_model.cc test.cc -lgtest -o tests
// ./tests
