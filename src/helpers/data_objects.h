#ifndef MAZE_DATA_OBJECTS_H
#define MAZE_DATA_OBJECTS_H

#include <vector>

namespace s21 {

struct Data {
  int rows = 1;
  int cols = 1;
  std::vector<std::vector<bool>> matrix_right{};
  std::vector<std::vector<bool>> matrix_down{};
  std::vector<std::pair<int, int>> way{};
};

}  // namespace s21

#endif  // MAZE_DATA_OBJECTS_H
