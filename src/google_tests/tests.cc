#include <gtest/gtest.h>

#include "../model/maze_model.h"
namespace s21 {

TEST(maze_tests, generate_1) {
  MazeModel A;
  A.SetRows(3);
  A.SetCols(3);
  A.Generate();
  for (int i = 0; i < 3; i++) {
    EXPECT_TRUE(A.GetData().matrix_right[i][2]);
  }
  for (int j = 0; j < 3; j++) {
    EXPECT_TRUE(A.GetData().matrix_down[2][j]);
  }
}

TEST(maze_tests, way_1) {
  MazeModel A;
  std::string file_path = "src/google_tests/test.txt";
  A.Import(file_path);
  A.Solution(std::make_pair(0, 0), std::make_pair(4, 4));

  std::vector<std::pair<int, int>> coordinates;

  coordinates.push_back(std::make_pair(4, 4));
  coordinates.push_back(std::make_pair(4, 3));
  coordinates.push_back(std::make_pair(4, 2));
  coordinates.push_back(std::make_pair(3, 2));
  coordinates.push_back(std::make_pair(3, 1));
  coordinates.push_back(std::make_pair(3, 0));
  coordinates.push_back(std::make_pair(2, 0));
  coordinates.push_back(std::make_pair(1, 0));
  coordinates.push_back(std::make_pair(0, 0));
  std::array<std::pair<int, int>, 250> arr;
  std::copy(coordinates.begin(), coordinates.end(), arr.begin());
  A.Solution(std::make_pair(0, 0), std::make_pair(4, 4));
  EXPECT_TRUE(A.GetData().is_solved);
  EXPECT_EQ(A.GetWay(), arr);
}

TEST(maze_tests, way_2) {
  MazeModel A;
  std::string file_path =
      "src/google_tests/test_wrong.txt";
  A.Import(file_path);
  A.Solution(std::make_pair(0, 0), std::make_pair(4, 4));
  EXPECT_FALSE(A.GetData().is_solved);
}


TEST(ParserTest, ParseImportPositive) {
  s21::MazeModel model;

  std::string valid_file_path = "src/google_tests/maze3x3.txt";

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
  std::string valid_file_path = "src/google_tests/maze3x3.txt";
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

}  // namespace s21
