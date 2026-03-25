#include <QApplication>

#include "RadarTestWindow.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  RadarTestWindow window;
  window.show();
  return app.exec();
}
