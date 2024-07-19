#ifndef SETTINGS_H
#define SETTINGS_H

#include "enums.h"

namespace s21 {

/**
 * @brief The Settings class manages viewer settings such as colors, styles,
 * projection type, and thickness.
 */
class Settings {
 public:
  /**
   * @brief Default constructor.
   */
  Settings();

  /**
   * @brief Destructor (defaulted).
   */
  ~Settings() = default;

  /**
   * @brief Sets the red component of the background color.
   *
   * @param color Red component.
   */
  void setBackgroundColorR(const float color);

  /**
   * @brief Sets the green component of the background color.
   *
   * @param color Green component.
   */
  void setBackgroundColorG(const float color);

  /**
   * @brief Sets the blue component of the background color.
   *
   * @param color Blue component.
   */
  void setBackgroundColorB(const float color);

  /**
   * @brief Sets the red component of the edge color.
   *
   * @param color Red component.
   */
  void setEdgeColorR(const float color);

  /**
   * @brief Sets the green component of the edge color.
   *
   * @param color Green component.
   */
  void setEdgeColorG(const float color);

  /**
   * @brief Sets the blue component of the edge color.
   *
   * @param color Blue component.
   */
  void setEdgeColorB(const float color);

  /**
   * @brief Sets the red component of the vertex color.
   *
   * @param color Red component.
   */
  void setVertexColorR(const float color);

  /**
   * @brief Sets the green component of the vertex color.
   *
   * @param color Green component.
   */
  void setVertexColorG(const float color);

  /**
   * @brief Sets the blue component of the vertex color.
   *
   * @param color Blue component.
   */
  void setVertexColorB(const float color);

  /**
   * @brief Sets the style of rendering edges.
   *
   * @param edgeStyle Edge rendering style (solid, dashed, etc.).
   */
  void setEdgeStyle(const EdgeStyle edgeStyle);

  /**
   * @brief Sets the style of rendering vertices.
   *
   * @param vertexStyle Vertex rendering style (circle, square, etc.).
   */
  void setVertexStyle(const VertexStyle vertexStyle);

  /**
   * @brief Sets the type of projection to be used.
   *
   * @param projectionType Projection type (central, parallel, etc.).
   */
  void setProjectionType(const ProjectionType projectionType);

  /**
   * @brief Sets the thickness of edges.
   *
   * @param thickness Thickness value.
   */
  void setThickness(const float thickness);

  /**
   * @brief Sets the thickness of vertices.
   *
   * @param thicknessOfVertices Thickness value.
   */
  void setThicknessOfVertices(const float thicknessOfVertices);

  /**
   * @brief Gets the red component of the background color.
   *
   * @return Red component.
   */
  float getBackgroundColorR() const;

  /**
   * @brief Gets the green component of the background color.
   *
   * @return Green component.
   */
  float getBackgroundColorG() const;

  /**
   * @brief Gets the blue component of the background color.
   *
   * @return Blue component.
   */
  float getBackgroundColorB() const;

  /**
   * @brief Gets the red component of the edge color.
   *
   * @return Red component.
   */
  float getEdgeColorR() const;

  /**
   * @brief Gets the green component of the edge color.
   *
   * @return Green component.
   */
  float getEdgeColorG() const;

  /**
   * @brief Gets the blue component of the edge color.
   *
   * @return Blue component.
   */
  float getEdgeColorB() const;

  /**
   * @brief Gets the red component of the vertex color.
   *
   * @return Red component.
   */
  float getVertexColorR() const;

  /**
   * @brief Gets the green component of the vertex color.
   *
   * @return Green component.
   */
  float getVertexColorG() const;

  /**
   * @brief Gets the blue component of the vertex color.
   *
   * @return Blue component.
   */
  float getVertexColorB() const;

  /**
   * @brief Gets the style of rendering edges.
   *
   * @return EdgeStyle value.
   */
  EdgeStyle getEdgeStyle() const;

  /**
   * @brief Gets the style of rendering vertices.
   *
   * @return VertexStyle value.
   */
  VertexStyle getVertexStyle() const;

  /**
   * @brief Gets the type of projection used.
   *
   * @return ProjectionType value.
   */
  ProjectionType getProjectionType() const;

  /**
   * @brief Gets the thickness of edges.
   *
   * @return Thickness value.
   */
  float getThickness() const;

  /**
   * @brief Gets the thickness of vertices.
   *
   * @return Thickness value.
   */
  float getThicknessOfVertices() const;

 private:
  float backgroundColorR;         ///< Red component of the background color.
  float backgroundColorG;         ///< Green component of the background color.
  float backgroundColorB;         ///< Blue component of the background color.
  float edgeColorR;               ///< Red component of the edge color.
  float edgeColorG;               ///< Green component of the edge color.
  float edgeColorB;               ///< Blue component of the edge color.
  float vertexColorR;             ///< Red component of the vertex color.
  float vertexColorG;             ///< Green component of the vertex color.
  float vertexColorB;             ///< Blue component of the vertex color.
  EdgeStyle edgeStyle;            ///< Style of rendering edges.
  VertexStyle vertexStyle;        ///< Style of rendering vertices.
  ProjectionType projectionType;  ///< Type of projection.
  float thickness;                ///< Thickness of edges.
  float thicknessOfVertices;      ///< Thickness of vertices.
};

}  // namespace s21

#endif  // SETTINGS_H