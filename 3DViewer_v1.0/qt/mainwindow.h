#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qgifimage.h>

#include <QDateTime>
#include <QDebug>
#include <QErrorMessage>
#include <QFileDialog>
#include <QMainWindow>
#include <QSlider>
#include <QString>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  QString mainwindow_filename;
  QString fileNameWithoutPath;

 protected:
  void keyPressEvent(QKeyEvent *event);

 private slots:
  // Movement
  void on_xRotSlider_valueChanged(int value);
  void on_yRotSlider_valueChanged(int value);
  void on_zRotSlider_valueChanged(int value);

  void on_xTransSlider_valueChanged(int value);
  void on_yTransSlider_valueChanged(int value);
  void on_zTransSlider_valueChanged(int value);

  void on_scaleSlider_valueChanged(int value);
  // Buttons
  void openButtonClicked();
  void on_imageButton_clicked();
  void on_gifButton_clicked();

  void make_gif();

  void on_BgColorButton_clicked();

 private:
  Ui::MainWindow *ui;
  QErrorMessage msg;
  QString gif_name;
  QGifImage *gif_frame;
  int frames_counter = 0;
  QTimer *timer;
  QColor bgColor;
  void saveSettings();
};
#endif  // MAINWINDOW_H
