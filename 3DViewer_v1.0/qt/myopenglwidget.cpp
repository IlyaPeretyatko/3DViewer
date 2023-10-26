#include "myopenglwidget.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent) {
  xRot = 0;
  yRot = 0;
  zRot = 0;
}

MyOpenGLWidget::~MyOpenGLWidget() {
  if (is_data_parsed && !in) {
    fclose(in);
    clear_memory(info);
    clear_memory(buff_info);
  }
}

static void qNormalizeAngle(int &angle) {
  while (angle < 0) angle += 360 * 16;
  while (angle > 360) angle -= 360 * 16;
}

void MyOpenGLWidget::setXRotation(int angle) {
  qNormalizeAngle(angle);
  if (angle != xRot) {
    xRot = angle;
    emit xRotationChanged(angle);
    update();
  }
}

void MyOpenGLWidget::setYRotation(int angle) {
  qNormalizeAngle(angle);
  if (angle != yRot) {
    yRot = angle;
    emit yRotationChanged(angle);
    update();
  }
}

void MyOpenGLWidget::setZRotation(int angle) {
  qNormalizeAngle(angle);
  if (angle != zRot) {
    zRot = angle;
    emit zRotationChanged(angle);
    update();
  }
}

void MyOpenGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(
      GL_DEPTH_TEST);  // включает буфер глубины для отображения z-координаты
  glEnable(GL_CULL_FACE);  //  включает отсечение задних граней чтоб они не
                           //  рисовались??
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glLineWidth(3.0f);
  glClearColor(backgroundColor.redF(), backgroundColor.greenF(),
               backgroundColor.blueF(), 1.0f);
}

void MyOpenGLWidget::paintGL() {
  glClearColor(backgroundColor.redF(), backgroundColor.greenF(),
               backgroundColor.blueF(), 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0, 0, 2 * width(), 2 * height());
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (currentProjectionType == 1) {
    glFrustum(-1, 1, -1, 1, 1, 1000.0);
    glTranslatef(0.0, 0.0, -10.0);
  } else {
    glOrtho(-4.0, 4.0, -4.0, 4.0, -100.5, 100.5);
  }

  glLineWidth(thickness);
  glColor3f(edgeColor.redF(), edgeColor.greenF(), edgeColor.blueF());
  if (currentLineStyle == DASHED) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x0101);  // Dashed pattern
  } else {
    glDisable(GL_LINE_STIPPLE);
  }
  glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
  glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
  glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);
  if (is_data_parsed) draw();
  if (currentVertexStyle == 0) {
    glEnable(GL_POINT_SMOOTH);
  } else if (currentVertexStyle == 1) {
    glDisable(GL_POINT_SMOOTH);
  }
  if (is_data_parsed && (currentVertexStyle == 1 || currentVertexStyle == 0)) {
    glColor3f(vertexColor.redF(), vertexColor.greenF(), vertexColor.blueF());
    glPointSize(thickness_of_vertexes);
    glBegin(GL_POINTS);
    for (int i = 1; i < info->count_of_facets + 1; ++i) {
      for (int j = 0; j < info->polygons[i].numbers_of_vertexes_in_facets;
           ++j) {
        double x = info->matrix_3d.matrix[info->polygons[i].vertexes[j]][0];
        double y = info->matrix_3d.matrix[info->polygons[i].vertexes[j]][1];
        double z = info->matrix_3d.matrix[info->polygons[i].vertexes[j]][2];
        glVertex3f(x, y, z);
      }
    }
    glEnd();
  }
}

void MyOpenGLWidget::resizeGL(int width, int height) {
  int side = qMin(width, height);
  glViewport((width - side) / 2, (height - side) / 2, side, side);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
#ifdef QT_OPENGL_ES_1
  glOrthof(-2, +2, -2, +2, 1.0, 15.0);
#else
  glOrtho(-2, +2, -2, +2, 1.0, 15.0);
#endif
  glMatrixMode(GL_MODELVIEW);
}

