#ifndef MAZE_MODEL_MAZE_MODEL_H
#define MAZE_MODEL_MAZE_MODEL_H

#include <iostream>
#include <random>
#include <array>
#include <vector>

#include <string> // подключаем строки
#include <fstream> // для std::getline

#include "../helpers/data_objects.h"

namespace s21 {

struct Cell {
  int set;
  bool right;
  bool down;
};

struct Finder {
  int step = 0;
  Finder *up = nullptr;
  Finder *down = nullptr;
  Finder *left = nullptr;
  Finder *right = nullptr;
};

class MazeModel {
 public:
  MazeModel() = default;
  ~MazeModel() = default;

  void Generate();
  Data GetData() { return data_; };
  void SetData(Data data) { data_ = data; }
  void Solution(std::pair<int, int> start, std::pair<int, int> finish);
  const std::array<std::pair<int, int>, 250>& GetWay() { return data_.way; };
  int GetWaySteps() { return data_.way_steps; };
  void ClearWay();
  bool IsSolved() { return data_.is_solved; };

  void SetRows(int rows);
  void SetCols(int cols);
  void PrintMatrix();
  void PrintLab();

  int Import(const std::string path_to_file);

//  void PrintStack();

 private:
    enum class ModelError : int {
      kOk = 0,
      kErrorReading,
    };

  Data data_;

  void LastStr(std::vector<Cell> &str);
  void NextStr(std::vector<Cell> &str, int *set_count);
  void RightWall(std::vector<Cell> &str);
  void DownWall(std::vector<Cell> &str);
  void CopyString(std::vector<Cell> str, int n);
  void UniteSet(std::vector<Cell> &str, int i);
  void ResizeMatrix();
  std::vector<std::vector<Finder>> InitLab();
  int Wave(std::vector<std::vector<Finder>> *lab, std::pair<int, int> start,
           std::pair<int, int> finish);
  void FindWay(std::vector<std::vector<Finder>> lab, int n,
               std::pair<int, int> start, std::pair<int, int> finish);
    MazeModel::ModelError ScanMatrixLineToVector(std::string from, size_t line_size, std::vector<bool>& to);

};

class Parser {
 public:
  static Parser& GetInstance() {
    static Parser instance;
    return instance;
  }

//  void ParseImportValidator(const std::string path_to_file);
//  void ParseImport(const std::string path_to_file);
//  void ParseExport(const std::string path_to_file);
  Data GetData() { return data_; };

  //std::vector<int>& GetIndices();

 private:
  Parser() {}
  Parser(const Parser&);
  Data data_;
};

}  // namespace s21

#endif  // MAZE_MODEL_MAZE_MODEL_H
