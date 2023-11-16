#ifndef MAZE_VIEW_MAZE_WINDOW_H
#define MAZE_VIEW_MAZE_WINDOW_H

#include <QKeyEvent>
#include <QMainWindow>
#include <fstream>
#include <iostream>

#include "./ui_maze_window.h"
//#include <QGraphicsView>
//#include <QGraphicsScene>
//#include <QLineF>
//#include <QPen>
#include <QFile>
#include <QPainter>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui {
class MazeWindow;
}
QT_END_NAMESPACE

namespace s21 {

class MazeWindow : public QMainWindow {
  Q_OBJECT

 public:
  MazeWindow(QWidget *parent = nullptr);
  ~MazeWindow();

  void keyPressEvent(QKeyEvent *event) override;
  void paintEvent(QPaintEvent *event) override;

 private:
  Ui::MazeWindow *ui_;
  void DrawBoarders(QPainter *painter) const;
  void DrawMaze(QPainter *painter) const;
};

}  // namespace s21

#endif  // MAZE_VIEW_MAZE_WINDOW_H
