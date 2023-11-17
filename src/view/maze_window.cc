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
}

void s21::MazeWindow::Generate() {
  data_ = controller_.Generate();
  repaint();
}

void s21::MazeWindow::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  QPainter painter(this);
  painter.setPen(QPen(Qt::lightGray, 2));

  DrawBoarders(&painter);
  DrawMaze(&painter);
}

void s21::MazeWindow::DrawBoarders(QPainter *painter) const {
  int start_x = 280;
  int start_y = 20;
  int size = 500;
  painter->drawLine(start_x, start_y, start_x + size, start_y);
  painter->drawLine(start_x, start_y, start_x, start_y + size);
  painter->drawLine(start_x, start_y + size, start_x + size, start_y + size);
  painter->drawLine(start_x + size, start_y, start_x + size, start_y + size);
}

void s21::MazeWindow::DrawMaze(QPainter *painter) const {
  int start_x = 280;
  int start_y = 20;
  int size = 500;
  double cell_width = size / data_.cols;
  double cell_height = size / data_.rows;

  for (int i = 0, end_i = data_.rows; i < end_i; ++i) {
    for (int j = 0, end_j = data_.cols - 1; j < end_j; ++j) {
      if (data_.matrix_right[i][j]) {
        int x = (j + 1) * cell_width;
        int y1 = i * cell_height;
        int y2 = (i + 1) * cell_height;
        painter->drawLine(start_x + x, start_y + y1, start_x + x, start_y + y2);
      }
    }
  }

  for (int i = 0, end_i = data_.rows - 1; i < end_i; ++i) {
    for (int j = 0, end_j = data_.cols; j < end_j; ++j) {
      if (data_.matrix_down[i][j]) {
        int x1 = j * cell_width;
        int x2 = (j + 1) * cell_width;
        int y = (i + 1) * cell_height;
        painter->drawLine(start_x + x1, start_y + y, start_x + x2, start_y + y);
      }
    }
  }
}

void s21::MazeWindow::keyPressEvent(QKeyEvent *event) {
  if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_W) {
    close();  // Закрытие окна по сочетанию клавиш Cmd+W
  } else {
    QMainWindow::keyPressEvent(event);
  }
}

s21::MazeWindow::~MazeWindow() { delete ui_; }