void MyOpenGLWidget::mousePressEvent(QMouseEvent *event) {
  lastPos = event->pos();
}

void MyOpenGLWidget::mouseMoveEvent(QMouseEvent *event) {
  int dx = event->position().toPoint().x() - lastPos.x();
  int dy = event->position().toPoint().y() - lastPos.y();

  if (event->buttons() & Qt::LeftButton) {
    setXRotation(xRot + 8 * dy);
    setYRotation(yRot + 8 * dx);
  } else if (event->buttons() & Qt::RightButton) {
    setXRotation(xRot + 8 * dy);
    setZRotation(zRot + 8 * dx);
  }
  lastPos = event->pos();
}

void MyOpenGLWidget::parse_obj() {
  from_QStr_to_string(filename, opengl_filename);
  is_data_parsed = 0;
  if (in != NULL) {
    fclose(in);
  }
  if (info != NULL) {
    clear_memory(info);
  }
  if (buff_info != NULL) {
    clear_memory(buff_info);
  }
  in = fopen(filename, "r");
  if (in != NULL) {
    info = (data_t *)calloc(1, sizeof(data_t));
    buff_info = (data_t *)calloc(1, sizeof(data_t));
    if (info == NULL || buff_info == NULL) {
      is_data_parsed = 0;
    } else {
      parsing_obj(in, buff_info);
      if (!create_data_for_copy(info, buff_info)) {
        copy_data(info, buff_info);
        is_data_parsed = 1;
      } else {
        is_data_parsed = 0;
      }
    }
  } else {
    is_data_parsed = 0;
  }
}

void MyOpenGLWidget::draw() {
  for (int i = 1; i < info->count_of_facets + 1; ++i) {
    glBegin(GL_POLYGON);
    for (int j = 0; j < info->polygons[i].numbers_of_vertexes_in_facets; ++j) {
      double x = info->matrix_3d.matrix[info->polygons[i].vertexes[j]][0];
      double y = info->matrix_3d.matrix[info->polygons[i].vertexes[j]][1];
      double z = info->matrix_3d.matrix[info->polygons[i].vertexes[j]][2];
      glVertex3f(x, y, z);
    }
    glEnd();
  }
}

void MyOpenGLWidget::qColortoRGB(const QColor &C, float &r, float &g,
                                 float &b) const {
  r = normalize(C.red(), RGB_MIN, RGB_MAX);
  g = normalize(C.green(), RGB_MIN, RGB_MAX);
  b = normalize(C.blue(), RGB_MIN, RGB_MAX);
}

float MyOpenGLWidget::normalize(float val, float min, float max) const {
  return (val - min) / (max - min);
}

void MyOpenGLWidget::from_QStr_to_string(char *str, QString qstr) {
  for (int i = 0; i < qstr.length(); ++i) {
    str[i] = qstr.toStdString().c_str()[i];
  }
  str[qstr.length()] = '\0';
}

void MyOpenGLWidget::setBackgroundColor(const QColor &color) {
  backgroundColor = color;
  update();
}

void MyOpenGLWidget::setEdgeColor(const QColor &color) {
  edgeColor = color;
  update();
}

void MyOpenGLWidget::setLineStyle(LineStyle style) {
  currentLineStyle = style;
  update();
}

void MyOpenGLWidget::setThickness(float thick) {
  thickness = thick;
  update();
}

QColor MyOpenGLWidget::getBackgroundColor() const { return backgroundColor; }

void MyOpenGLWidget::setVertexStyle(VertexStyle style) {
  currentVertexStyle = style;
  update();
}

void MyOpenGLWidget::setVertexColor(const QColor &color) {
  vertexColor = color;
  update();
}

void MyOpenGLWidget::setThicknessVertexes(float thick) {
  thickness_of_vertexes = thick;
  update();
}

void MyOpenGLWidget::setProjectionType(ProjectionType type) {
  currentProjectionType = type;
  repaint();
}
