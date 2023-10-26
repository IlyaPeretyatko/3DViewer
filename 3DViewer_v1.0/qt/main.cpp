#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow window;
  window.setWindowTitle("3D Viewer");
  window.setFixedSize(window.size());
  window.show();
  return a.exec();
}
