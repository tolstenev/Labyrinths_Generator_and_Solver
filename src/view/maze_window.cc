#include "maze_window.h"

#include "./ui_maze_window.h"

s21::MazeWindow::MazeWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MazeWindow) {
  ui->setupUi(this);
  setWindowTitle("Maze");
}

void s21::MazeWindow::keyPressEvent(QKeyEvent *event) {
  if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_W) {
    close();  // Закрытие окна по сочетанию клавиш Cmd+W
  } else {
    QMainWindow::keyPressEvent(event);
  }
}

s21::MazeWindow::~MazeWindow() { delete ui; }
