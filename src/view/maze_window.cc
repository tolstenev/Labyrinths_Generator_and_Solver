#include "maze_window.h"

#include <fstream>

s21::MazeWindow::MazeWindow(MazeController &controller, QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::MazeWindow), controller_(controller) {
  ui_->setupUi(this);
  setWindowTitle("Maze");
  ConnectSlots();
}

void s21::MazeWindow::ConnectSlots() {
  connect(ui_->bt_generate, &QPushButton::clicked, this, &MazeWindow::Generate);
//  connect(ui_->bt_solve, &QPushButton::clicked, this, &MazeWindow::Solve);
  connect(ui_->bt_clear, &QPushButton::clicked, this, &MazeWindow::Clear);
  connect(ui_->bt_import, &QPushButton::clicked, this, &MazeWindow::Import);
  connect(ui_->bt_export, &QPushButton::clicked, this, &MazeWindow::Export);
}

void s21::MazeWindow Import() {

}

void s21::MazeWindow Export() {
  
}

void s21::MazeWindow::Generate() {
  controller_.SetRows(ui_->sb_vertical_cells->value());
  controller_.SetCols(ui_->sb_horizont_cells->value());
  data_ = controller_.Generate();
  data_.exist = true;
  repaint();
}

void s21::MazeWindow::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  QPainter painter(this);
  painter.setPen(QPen(Qt::lightGray, 2));

  DrawBoarders(&painter);
  DrawMaze(&painter);
  DrawSolving(&painter);
}

void s21::MazeWindow::DrawBoarders(QPainter *painter) {
  int start_x = 280;
  int start_y = 20;
  int size = 500;
  painter->drawLine(start_x, start_y, start_x + size, start_y);
  painter->drawLine(start_x, start_y, start_x, start_y + size);
  painter->drawLine(start_x, start_y + size, start_x + size, start_y + size);
  painter->drawLine(start_x + size, start_y, start_x + size, start_y + size);
}

void s21::MazeWindow::DrawMaze(QPainter *painter) {
  cell_width_ = size_ / data_.cols;
  cell_height_ = size_ / data_.rows;

  for (int i = 0, end_i = data_.rows; i < end_i; ++i) {
    for (int j = 0, end_j = data_.cols - 1; j < end_j; ++j) {
      if (data_.matrix_right[i][j]) {
        double x = (j + 1) * cell_width_;
        double y1 = i * cell_height_;
        double y2 = (i + 1) * cell_height_;
        painter->drawLine(std::round(start_x_ + x), std::round(start_y_ + y1),
                          std::round(start_x_ + x), std::round(start_y_ + y2));
      }
    }
  }

  for (int i = 0, end_i = data_.rows - 1; i < end_i; ++i) {
    for (int j = 0, end_j = data_.cols; j < end_j; ++j) {
      if (data_.matrix_down[i][j]) {
        double x1 = j * cell_width_;
        double x2 = (j + 1) * cell_width_;
        double y = (i + 1) * cell_height_;
        painter->drawLine(std::round(start_x_ + x1), std::round(start_y_ + y),
                          std::round(start_x_ + x2), std::round(start_y_ + y));
      }
    }
  }
}

void s21::MazeWindow::DrawSolving(QPainter *painter) {
  //    /*For data_.way in list realization*/
  //    painter->setPen(QPen(Qt::red, 2));
  //    double start_x = start_x_ + cell_width_ / 2;
  //    double start_y = start_y_ + cell_height_ / 2;
  //    if (data_.way.size() > 1) {
  //        std::pair<int, int> current = data_.way.top();
  //        data_.way.pop();
  //        while (!data_.way.empty()) {
  //            std::pair<int, int> next = data_.way.top();
  //            data_.way.pop();
  //            painter->drawLine(std::round(start_x + current.second *
  //            cell_height_),
  //                              std::round(start_y + current.first *
  //                              cell_width_), std::round(start_x + next.second
  //                              * cell_height_), std::round(start_y +
  //                              next.first * cell_width_));
  //            current = next;
  //        }
  //    }
    if (show_way_) {
        auto s = data_.way;
        painter->setPen(QPen(Qt::red, 2));
        double start_x = start_x_ + cell_width_ / 2;
        double start_y = start_y_ + cell_height_ / 2;
        if (s.size() > 1) {
            std::pair<int, int> current = s.top();
            s.pop();
            while (!s.empty()) {
                std::pair<int, int> next = s.top();
                s.pop();
                painter->drawLine(std::round(start_x + current.second * cell_width_),
                                  std::round(start_y + current.first * cell_height_),
                                  std::round(start_x + next.second * cell_width_),
                                  std::round(start_y + next.first * cell_height_));
                current = next;
            }
        }
    }
}

void s21::MazeWindow::Solve() {
  if (data_.exist && !data_.is_solved) {
    data_.way = controller_.GetWay(data_.start, data_.finish);
    data_.is_solved = true;
    show_way_ = true;
    update();
  }
}

void s21::MazeWindow::keyPressEvent(QKeyEvent *event) {
  if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_W) {
    close();
  } else {
    QMainWindow::keyPressEvent(event);
  }
}

void s21::MazeWindow::Clear() {
    show_way_ = false;
    data_.is_solved = false;
    data_.start_is_set = false;
    data_.finish_is_set = false;
    controller_.ClearWay();
    update();
}

void s21::MazeWindow::mouseReleaseEvent(QMouseEvent* event) {
    QPoint p = event->pos();
    int y = (p.x() - start_x_) / cell_width_;
    int x = (p.y() - start_y_) / cell_height_;
    if (!data_.exist) {
        Generate();
    } else if (!data_.start_is_set) {
        data_.start = std::make_pair(x, y);
        data_.start_is_set = true;
    } else if (!data_.finish_is_set) {
        data_.finish = std::make_pair(x, y);
        data_.finish_is_set = true;
        Solve();
    }
}

s21::MazeWindow::~MazeWindow() { delete ui_; }
