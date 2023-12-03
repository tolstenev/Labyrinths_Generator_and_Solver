#ifndef MAZE_VIEW_MAZE_WINDOW_H
#define MAZE_VIEW_MAZE_WINDOW_H

#include <QKeyEvent>
#include <QMainWindow>
#include <QPainter>
#include <QErrorMessage>
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
  void mouseReleaseEvent(QMouseEvent* event) override;

 private slots:
  void Generate();
  void Solve();
//  void Import();
//  void Export();

 private:
  Ui::MazeWindow *ui_;
  MazeController &controller_;
  Data data_;
  const double start_x_{280};
  const double start_y_{20};
  const double size_{500};
  double cell_width_{};
  double cell_height_{};
  bool show_way_ = false;
  bool start_is_set_ = false;
  bool finish_is_set_ = false;
  bool maze_is_solved_ = false;
  bool data_exist_ = false;
  std::pair<int, int> start_{};
  std::pair<int, int> finish_{};

  void ConnectSlots();
  void DrawBoarders(QPainter *painter);
  void DrawMaze(QPainter *painter);
  void DrawSolving(QPainter *painter);
    void Clear();
};

}  // namespace s21

#endif  // MAZE_VIEW_MAZE_WINDOW_H
