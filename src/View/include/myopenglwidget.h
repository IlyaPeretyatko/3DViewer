#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#define GL_SILENCE_DEPRECATION
#include <QColor>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>

#include "command.h"
#include "commands.h"
#include "enums.h"
#include "viewer_controller.h"

/**
 * @brief The MyOpenGLWidget class provides a custom OpenGL widget for rendering
 * and interaction.
 */
class MyOpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions {
  Q_OBJECT
 public:
  /**
   * @brief Constructor for MyOpenGLWidget.
   *
   * @param parent Pointer to the parent widget (default is nullptr).
   */
  MyOpenGLWidget(QWidget *parent = nullptr);

  /**
   * @brief Sets the controller for interacting with the viewer.
   *
   * @param controller Pointer to the viewer controller.
   */
  void setController(s21::Controller *controller);

  /**
   * @brief Sets the flag indicating if an OBJ file is parsed.
   *
   * @param flag Boolean flag indicating parsed status.
   */
  void setIsParsed(const bool flag);

  /**
   * @brief Sets the thickness value for rendering edges.
   *
   * @param value Thickness value for edges.
   */
  void setThickness(const double value);

  /**
   * @brief Sets the thickness value for rendering vertices.
   *
   * @param value Thickness value for vertices.
   */
  void setThicknessOfVertices(const double value);

  /**
   * @brief Sets the edge style for rendering edges.
   *
   * @param edgeStyle Enum value representing the edge style.
   */
  void setEdgeStyle(const EdgeStyle edgeStyle);

  /**
   * @brief Sets the vertex style for rendering vertices.
   *
   * @param vertexStyle Enum value representing the vertex style.
   */
  void setVertexStyle(const VertexStyle vertexStyle);

  /**
   * @brief Sets the projection type for rendering.
   *
   * @param projectionType Enum value representing the projection type.
   */
  void setProjectionType(const ProjectionType projectionType);

  /**
   * @brief Sets the background color for rendering.
   *
   * @param color QColor object representing the background color.
   */
  void setBackgroundColor(const QColor color);

  /**
   * @brief Sets the edge color for rendering.
   *
   * @param color QColor object representing the edge color.
   */
  void setEdgeColor(const QColor color);

  /**
   * @brief Sets the vertex color for rendering.
   *
   * @param color QColor object representing the vertex color.
   */
  void setVertexColor(const QColor color);

 public slots:
  /**
   * @brief Slot to set the X rotation angle.
   *
   * @param angle New X rotation angle.
   */
  void setXRotation(int angle);

  /**
   * @brief Slot to set the Y rotation angle.
   *
   * @param angle New Y rotation angle.
   */
  void setYRotation(int angle);

  /**
   * @brief Slot to set the Z rotation angle.
   *
   * @param angle New Z rotation angle.
   */
  void setZRotation(int angle);

 signals:
  /**
   * @brief Signal emitted when the X rotation angle changes.
   *
   * @param angle New X rotation angle.
   */
  void xRotationChanged(int angle);

  /**
   * @brief Signal emitted when the Y rotation angle changes.
   *
   * @param angle New Y rotation angle.
   */
  void yRotationChanged(int angle);

  /**
   * @brief Signal emitted when the Z rotation angle changes.
   *
   * @param angle New Z rotation angle.
   */
  void zRotationChanged(int angle);

 protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int width, int height) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;

 private:
  s21::Controller *controller;  ///< Pointer to the viewer controller.
  s21::CommandManager
      commandManager;  ///< Command manager for executing viewer commands.
  bool isParsed;       ///< Flag indicating if an OBJ file is parsed.
  int xRot;            ///< X rotation angle.
  int yRot;            ///< Y rotation angle.
  int zRot;            ///< Z rotation angle.
  QPoint lastPos;      ///< Last mouse position for rotation calculations.

  /**
   * @brief Draws the OpenGL scene.
   */
  void draw();
};

#endif  // MYOPENGLWIDGET_H