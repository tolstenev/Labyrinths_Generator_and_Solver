#ifndef MAZE_CONTROLLER_MAZE_CONTROLLER_H_
#define MAZE_CONTROLLER_MAZE_CONTROLLER_H_

#include "../model/maze_model.h"

namespace s21 {

class MazeController {
 public:
  MazeController(MazeModel &m) : model_(m) {};

  Data Generate() {
    model_.Generate(/*25, 25*/);
    return model_.GetData();
  };

  void SetRows(int rows) { model_.SetRows(rows); };
  void SetCols(int cols) { model_.SetCols(cols); };

//  1. Добавить сеттеры для рядов
//  2. для колонок


 private:
  MazeModel &model_;

};  // class MazeController

}  // namespace s21

#endif //MAZE_CONTROLLER_MAZE_CONTROLLER_H_
