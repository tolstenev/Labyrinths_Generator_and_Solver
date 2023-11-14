#ifndef MAZE_MODEL_MAZE_MODEL_H
#define MAZE_MODEL_MAZE_MODEL_H


namespace s21 {

struct Data {
    int rows;
    int cols;
    std::vector<std::vector<bool>> matrix_right;
    std::vector<std::vector<bool>> matrix_down; 
}

struct Cell {
    int set;
    bool right;
    bool down;
}

class MazeModel {
    public:
        void Generate(int rows, int cols); 
        void SetRows(int rows);
        void SetCols(int cols); 

    private:
        Data data_;

        void LastStr(std::vector<cell> &str);
        void NextStr(std::vector<cell> &str, int *set_count);
        void RightWall(std::vector<cell> &str); 
        void DownWall(std::vector<cell> &str);
        void CopyString(std::vector<cell> str);
        void UniteSet(std::vector<cell> &str, int i);

}


}  // namespace s21

#endif  // MAZE_MODEL_MAZE_MODEL_H

