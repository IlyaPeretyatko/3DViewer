#ifndef SRC_MODEL_VIEWER_MODEL_H
#define SRC_MODEL_VIEWER_MODEL_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

/**
 * @brief Structure representing a matrix.
 */
typedef struct matrix {
  double **matrix = nullptr;  ///< 2D array representing the matrix.
  int rows;                   ///< Number of rows in the matrix.
  int columns;                ///< Number of columns in the matrix.
} matrix_t;

/**
 * @brief Structure representing a polygon (facets).
 */
typedef struct facets {
  int *vertices;                  ///< Array of vertex indices in the polygon.
  int numbersOfVerticesInFacets;  ///< Number of vertices in the polygon.
} polygon_t;

namespace s21 {

/**
 * @brief The Model class represents a 3D model and provides methods for
 * manipulating it.
 */
class Model {
 public:
  /**
   * @brief Default constructor.
   */
  Model() = default;

  /**
   * @brief Destructor.
   */
  ~Model();

  /**
   * @brief Gets the count of vertices in the model.
   *
   * @return Number of vertices.
   */
  int getCountOfVertices() const;

  /**
   * @brief Gets the count of facets (polygons) in the model.
   *
   * @return Number of facets.
   */
  int getCountOfFacets() const;

  /**
   * @brief Gets the 3D transformation matrix of the model.
   *
   * @return 3D transformation matrix.
   */
  matrix_t getMatrix_3d() const;

  /**
   * @brief Gets the array of polygons (facets) in the model.
   *
   * @return Pointer to the array of polygons.
   */
  polygon_t *getPolygons() const;

  /**
   * @brief Parses an OBJ file to populate the model.
   *
   * @param in File pointer to the input OBJ file.
   */
  void parsingObj(FILE *in);

  /**
   * @brief Clears the model data.
   */
  void clear();

  /**
   * @brief Creates data for copying from another Model object.
   *
   * @param model Reference to the Model object to copy from.
   */
  void createDataForCopy(const Model &model);

  /**
   * @brief Copies data from another Model object.
   *
   * @param model Reference to the Model object to copy from.
   */
  void copyData(const Model &model);

  /**
   * @brief Moves the model along the X axis.
   *
   * @param a Distance to move.
   */
  void moveX(const double &a);

  /**
   * @brief Moves the model along the Y axis.
   *
   * @param a Distance to move.
   */
  void moveY(const double &a);

  /**
   * @brief Moves the model along the Z axis.
   *
   * @param a Distance to move.
   */
  void moveZ(const double &a);

  /**
   * @brief Rotates the model around the X axis.
   *
   * @param angle Rotation angle in degrees.
   */
  void rotationByOx(const double &angle);

  /**
   * @brief Rotates the model around the Y axis.
   *
   * @param angle Rotation angle in degrees.
   */
  void rotationByOy(const double &angle);

  /**
   * @brief Rotates the model around the Z axis.
   *
   * @param angle Rotation angle in degrees.
   */
  void rotationByOz(const double &angle);

  /**
   * @brief Scales the model.
   *
   * @param x Scaling factor.
   */
  void scaling(const double &x);

 private:
  int countOfVertices;            ///< Number of vertices in the model.
  int countOfFacets;              ///< Number of facets (polygons) in the model.
  matrix_t matrix_3d;             ///< 3D transformation matrix of the model.
  polygon_t *polygons = nullptr;  ///< Array of polygons (facets) in the model.

  /**
   * @brief Helper function to count vertices and facets in an OBJ file.
   *
   * @param in File pointer to the input OBJ file.
   */
  void getCountOfVerticesAndFacets(FILE *in);

  /**
   * @brief Utility function to parse and retrieve vertices and polygons from an
   * OBJ file.
   *
   * @param in File pointer to the OBJ file.
   */
  void getValueOfVerticesAndPolygons(FILE *in);

  /**
   * @brief Helper function to extract vertex indices of polygons from an OBJ
   * file line.
   *
   * @param line Pointer to the line containing polygon vertex indices.
   * @param index Index of the current polygon.
   */
  void getVerticesOfPolygons(const char *line, const int &index);

  /**
   * @brief Creates a matrix of specified dimensions.
   *
   * @param rows Number of rows.
   * @param columns Number of columns.
   */
  void createMatrix(const int &rows, const int &columns);

  /**
   * @brief Deletes the dynamically allocated matrix.
   */
  void deleteMatrix();

  /**
   * @brief Calculates the number of vertices in polygons from an OBJ file line.
   *
   * @param line Pointer to the line containing polygon vertex indices.
   * @return Number of vertices in the polygon.
   */
  int calcCountOfVerticesInPolygons(const char *line) const;
};

}  // namespace s21

#endif  // SRC_MODEL_VIEWER_MODEL_H