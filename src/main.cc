#include <QApplication>

#include "./controller/maze_controller.h"
#include "./model/maze_model.h"
#include "./view/maze_window.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  s21::MazeModel model;
  s21::MazeController controller(model);
  s21::MazeWindow view(controller);
  view.show();
  return app.exec();
}
