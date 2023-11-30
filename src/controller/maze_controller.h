#ifndef MAZE_CONTROLLER_MAZE_CONTROLLER_H_
#define MAZE_CONTROLLER_MAZE_CONTROLLER_H_

#include "../model/maze_model.h"

namespace s21 {

class MazeController {
 public:
  MazeController(MazeModel &m) : model_(m){};

  Data Generate() {
    model_.Generate();
    return model_.GetData();
  };

  void SetRows(int rows) { model_.SetRows(rows); };
  void SetCols(int cols) { model_.SetCols(cols); };

  std::stack<std::pair<int, int>> GetWay(std::pair<int, int> start,
                                         std::pair<int, int> finish) {
    model_.Solution(start, finish);
    return model_.GetWay();
  };

 private:
  MazeModel &model_;

};  // class MazeController

}  // namespace s21

#endif  // MAZE_CONTROLLER_MAZE_CONTROLLER_H_
