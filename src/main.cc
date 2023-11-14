#include <QApplication>

#include "view/maze_window.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::MazeWindow w;
  w.show();
  return a.exec();
}
