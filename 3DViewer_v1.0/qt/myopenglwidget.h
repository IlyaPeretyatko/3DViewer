#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#define GL_SILENCE_DEPRECATION
#include <QColor>
#include <QErrorMessage>
#include <QMouseEvent>
#include <QString>

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#include <QOpenGLFunctions_3_3_Compatibility>
#include <QOpenGLWidget>
#else
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#endif

#define RGB_MIN 1.0f
#define RGB_MAX 255.0f

#include "mainwindow.h"
#include "styles.h"

extern "C" {
#include "../s21_viewer.h"
}

enum LineStyle { SOLID, DASHED };

enum VertexStyle { CIRCLE, SQUARE, NONE };

enum ProjectionType { CENTRAL, PARALLEL };

class MyOpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions {
  Q_OBJECT
 public:
  MyOpenGLWidget(QWidget *parent = nullptr);
  ~MyOpenGLWidget();
  char filename[1024];
  data_t *info;
  data_t *buff_info;
  int is_data_parsed = 0;
  QString opengl_filename;
  void from_QStr_to_string(char *filename, QString mainwindow_filename);
  void parse_obj();
  void draw();
  FILE *in;
  double save_move_x, save_move_y, save_move_z, save_scale;
  QColor edgeColor = Qt::white;
  QColor vertexColor = Qt::white;
  LineStyle currentLineStyle;
  VertexStyle currentVertexStyle;
  ProjectionType currentProjectionType;
  float thickness;
  float thickness_of_vertexes;

 protected:
  void initializeGL();
  void paintGL();
  void resizeGL(int width, int height);
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);

 public slots:
  // slots for xyz-rotation slider
  void setXRotation(int angle);
  void setYRotation(int angle);
  void setZRotation(int angle);
  void setBackgroundColor(const QColor &color);
  void setEdgeColor(const QColor &color);
  void setVertexColor(const QColor &color);
  void setLineStyle(LineStyle style);
  void setVertexStyle(VertexStyle style);
  void setProjectionType(ProjectionType type);
  void setThickness(float thick);
  void setThicknessVertexes(float thick);
  QColor getBackgroundColor() const;

 signals:
  // signaling rotation from mouse movement
  void xRotationChanged(int angle);
  void yRotationChanged(int angle);
  void zRotationChanged(int angle);

 private:
  void qColortoRGB(const QColor &C, float &r, float &g, float &b) const;
  float normalize(float val, float min, float max) const;
  int xRot;
  int yRot;
  int zRot;
  QPoint lastPos;
  QColor backgroundColor;
};

#endif  // MYOPENGLWIDGET_H
