#ifndef ENUMS_H
#define ENUMS_H

/**
 * @brief Enum defining different styles for rendering edges.
 */
enum EdgeStyle {
  SOLID,  ///< Solid edge style.
  DASHED  ///< Dashed edge style.
};

/**
 * @brief Enum defining different styles for rendering vertices.
 */
enum VertexStyle {
  CIRCLE,  ///< Circle vertex style.
  SQUARE,  ///< Square vertex style.
  NONE     ///< No vertex style.
};

/**
 * @brief Enum defining different types of projection.
 */
enum ProjectionType {
  CENTRAL,  ///< Central projection type.
  PARALLEL  ///< Parallel projection type.
};

#endif  // ENUMS_H