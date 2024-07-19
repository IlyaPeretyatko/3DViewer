#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qgifimage.h>

#include <QColorDialog>
#include <QErrorMessage>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>
#include <QTimer>

#include "strategies.h"
#include "strategy.h"
#include "viewer_controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {

/**
 * @brief The MainWindow class represents the main application window for the
 * OBJ viewer.
 */
class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  /**
   * @brief Constructor for MainWindow.
   *
   * @param parent Pointer to the parent widget (default is nullptr).
   */
  MainWindow(QWidget *parent = nullptr);

  /**
   * @brief Destructor for MainWindow.
   */
  ~MainWindow();

 private slots:
  void on_openButton_clicked();
  void on_scaleSlider_valueChanged(int value);
  void on_xTransSlider_valueChanged(int value);
  void on_yTransSlider_valueChanged(int value);
  void on_zTransSlider_valueChanged(int value);
  void on_xRotSlider_valueChanged(int value);
  void on_yRotSlider_valueChanged(int value);
  void on_zRotSlider_valueChanged(int value);
  void on_edgeThickness_valueChanged(int value);
  void on_vertexThickness_valueChanged(int value);
  void on_solidButton_toggled(bool checked);
  void on_dashButton_toggled(bool checked);
  void on_circleButton_toggled(bool checked);
  void on_squareButton_toggled(bool checked);
  void on_noneButton_toggled(bool checked);
  void on_BgColorButton_clicked();
  void on_vertexColor_clicked();
  void on_edgeColor_clicked();
  void on_centralButton_toggled(bool checked);
  void on_parallelButton_toggled(bool checked);
  void on_imageButton_clicked();
  void on_gifButton_clicked();
  void makeGif();

 private:
  Ui::MainWindow *ui;           ///< Pointer to the UI object.
  s21::Controller *controller;  ///< Pointer to the viewer controller.
  s21::ContextStrategy
      contextStrategy;  ///< Strategy context for viewer strategies.
  QErrorMessage msg;    ///< Error message handler.
  bool isParsed;        ///< Flag indicating if OBJ file is parsed.
  QString gifName;      ///< Name of the GIF file.
  QGifImage *gifFrame;  ///< GIF image frame.
  int framesCounter;    ///< Counter for frames in GIF.
  QTimer *timer;        ///< Timer for GIF creation.

  /**
   * @brief Parses an OBJ file and initializes the viewer.
   *
   * @param filename Path to the OBJ file.
   */
  void parseObj(const QString filename);

  /**
   * @brief Resets viewer settings to default.
   */
  void resetSettings() const;

  /**
   * @brief Converts QString to C-string.
   *
   * @param str Pointer to a C-string buffer.
   * @param qstr QString to convert.
   */
  void fromQStrToString(char *str, const QString qstr) const;

  /**
   * @brief Saves current viewer settings.
   */
  void saveSettings() const;
};

}  // namespace s21

#endif  // MAINWINDOW_H