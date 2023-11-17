#ifndef MAZE_VIEW_MAZE_WINDOW_H
#define MAZE_VIEW_MAZE_WINDOW_H

#include <QKeyEvent>
#include <QMainWindow>
#include <QPainter>
#include <vector>

#include "../controller/maze_controller.h"
#include "../helpers/data_objects.h"
#include "./ui_maze_window.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MazeWindow;
}
QT_END_NAMESPACE

namespace s21 {

class MazeWindow : public QMainWindow {
  Q_OBJECT

 public:
  MazeWindow(MazeController &controller, QWidget *parent = nullptr);
  ~MazeWindow();

  void keyPressEvent(QKeyEvent *event) override;
  void paintEvent(QPaintEvent *event) override;

 private slots:
  void Generate();

 private:
  Ui::MazeWindow *ui_;
  MazeController &controller_;
  Data data_{};

  void ConnectSlots();
  void DrawBoarders(QPainter *painter) const;
  void DrawMaze(QPainter *painter) const;
};

}  // namespace s21

#endif  // MAZE_VIEW_MAZE_WINDOW_H
