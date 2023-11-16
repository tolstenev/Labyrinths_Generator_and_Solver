#include "maze_window.h"

#include <fstream>

s21::MazeWindow::MazeWindow(QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::MazeWindow) {
  ui_->setupUi(this);
  setWindowTitle("Maze");
}

void s21::MazeWindow::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  QPainter painter(this);
  painter.setPen(QPen(Qt::red, 2));

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
  int rows = 10;
  int cols = 10;
  int size = 500;
  double cell_width = size / rows;
  double cell_height = size / cols;
  QVector<QVector<int>> vertical_walls;
  QVector<QVector<int>> horizontal_walls;

  // Установка каждой стенки
  for (int i = 0; i < rows; i++) {
    QVector<int> row;
    for (int j = 0; j < cols; j++) {
      row.append(1);
    }
    vertical_walls.append(row);
  }

  // Установка каждой стенки
  for (int i = 0; i < rows; i++) {
    QVector<int> row;
    for (int j = 0; j < cols; j++) {
      row.append(1);
    }
    horizontal_walls.append(row);
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols - 1; j++) {
      if (vertical_walls[i][j] == 1) {
        int x = (j + 1) * cell_width;
        int y1 = i * cell_height;
        int y2 = (i + 1) * cell_height;
        painter->drawLine(start_x + x, start_y + y1, start_x + x, start_y + y2);
      }
    }
  }

  for (int i = 0; i < rows - 1; i++) {
    for (int j = 0; j < cols; j++) {
      if (horizontal_walls[i][j] == 1) {
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
