#ifndef MAZEWINDOW_H
#define MAZEWINDOW_H

#include <QKeyEvent>
#include <QMainWindow>

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

 private:
  Ui::MazeWindow *ui;
};

}  // namespace s21

#endif  // MAZEWINDOW_H
