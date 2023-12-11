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
  std::string file_path = "/Users/marbrand/maze3/src/google_tests/test.txt";
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
      "/Users/marbrand/maze3/src/google_tests/test_wrong.txt";
  A.Import(file_path);
  A.Solution(std::make_pair(0, 0), std::make_pair(4, 4));
  EXPECT_FALSE(A.GetData().is_solved);
}

}  // namespace s21
