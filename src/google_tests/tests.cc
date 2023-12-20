#include <gtest/gtest.h>

#include "../model/maze_model.h"
namespace s21 {

TEST(maze_tests, generate_1) {
  MazeModel A;
  A.SetRows(30);
  A.SetCols(30);
  A.Generate();
  for (int i = 0; i < 30; i++) {
    EXPECT_TRUE(A.GetData().matrix_right[i][29]);
  }
  for (int j = 0; j < 30; j++) {
    EXPECT_TRUE(A.GetData().matrix_down[29][j]);
  }
  A.Solution(std::make_pair(29, 0), std::make_pair(0, 29));
  EXPECT_TRUE(A.GetData().is_solved);
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
  std::string file_path = "src/google_tests/test_wrong.txt";
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

TEST(ParserTest, ParseExport_Positive) {
  // Create an instance of the Parser class
  s21::MazeModel model;
  std::string valid_file_path = "src/google_tests/maze3x3.txt";

  // std::string valid_file_path = "maze3x3.txt";
  model.Import(valid_file_path);

  // Call the ParseExport function with a valid path to file
  model.Export("maze3.txt");

  // Verify that the output file is generated correctly
  std::ifstream in(valid_file_path);
  std::string line;
  std::getline(in, line);
  ASSERT_EQ(line, "3 3");
  std::getline(in, line);
  ASSERT_EQ(line, "0 0 1");
  std::getline(in, line);
  ASSERT_EQ(line, "1 0 1");
  std::getline(in, line);
  ASSERT_EQ(line, "1 0 1");
  std::getline(in, line);
  ASSERT_EQ(line, "");
  std::getline(in, line);
  ASSERT_EQ(line, "0 0 1");
  std::getline(in, line);
  ASSERT_EQ(line, "0 1 0");
  std::getline(in, line);
  ASSERT_EQ(line, "1 1 1");
}

}  // namespace s21
