#include "maze_model.h"


using namespace s21;

void MazeModel::Generate(/*int rows, int cols*/) {
  //  SetRows(rows);
  //  SetCols(cols);
  SizeMatrix(data_.rows, data_.cols);
  std::vector<Cell> str(data_.cols);
  int set_count = 1;
  for (int i = 0; i < data_.cols; i++) {
    str[i].set = set_count;
    set_count++;
  }
  for (int n = 0; n < data_.rows; n++) {
    RightWall(str);
    DownWall(str);

    if (n == data_.rows - 1) LastStr(str);
    CopyString(str, n);
    if (n < data_.rows - 1) NextStr(str, &set_count);
  }
}

void MazeModel::LastStr(std::vector<Cell> &str) {
  for (int i = 0; i < data_.cols; i++) {
    str[i].down = 1;
  }
  for (int i = 0; i < data_.cols - 1; i++) {
    if (str[i].set != str[i + 1].set) {
      str[i].right = 0;
      UniteSet(str, i);
    }
  }
}

void MazeModel::NextStr(std::vector<Cell> &str, int *set_count) {
  for (int i = 0; i < data_.cols - 1; i++) {
    str[i].right = 0;
  }
  for (int i = 0; i < data_.cols; i++) {
    if (str[i].down == 1) {
      str[i].set = *set_count;
      (*set_count)++;
      str[i].down = 0;
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
    // int r_wall = std::rand() % 2;
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
    // int d_wall = std::rand() % 2;
    if (!d_wall) {
      str[i].down = 0;
    } else {
      int count = 0;
      for (int j = 0; j < data_.cols; j++) {
        if (str[i].set == str[j].set && str[j].down == 0) {
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
  int num = str[i + 1].set;
  for (int j = 0; j < data_.cols; j++) {
    if (str[j].set == num) {
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

void MazeModel::Solution(
    std::pair<int, int> start, std::pair<int, int> finish) {
  std::vector<std::vector<Finder>> lab = InitLab();
  int n = Wave(&lab, start, finish);
  // std::stack<std::pair<int, int>> way = 
  FindWay(lab, n, start, finish);
  //return way;
}

std::vector<std::vector<Finder>> MazeModel::InitLab() {
  std::vector<std::vector<Finder>> lab(data_.rows,
                                       std::vector<Finder>(data_.cols));
  for (int i = 0; i < data_.rows; i++) {
    for (int j = 0; j < data_.cols; j++) {
      if (!data_.matrix_right[i][j]) lab[i][j].right = &lab[i][j + 1];
      if (!data_.matrix_down[i][j]) lab[i][j].down = &lab[i + 1][j];
      if (i > 0 && !data_.matrix_down[i - 1][j]) lab[i][j].up = &lab[i - 1][j];
      if (j > 0 && !data_.matrix_right[i][j - 1])
        lab[i][j].left = &lab[i][j - 1];
    }
  }
  return lab;
}

int MazeModel::Wave(std::vector<std::vector<Finder>> *lab,
                    std::pair<int, int> start, std::pair<int, int> finish) {
  (*lab)[start.first][start.second].step = 1;
  int n = 1;
  while (!(*lab)[finish.first][finish.second].step) {
    int next = 0;
    for (int i = 0; i < data_.rows; i++) {
      for (int j = 0; j < data_.cols; j++) {
        if ((*lab)[i][j].step == n) {
          if ((*lab)[i][j].right && !(*lab)[i][j].right->step) {
            (*lab)[i][j].right->step = n + 1;
            next++;
          }
          if ((*lab)[i][j].left && !(*lab)[i][j].left->step) {
            (*lab)[i][j].left->step = n + 1;
            next++;
          }
          if ((*lab)[i][j].up && !(*lab)[i][j].up->step) {
            (*lab)[i][j].up->step = n + 1;
            next++;
          }
          if ((*lab)[i][j].down && !(*lab)[i][j].down->step) {
            (*lab)[i][j].down->step = n + 1;
            next++;
          }
        }
      }
    }
    if (!next) break;
    n++;
  }
  return n;
}

void MazeModel::FindWay(
    std::vector<std::vector<Finder>> lab, int n, std::pair<int, int> start,
    std::pair<int, int> finish) {
  //std::stack<std::pair<int, int>> way;
  if (!lab[finish.first][finish.second].step) {
    throw std::invalid_argument("Путь не найден!\n");
  } else {
    int i = finish.first, j = finish.second;
    data_.way.push(std::make_pair(i, j));
    while (data_.way.top() != start) {
      if (lab[i][j].right && lab[i][j].right->step == n - 1) {
        j++;
      } else if (lab[i][j].left && lab[i][j].left->step == n - 1) {
        j--;
      } else if (lab[i][j].up && lab[i][j].up->step == n - 1) {
        i--;
      } else if (lab[i][j].down && lab[i][j].down->step == n - 1) {
        i++;
      }
      data_.way.push(std::make_pair(i, j));
      n--;
    }
    //return way;
  }
}


std::stack<std::pair<int, int>> MazeModel::GetWay() { return data_.way; }

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

void MazeModel::PrintLab() {
  for (int i = 0; i < data_.cols; i++) std::cout << "__";
  std::cout << std::endl;
  for (int i = 0; i < data_.rows; i++) {
    std::cout << "|";
    for (int j = 0; j < data_.cols; j++) {
      if (data_.matrix_down[i][j]) {
        std::cout << "_";
      } else {
        std::cout << " ";
      }
      if (data_.matrix_right[i][j]) {
        std::cout << "|";
      } else {
        std::cout << " ";
      }
    }
    std::cout << std::endl;
  }
}

void PrintStack(std::stack<std::pair<int, int>> s) {
  while (!s.empty()) {
    std::cout << "(" << s.top().first << ", " << s.top().second << ") ";
    s.pop();
  }
  std::cout << '\n';
}



//  }
// int main() {
//   MazeModel A;
//   A.SetRows(50);
//   A.SetCols(50);
//   A.Generate();
//   //   try {
//   //      std::stack<std::pair<int, int>> B = A.Solution(std::make_pair(0,
//   // 0),
//   //      std::make_pair(4, 4));
//   //   } catch (std::exception &e) {
//   //     std::cout << e.what() << std::endl;
//   //   }
//   // std::stack<std::pair<int, int>> B =
//   A.Solution(std::make_pair(0, 0), std::make_pair(1, 9));
//   // A.PrintMatrix();
//   A.PrintLab();
//   PrintStack(A.GetWay());
// }