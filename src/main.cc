#include <QApplication>
#include <QStyleFactory>

#include "mainwindow.h"
#include "viewer_controller.h"
#include "viewer_model.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QCoreApplication::setAttribute(Qt::AA_DontUseNativeMenuBar);
  QApplication::setStyle(QStyleFactory::create("Fusion"));
  s21::MainWindow mainWindow;
  mainWindow.show();
  return a.exec();
}
