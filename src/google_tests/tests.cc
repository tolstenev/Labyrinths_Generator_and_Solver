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
  Parser B = Parser::GetInstance();
  std::string file_path = "test.txt";
  parser.ParseImport(file_path);
  A.SetData() = B.GetData();

  std::vector<std::pair<int, int>> coordinates;

  coordinates.push_back(std::make_pair(0, 0));
  coordinates.push_back(std::make_pair(1, 0));
  coordinates.push_back(std::make_pair(2, 0));
  coordinates.push_back(std::make_pair(3, 0));
  coordinates.push_back(std::make_pair(3, 1));
  coordinates.push_back(std::make_pair(3, 2));
  coordinates.push_back(std::make_pair(4, 2));
  coordinates.push_back(std::make_pair(4, 3));
  coordinates.push_back(std::make_pair(4, 4));

  A.Solution(std::make_pair(0, 0), std::make_pair(4, 4));

  EXPECT_TRUE(A.GetWay() == coordinates);
}

TEST(maze_tests, way_2) {
  MazeModel A;
  Parser B = Parser::GetInstance();
  std::string file_path = "test_wrong.txt";
  parser.ParseImport(file_path);
  A.SetData() = B.GetData();

  EXPECT_THROW(A.Solution(std::make_pair(0, 0), std::make_pair(4, 4)),
               std::invalid_argument);
}

}  // namespace s21
