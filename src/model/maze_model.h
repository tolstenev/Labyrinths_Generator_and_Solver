#ifndef MAZE_MODEL_MAZE_MODEL_H
#define MAZE_MODEL_MAZE_MODEL_H

#include <vector>

namespace s21 {

struct Data {
  int rows;
  int cols;
  std::vector<std::vector<bool>> matrix_right;
  std::vector<std::vector<bool>> matrix_down;
};

struct Cell {
  int set;
  bool right;
  bool down;
};

class MazeModel {
 public:
  MazeModel() = default;
  ~MazeModel() = default;

  void Generate(int rows, int cols);

  void SetRows(int rows);
  void SetCols(int cols);
  void PrintMatrix();
  void PrintLab();

 private:
  Data data_;

  void LastStr(std::vector<Cell> &str);
  void NextStr(std::vector<Cell> &str, int *set_count);
  void RightWall(std::vector<Cell> &str);
  void DownWall(std::vector<Cell> &str);
  void CopyString(std::vector<Cell> str, int n);
  void UniteSet(std::vector<Cell> &str, int i);
  void SizeMatrix(int rows, int cols);
};

}  // namespace s21

#endif  // MAZE_MODEL_MAZE_MODEL_H
