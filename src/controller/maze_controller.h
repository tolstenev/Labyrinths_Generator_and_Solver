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
  Data GetData() { return model_.GetData(); }
  const std::array<std::pair<int, int>, 250> &GetWay(
      std::pair<int, int> start, std::pair<int, int> finish) {
    model_.Solution(start, finish);
    return model_.GetWay();
  };

  int GetWaySteps() { return model_.GetWaySteps(); }
  void ClearWay() { model_.ClearWay(); }
  bool IsSolved() { return model_.IsSolved(); };

  int Import(const std::string path_to_file) {
    int errcode = model_.Import(path_to_file);
    return errcode;
  }

  void Export(const std::string path_to_file) { model_.Export(path_to_file); }

 private:
  MazeModel &model_;

};  // class MazeController

}  // namespace s21

#endif  // MAZE_CONTROLLER_MAZE_CONTROLLER_H_
