#ifndef MAZE_DATA_OBJECTS_H
#define MAZE_DATA_OBJECTS_H

#include <vector>

namespace s21 {

struct Data {
  bool exist = false;
  bool is_solved = false;
  bool start_is_set = false;
  bool finish_is_set = false;
  int rows = 1;
  int cols = 1;
  std::pair<int, int> start{};
  std::pair<int, int> finish{};
  std::vector<std::vector<bool>> matrix_right{};
  std::vector<std::vector<bool>> matrix_down{};
  std::stack<std::pair<int, int>> way{};
};

}  // namespace s21

#endif  // MAZE_DATA_OBJECTS_H
