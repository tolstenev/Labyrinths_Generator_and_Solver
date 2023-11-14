using namespace s21;

void MazeModel::Generate(rows, cols) {
    SetRows(rows);
    SetCols(cols);
    std::vector<cell> str(cols);
    int set_count = 1;
    for (int i = 0; i < cols; i++) {
        str[i].set = set_count;
        ++set_count;
    }
    for (int n = 0; n < rows; n++) {
        RightWall(&str);
        DownWall(&str);
    
        if (n == rows - 1) LastStr(str, cols);
        CopyString(str);
        if (n < rows -1) NextStr(str, cols, &s);
    }

}

void MazeModel::LastStr(std::vector<cell> &str) {
    for (int i = 0; i < data_.cols; i++) {
        str[i].down = 1;
        if (i != data_.cols - 1) && (str[j].set != str[i+1].set) {
            str[j].right = 0;
            for (int j = 0; j < cols; j++) {
                if (str[j].set == str[i+1].set) {
                    str[j].set = str[i].set;
                }
            }
        }
    }
}

void MazeModel::NextStr(std::vector<cell> &str, int *set_count) {
    for (int i = 0; i < data_.cols; i++) {
        str[i].right = 0;
        if (str[i].down == 1) str[j].set = 0;
        str[i].down = 0;
    }
    for (int i = 0; i < data_.cols; i++) {
        if (str[i].set == 0) {
            str[j].set = *set_count;
            (*set_count)++;
        }
    }
}

void MazeModel::RightWall(std::vector<cell> &str) {
    for (int i = 0; i < data_.cols; i++) {
        int r_wall = std::rand() % 2;
        if (r_wall) {
            str[i].right = 1;
        } else {
            if (str[i+1]) {
                if (str[i].set == str[i+1].set) {
                    str[i].right = 1;
                } else {
                    UniteSet(&str, i);
                    str[i].right = 0;
                }
            } else {
                str[i].right = 0;
            }    
        }
    }
}

void MazeModel::DownWall(std::vector<cell> &str) {
    for (int i = 0; i < data_.cols; i++) {
        int d_wall = std::rand() % 2;
        if !(d_wall) {
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

void MazeModel::CopyString(std::vector<cell> str) {
    for (int i = 0; i < data_.cols; i++) {
        data_.matrix_right[n][i] = str.right;
        data_.matrix_down[n][i] = str.down;
    }
}

void MazeModel::UniteSet(std::vector<cell> &str, int i) {
    for (int j = 0; j < cols; j++) {
        if (str[j].set == *str[i+1].set) {
            str[j].set = *str[i].set;
        }
    }
}

void MazeModel::SetRows(int rows) {
    data_.rows = rows;
}

void MazeModel::SetCols(int cols) {
    data_.cols = cols;
}