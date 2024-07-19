#ifndef COMMANDS_H
#define COMMANDS_H

#include <QColor>

#include "command.h"
#include "viewer_controller.h"

namespace s21 {

/**
 * @brief Command to change the projection type in the viewer controller.
 */
class ProjectionTypeChange : public Command {
 public:
  /**
   * @brief Constructor.
   *
   * @param controller Pointer to the viewer controller.
   * @param index Index indicating the new projection type.
   */
  ProjectionTypeChange(Controller *controller, int index)
      : controller(controller), index(index){};

  /**
   * @brief Executes the projection type change command.
   */
  virtual void execute();

 private:
  Controller *controller;  ///< Pointer to the viewer controller.
  int index;               ///< Index indicating the new projection type.
};

/**
 * @brief Command to change the edges type in the viewer controller.
 */
class EdgesTypeChange : public Command {
 public:
  /**
   * @brief Constructor.
   *
   * @param controller Pointer to the viewer controller.
   * @param index Index indicating the new edges type.
   */
  EdgesTypeChange(Controller *controller, int index)
      : controller(controller), index(index){};

  /**
   * @brief Executes the edges type change command.
   */
  virtual void execute();

 private:
  Controller *controller;  ///< Pointer to the viewer controller.
  int index;               ///< Index indicating the new edges type.
};

/**
 * @brief Command to change the vertices type in the viewer controller.
 */
class VerticesTypeChange : public Command {
 public:
  /**
   * @brief Constructor.
   *
   * @param controller Pointer to the viewer controller.
   * @param index Index indicating the new vertices type.
   */
  VerticesTypeChange(Controller *controller, int index)
      : controller(controller), index(index){};

  /**
   * @brief Executes the vertices type change command.
   */
  virtual void execute();

 private:
  Controller *controller;  ///< Pointer to the viewer controller.
  int index;               ///< Index indicating the new vertices type.
};

/**
 * @brief Command to change the thickness of vertices in the viewer controller.
 */
class VerticesThicknessChange : public Command {
 public:
  /**
   * @brief Constructor.
   *
   * @param controller Pointer to the viewer controller.
   * @param value New thickness value for vertices.
   */
  VerticesThicknessChange(Controller *controller, double value)
      : controller(controller), value(value){};

  /**
   * @brief Executes the vertices thickness change command.
   */
  virtual void execute();

 private:
  Controller *controller;  ///< Pointer to the viewer controller.
  double value;            ///< New thickness value for vertices.
};

/**
 * @brief Command to change the thickness of edges in the viewer controller.
 */
class EdgesThicknessChange : public Command {
 public:
  /**
   * @brief Constructor.
   *
   * @param controller Pointer to the viewer controller.
   * @param value New thickness value for edges.
   */
  EdgesThicknessChange(Controller *controller, double value)
      : controller(controller), value(value){};

  /**
   * @brief Executes the edges thickness change command.
   */
  virtual void execute();

 private:
  Controller *controller;  ///< Pointer to the viewer controller.
  double value;            ///< New thickness value for edges.
};

/**
 * @brief Command to change the background color in the viewer controller.
 */
class BackgroundColorChange : public Command {
 public:
  /**
   * @brief Constructor.
   *
   * @param controller Pointer to the viewer controller.
   * @param color New background color.
   */
  BackgroundColorChange(Controller *controller, QColor color)
      : controller(controller), color(color){};

  /**
   * @brief Executes the background color change command.
   */
  virtual void execute();

 private:
  Controller *controller;  ///< Pointer to the viewer controller.
  QColor color;            ///< New background color.
};

/**
 * @brief Command to change the color of edges in the viewer controller.
 */
class EdgesColorChange : public Command {
 public:
  /**
   * @brief Constructor.
   *
   * @param controller Pointer to the viewer controller.
   * @param color New color for edges.
   */
  EdgesColorChange(Controller *controller, QColor color)
      : controller(controller), color(color){};

  /**
   * @brief Executes the edges color change command.
   */
  virtual void execute();

 private:
  Controller *controller;  ///< Pointer to the viewer controller.
  QColor color;            ///< New color for edges.
};

/**
 * @brief Command to change the color of vertices in the viewer controller.
 */
class VerticesColorChange : public Command {
 public:
  /**
   * @brief Constructor.
   *
   * @param controller Pointer to the viewer controller.
   * @param color New color for vertices.
   */
  VerticesColorChange(Controller *controller, QColor color)
      : controller(controller), color(color){};

  /**
   * @brief Executes the vertices color change command.
   */
  virtual void execute();

 private:
  Controller *controller;  ///< Pointer to the viewer controller.
  QColor color;            ///< New color for vertices.
};

}  // namespace s21

#endif  // COMMANDS_H
