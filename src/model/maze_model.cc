#include "maze_model.h"

void s21::MazeModel::Generate() {
  ClearWay();
  ResizeMatrix();
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

void s21::MazeModel::ClearWay() {
  data_.is_solved = false;
  std::pair<int, int> zero_pair = std::make_pair(0, 0);
  data_.way.fill(zero_pair);
}

void s21::MazeModel::LastStr(std::vector<Cell> &str) {
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

void s21::MazeModel::NextStr(std::vector<Cell> &str, int *set_count) {
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

void s21::MazeModel::RightWall(std::vector<Cell> &str) {
  std::random_device rd;
  std::mt19937 gen(rd());

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

void s21::MazeModel::DownWall(std::vector<Cell> &str) {
  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_int_distribution<> dis(0, 1);

  for (int i = 0; i < data_.cols; i++) {
    int d_wall = dis(gen);
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

void s21::MazeModel::CopyString(std::vector<Cell> str, int n) {
  for (int i = 0; i < data_.cols; i++) {
    data_.matrix_right[n][i] = str[i].right;
    data_.matrix_down[n][i] = str[i].down;
  }
}

void s21::MazeModel::UniteSet(std::vector<Cell> &str, int i) {
  int num = str[i + 1].set;
  for (int j = 0; j < data_.cols; j++) {
    if (str[j].set == num) {
      str[j].set = str[i].set;
    }
  }
}

void s21::MazeModel::SetRows(int rows) { data_.rows = rows; }

void s21::MazeModel::SetCols(int cols) { data_.cols = cols; }

void s21::MazeModel::ResizeMatrix() {
  data_.matrix_right.resize(data_.rows);
  data_.matrix_down.resize(data_.rows);
  for (int i = 0; i < data_.rows; i++) {
    data_.matrix_right[i].resize(data_.cols);
    data_.matrix_down[i].resize(data_.cols);
  }
}

void s21::MazeModel::Solution(std::pair<int, int> start,
                              std::pair<int, int> finish) {
  std::vector<std::vector<Finder>> lab = InitLab();
  int n = Wave(&lab, start, finish);
  try {
    FindWay(lab, n, start, finish);
    data_.is_solved = true;
  } catch (...) {
    data_.is_solved = false;
  }
}

std::vector<std::vector<s21::Finder>> s21::MazeModel::InitLab() {
  std::vector<std::vector<s21::Finder>> lab(data_.rows,
                                            std::vector<Finder>(data_.cols));

  for (int i = 0; i < data_.rows; i++) {
    for (int j = 0; j < data_.cols; j++) {
      if (!data_.matrix_right[i][j]) lab[i][j].right = &lab[i][j + 1];
      if (!data_.matrix_down[i][j]) lab[i][j].down = &lab[i + 1][j];
      if (i > 0 && !data_.matrix_down[i - 1][j]) lab[i][j].up = &lab[i - 1][j];
      if (j > 0 && !data_.matrix_right[i][j - 1])
        lab[i][j].left = &lab[i][j - 1];
      //  std::cout << "*******" << std::endl;
    }
  }
  return lab;
}

int s21::MazeModel::Wave(std::vector<std::vector<s21::Finder>> *lab,
                         std::pair<int, int> start,
                         std::pair<int, int> finish) {
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

void s21::MazeModel::FindWay(std::vector<std::vector<Finder>> lab, int n,
                             std::pair<int, int> start,
                             std::pair<int, int> finish) {
  if (!lab[finish.first][finish.second].step) {
    throw std::invalid_argument("There is no solution\n");
  } else {
    int k = 0, i = finish.first, j = finish.second;
    data_.way[k] = (std::make_pair(i, j));
    while (data_.way[k] != start) {
      if (lab[i][j].right && lab[i][j].right->step == n - 1) {
        j++;
      } else if (lab[i][j].left && lab[i][j].left->step == n - 1) {
        j--;
      } else if (lab[i][j].up && lab[i][j].up->step == n - 1) {
        i--;
      } else if (lab[i][j].down && lab[i][j].down->step == n - 1) {
        i++;
      }
      data_.way[++k] = std::make_pair(i, j);
      n--;
    }
    data_.way_steps = k + 1;
  }
}

int s21::MazeModel::Import(const std::string path_to_file) {
  ModelError errcode = ModelError::kOk;
  int tmp{}, matrix_right_lines{}, matrix_down_lines{};
  bool right_matrix = true;
  size_t line_size = 0;
  char *pEnd;
  std::string line;
  std::ifstream file(path_to_file);

  std::getline(file, line);

  tmp = std::strtol(line.c_str(), &pEnd, 10);
  if (tmp > 0 && tmp < 51) {
    data_.rows = tmp;
  } else {
    errcode = ModelError::kErrorReading;
  }

  if (errcode == ModelError::kOk) {
    tmp = std::strtol(pEnd, NULL, 10);
    if (tmp > 0 && tmp < 51) {
      data_.cols = tmp;
    } else {
      errcode = ModelError::kErrorReading;
    }

    ResizeMatrix();
    data_.matrix_right.clear();
    data_.matrix_down.clear();

    while (std::getline(file, line) && (errcode == ModelError::kOk)) {
      line_size = line.size();

      if (line_size == 0) {
        right_matrix = false;
        continue;
      }

      std::vector<bool> tmp_vector;
      errcode = ScanMatrixLineToVector(line, line_size, tmp_vector);
      int size_cols = tmp_vector.size();
      if (size_cols != data_.cols) {
        errcode = ModelError::kErrorReading;
      }
      if (errcode == ModelError::kOk) {
        if (right_matrix) {
          data_.matrix_right.push_back(tmp_vector);
          matrix_right_lines++;
        } else {  // down matrix
          data_.matrix_down.push_back(tmp_vector);
          matrix_down_lines++;
        }
      }
    }

    if (data_.rows != matrix_right_lines && data_.rows != matrix_down_lines) {
      errcode = ModelError::kErrorReading;
    }
  }
  file.close();
  return static_cast<int>(errcode);
}

s21::MazeModel::ModelError s21::MazeModel::ScanMatrixLineToVector(
    const std::string from, const size_t line_size, std::vector<bool> &to) {
  ModelError errcode = ModelError::kOk;
  for (size_t i = 0; (i < line_size) && (errcode == ModelError::kOk); ++i) {
    if (from[i] != ' ') {
      if (from[i] == '1') {
        to.push_back(true);
      } else if (from[i] == '0') {
        to.push_back(false);
      } else {
        errcode = ModelError::kErrorReading;
      }
    }
  }
  return errcode;
}

void s21::MazeModel::Export(const std::string path_to_file) {
  std::ofstream out;
  out.open(path_to_file);
  if (out.is_open()) {
    out << data_.rows << " " << data_.cols << std::endl;

    for (int i = 0, end_i = data_.rows; i < end_i; ++i) {
      for (int j = 0, end_j = data_.cols; j < end_j; ++j) {
        out << data_.matrix_right.at(i).at(j) << " ";
      }
      out << std::endl;
    }
    out << std::endl;

    for (int i = 0, end_i = data_.rows; i < end_i; ++i) {
      for (int j = 0, end_j = data_.cols; j < end_j; ++j) {
        out << data_.matrix_down.at(i).at(j) << " ";
      }
      out << std::endl;
    }
    out.close();
  }
}
