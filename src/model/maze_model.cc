#include "maze_model.h"

#include <iostream>
#include <random>

using namespace s21;

void MazeModel::Generate(int rows, int cols) {
  SetRows(rows);
  SetCols(cols);
  SizeMatrix(rows, cols);
  std::vector<Cell> str(cols);
  int set_count = 1;
  for (int i = 0; i < cols; i++) {
    str[i].set = set_count;
    ++set_count;
  }
  for (int n = 0; n < rows; n++) {
    RightWall(str);
    DownWall(str);

    if (n == rows - 1) LastStr(str);
    CopyString(str, n);
    if (n < rows - 1) NextStr(str, &set_count);
  }
}

void MazeModel::LastStr(std::vector<Cell> &str) {
  for (int i = 0; i < data_.cols; i++) {
    str[i].down = 1;
    if ((i != data_.cols - 1) && (str[i].set != str[i + 1].set)) {
      str[i].right = 0;
      for (int j = 0; j < data_.cols; j++) {
        if (str[j].set == str[i + 1].set) {
          str[j].set = str[i].set;
        }
      }
    }
  }
}

void MazeModel::NextStr(std::vector<Cell> &str, int *set_count) {
  for (int i = 0; i < data_.cols; i++) {
    str[i].right = 0;
    if (str[i].down == 1) str[i].set = 0;
    str[i].down = 0;
  }
  for (int i = 0; i < data_.cols; i++) {
    if (str[i].set == 0) {
      str[i].set = *set_count;
      (*set_count)++;
    }
  }
}

void MazeModel::RightWall(std::vector<Cell> &str) {
  // Создание генератора случайных чисел
  std::random_device rd;
  std::mt19937 gen(rd());

  // Задание диапазона случайных чисел
  std::uniform_int_distribution<> dis(0, 1);

  for (int i = 0; i < data_.cols - 1; i++) {
    int r_wall = dis(gen);
    if (r_wall) {
      str[i].right = 1;
    } else {
      if (str[i].set == str[i + 1].set) {
        str[i].right = 1;
      } else {
        UniteSet(str, i);
        str[i].right = 0;
      }
    }
  }
  str[data_.cols - 1].right = 1;
}

void MazeModel::DownWall(std::vector<Cell> &str) {
  // Создание генератора случайных чисел
  std::random_device rd;
  std::mt19937 gen(rd());

  // Задание диапазона случайных чисел
  std::uniform_int_distribution<> dis(0, 1);

  for (int i = 0; i < data_.cols; i++) {
    int d_wall = dis(gen);
    if (!d_wall) {
      str[i].down = 0;
    } else {
      int count = 0;
      for (int j = 0; j < data_.cols; j++) {
        if (str[j].down == 0) {
          count++;
        }
      }
      if (count > 1) {
        str[i].down = 1;
      } else {
        str[i].down = 0;
      }
    }
  }
}

void MazeModel::CopyString(std::vector<Cell> str, int n) {
  for (int i = 0; i < data_.cols; i++) {
    data_.matrix_right[n][i] = str[i].right;
    data_.matrix_down[n][i] = str[i].down;
  }
}

void MazeModel::UniteSet(std::vector<Cell> &str, int i) {
  for (int j = 0; j < data_.cols; j++) {
    if (str[j].set == str[i + 1].set) {
      str[j].set = str[i].set;
    }
  }
}

void MazeModel::SetRows(int rows) { data_.rows = rows; }

void MazeModel::SetCols(int cols) { data_.cols = cols; }

void MazeModel::SizeMatrix(int rows, int cols) {
  data_.matrix_right.resize(rows);
  data_.matrix_down.resize(rows);
  for (int i = 0; i < rows; i++) {
    data_.matrix_right[i].resize(cols);
    data_.matrix_down[i].resize(cols);
  }
}

void MazeModel::PrintMatrix() {
  for (int i = 0; i < data_.rows; i++) {
    for (int j = 0; j < data_.cols; j++) {
      std::cout << data_.matrix_right[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
  for (int i = 0; i < data_.rows; i++) {
    for (int j = 0; j < data_.cols; j++) {
      std::cout << data_.matrix_down[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

int main() {
  MazeModel A;
  A.Generate(10, 10);
  A.PrintMatrix();
}