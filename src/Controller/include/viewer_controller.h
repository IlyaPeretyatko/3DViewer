#ifndef SRC_CONTROLLER_VIEWER_CONTROLLER_H
#define SRC_CONTROLLER_VIEWER_CONTROLLER_H

#include "enums.h"
#include "settings.h"
#include "viewer_model.h"

namespace s21 {

/**
 * @brief The Controller class manages the viewer for OBJ files.
 *
 * This class handles setting up the model, managing transformations and
 * settings, and providing access to various properties and configurations for
 * rendering.
 */
class Controller {
 public:
  /**
   * @brief Default constructor.
   */
  Controller();

  /**
   * @brief Destructor.
   */
  ~Controller();

  /**
   * @brief Sets the model to be used for rendering.
   */
  void setModel() const;

  /**
   * @brief Gets the count of vertices in the model.
   *
   * @return The number of vertices.
   */
  int getCountOfVertices();

  /**
   * @brief Gets the count of facets (polygons) in the model.
   *
   * @return The number of facets.
   */
  int getCountOfFacets();

  /**
   * @brief Gets the transformation matrix of the model.
   *
   * @return The transformation matrix.
   */
  matrix_t getMatrix();

  /**
   * @brief Gets the array of polygons (facets) in the model.
   *
   * @return Pointer to the array of polygons.
   */
  polygon_t *getPolygons();

  /**
   * @brief Parses an OBJ file and runs the parsing process.
   *
   * @param in File pointer to the input OBJ file.
   */
  void runParsingObj(FILE *in) const;

  /**
   * @brief Sets the translation along the X axis.
   *
   * @param a Translation distance.
   */
  void setMoveX(const double &a);

  /**
   * @brief Sets the translation along the Y axis.
   *
   * @param a Translation distance.
   */
  void setMoveY(const double &a);

  /**
   * @brief Sets the translation along the Z axis.
   *
   * @param a Translation distance.
   */
  void setMoveZ(const double &a);

  /**
   * @brief Sets the rotation around the X axis.
   *
   * @param angle Rotation angle in degrees.
   */
  void setRotationByOx(const double &angle);

  /**
   * @brief Sets the rotation around the Y axis.
   *
   * @param angle Rotation angle in degrees.
   */
  void setRotationByOy(const double &angle);

  /**
   * @brief Sets the rotation around the Z axis.
   *
   * @param angle Rotation angle in degrees.
   */
  void setRotationByOz(const double &angle);

  /**
   * @brief Sets the scaling factor.
   *
   * @param x Scaling factor.
   */
  void setScaling(const double &x);

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
   * @param vertexStyle Vertex rendering style (point, sphere, etc.).
   */
  void setVertexStyle(const VertexStyle vertexStyle);

  /**
   * @brief Sets the type of projection to be used.
   *
   * @param projectionType Projection type (orthographic, perspective, etc.).
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
  Model *model;              ///< Pointer to the main Model object.
  Model *modelForTransform;  ///< Pointer to the Model object used for
                             ///< transformations.
  Settings settings;         ///< Object containing viewer settings.
};

}  // namespace s21

#endif  // SRC_CONTROLLER_VIEWER_CONTROLLER_H