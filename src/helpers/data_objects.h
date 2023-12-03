#ifndef MAZE_DATA_OBJECTS_H
#define MAZE_DATA_OBJECTS_H

#include <vector>

namespace s21 {

struct Data {
  int rows = 1;
  int cols = 1;
  std::pair<int, int> start{};
  std::pair<int, int> finish{};
  std::vector<std::vector<bool>> matrix_right{};
  std::vector<std::vector<bool>> matrix_down{};
  std::array<std::pair<int, int>, 250> way{};
  int way_steps{};
  bool is_solved{};
};

}  // namespace s21

#endif  // MAZE_DATA_OBJECTS_H
