#include "myopenglwidget.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent) : QOpenGLWidget{parent} {
  xRot = 0;
  yRot = 0;
  zRot = 0;
}

void MyOpenGLWidget::setController(s21::Controller *controller) {
  this->controller = controller;
}

void MyOpenGLWidget::setIsParsed(bool flag) { this->isParsed = flag; }

void MyOpenGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glLineWidth(3.0f);
}

void MyOpenGLWidget::paintGL() {
  if (isParsed) {
    glClearColor((GLclampf)controller->getBackgroundColorR(),
                 (GLclampf)controller->getBackgroundColorG(),
                 (GLclampf)controller->getBackgroundColorB(), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, 2 * width(), 2 * height());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    draw();
  }
}

void MyOpenGLWidget::resizeGL(int width, int height) {
  int side = qMin(width, height);
  glViewport((width - side) / 2, (height - side) / 2, side, side);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-2, +2, -2, +2, 1.0, 15.0);
  glMatrixMode(GL_MODELVIEW);
}

void MyOpenGLWidget::draw() {
  if (controller->getProjectionType() == 1) {
    glFrustum(-1, 1, -1, 1, 1, 1000.0);
    glTranslatef(0.0, 0.0, -10.0);
  } else {
    glOrtho(-4.0, 4.0, -4.0, 4.0, -100.5, 100.5);
  }
  glLineWidth(controller->getThickness());
  glColor3f(controller->getEdgeColorR(), controller->getEdgeColorG(),
            controller->getEdgeColorB());
  if (controller->getEdgeStyle() == DASHED) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x0101);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }
  glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
  glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
  glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);
  for (int i = 1; i < controller->getCountOfFacets() + 1; ++i) {
    glBegin(GL_POLYGON);
    for (int j = 0;
         j < (controller->getPolygons() + i)->numbersOfVerticesInFacets; ++j) {
      double x = controller->getMatrix()
                     .matrix[(controller->getPolygons() + i)->vertices[j]][0];
      double y = controller->getMatrix()
                     .matrix[(controller->getPolygons() + i)->vertices[j]][1];
      double z = controller->getMatrix()
                     .matrix[(controller->getPolygons() + i)->vertices[j]][2];
      glVertex3f(x, y, z);
    }
    glEnd();
  }
  if (controller->getVertexStyle() == 0) {
    glEnable(GL_POINT_SMOOTH);
  } else if (controller->getVertexStyle() == 1) {
    glDisable(GL_POINT_SMOOTH);
  }
  if (controller->getVertexStyle() == 1 || controller->getVertexStyle() == 0) {
    glColor3f(controller->getVertexColorR(), controller->getVertexColorG(),
              controller->getVertexColorB());
    glPointSize(controller->getThicknessOfVertices());
    glBegin(GL_POINTS);
    for (int i = 1; i < controller->getCountOfFacets() + 1; ++i) {
      for (int j = 0;
           j < (controller->getPolygons() + i)->numbersOfVerticesInFacets;
           ++j) {
        double x = controller->getMatrix()
                       .matrix[(controller->getPolygons() + i)->vertices[j]][0];
        double y = controller->getMatrix()
                       .matrix[(controller->getPolygons() + i)->vertices[j]][1];
        double z = controller->getMatrix()
                       .matrix[(controller->getPolygons() + i)->vertices[j]][2];
        glVertex3f(x, y, z);
      }
    }
    glEnd();
  }
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

void MyOpenGLWidget::setThickness(const double value) {
  s21::EdgesThicknessChange edgesThicknessChange(controller, value);
  commandManager.setCommand(&edgesThicknessChange);
  commandManager.run();
}

void MyOpenGLWidget::setThicknessOfVertices(const double value) {
  s21::VerticesThicknessChange verticesThicknessChange(controller, value);
  commandManager.setCommand(&verticesThicknessChange);
  commandManager.run();
}

void MyOpenGLWidget::setEdgeStyle(const EdgeStyle edgeStyle) {
  s21::EdgesTypeChange edgesTypeChange(controller, edgeStyle);
  commandManager.setCommand(&edgesTypeChange);
  commandManager.run();
}

void MyOpenGLWidget::setVertexStyle(const VertexStyle vertexStyle) {
  s21::VerticesTypeChange verticesTypeChange(controller, vertexStyle);
  commandManager.setCommand(&verticesTypeChange);
  commandManager.run();
}

void MyOpenGLWidget::setProjectionType(const ProjectionType projectionType) {
  s21::ProjectionTypeChange projectionTypeChange(controller, projectionType);
  commandManager.setCommand(&projectionTypeChange);
  commandManager.run();
}

void MyOpenGLWidget::setBackgroundColor(const QColor color) {
  s21::BackgroundColorChange backgroundColorChange(controller, color);
  commandManager.setCommand(&backgroundColorChange);
  commandManager.run();
}

void MyOpenGLWidget::setEdgeColor(const QColor color) {
  s21::EdgesColorChange edgesColorChange(controller, color);
  commandManager.setCommand(&edgesColorChange);
  commandManager.run();
}

void MyOpenGLWidget::setVertexColor(const QColor color) {
  s21::VerticesColorChange verticesColorChange(controller, color);
  commandManager.setCommand(&verticesColorChange);
  commandManager.run();
}
