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
  connect(ui_->bt_clear, &QPushButton::clicked, this, &MazeWindow::Clear);
//  connect(ui_->bt_import, &QPushButton::clicked, this, &MazeWindow::Import);
//  connect(ui_->bt_export, &QPushButton::clicked, this, &MazeWindow::Export);
}

//void s21::MazeWindow Import() {
//
//}
//
//void s21::MazeWindow Export() {
//
//}

void s21::MazeWindow::Generate() {
  Clear();
  controller_.SetRows(ui_->sb_vertical_cells->value());
  controller_.SetCols(ui_->sb_horizont_cells->value());
  data_ = controller_.Generate();
  data_exist_ = true;
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
    if (show_way_) {
        painter->setPen(QPen(Qt::red, 2));
        double start_x = start_x_ + cell_width_ / 2;
        double start_y = start_y_ + cell_height_ / 2;
        std::pair<int, int> current = data_.way[0];
        std::pair<int, int> next;
        for (int i = 1; i < data_.way_steps; ++i) {
            next = data_.way[i];
            painter->drawLine(std::round(start_x + current.second * cell_width_),
                              std::round(start_y + current.first * cell_height_),
                              std::round(start_x + next.second * cell_width_),
                              std::round(start_y + next.first * cell_height_));
            current = next;
        }
    }
}

void s21::MazeWindow::Solve() {
  if (data_exist_ && !controller_.IsSolved()) {
    data_.way = controller_.GetWay(start_, finish_);
    data_.way_steps = controller_.GetWaySteps();
    show_way_ = true;
    update();
  } else {
      QErrorMessage error_message;
      error_message.showMessage("This maze has no solution");
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
    start_is_set_ = false;
    finish_is_set_ = false;
    controller_.ClearWay();
    update();
}

void s21::MazeWindow::mouseReleaseEvent(QMouseEvent* event) {
    QPoint p = event->pos();
    int y = (p.x() - start_x_) / cell_width_;
    int x = (p.y() - start_y_) / cell_height_;
    if (!data_exist_) {
        Generate();
    } else if (!start_is_set_) {
        start_ = std::make_pair(x, y);
        start_is_set_ = true;
    } else if (!finish_is_set_) {
        finish_ = std::make_pair(x, y);
        finish_is_set_ = true;
        Solve();
    } else {
        Clear();
    }
}

s21::MazeWindow::~MazeWindow() { delete ui_; }
