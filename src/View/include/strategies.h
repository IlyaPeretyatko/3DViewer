#ifndef STRATEGIES_H
#define STRATEGIES_H

#include "strategy.h"
#include "viewer_controller.h"

namespace s21 {

/**
 * @brief Strategy for rotating around the X axis.
 */
class RotateX : public TransformStrategy {
 public:
  /**
   * @brief Constructor for RotateX strategy.
   *
   * @param c Pointer to the controller managing transformations.
   */
  RotateX(Controller *c) : controller(c) {}

  /**
   * @brief Applies rotation around the X axis.
   *
   * @param value Angle of rotation.
   */
  void transform(float value) override;

 private:
  Controller *controller;  ///< Pointer to the controller.
};

/**
 * @brief Strategy for rotating around the Y axis.
 */
class RotateY : public TransformStrategy {
 public:
  /**
   * @brief Constructor for RotateY strategy.
   *
   * @param c Pointer to the controller managing transformations.
   */
  RotateY(Controller *c) : controller(c) {}

  /**
   * @brief Applies rotation around the Y axis.
   *
   * @param value Angle of rotation.
   */
  void transform(float value) override;

 private:
  Controller *controller;  ///< Pointer to the controller.
};

/**
 * @brief Strategy for rotating around the Z axis.
 */
class RotateZ : public TransformStrategy {
 public:
  /**
   * @brief Constructor for RotateZ strategy.
   *
   * @param c Pointer to the controller managing transformations.
   */
  RotateZ(Controller *c) : controller(c) {}

  /**
   * @brief Applies rotation around the Z axis.
   *
   * @param value Angle of rotation.
   */
  void transform(float value) override;

 private:
  Controller *controller;  ///< Pointer to the controller.
};

/**
 * @brief Strategy for scaling.
 */
class Scale : public TransformStrategy {
 public:
  /**
   * @brief Constructor for Scale strategy.
   *
   * @param c Pointer to the controller managing transformations.
   */
  Scale(Controller *c) : controller(c) {}

  /**
   * @brief Applies scaling transformation.
   *
   * @param value Scaling factor.
   */
  void transform(float value) override;

 private:
  Controller *controller;  ///< Pointer to the controller.
};

/**
 * @brief Strategy for translating along the X axis.
 */
class TranslationX : public TransformStrategy {
 public:
  /**
   * @brief Constructor for TranslationX strategy.
   *
   * @param c Pointer to the controller managing transformations.
   */
  TranslationX(Controller *c) : controller(c) {}

  /**
   * @brief Applies translation along the X axis.
   *
   * @param value Translation amount.
   */
  void transform(float value) override;

 private:
  Controller *controller;  ///< Pointer to the controller.
};

/**
 * @brief Strategy for translating along the Y axis.
 */
class TranslationY : public TransformStrategy {
 public:
  /**
   * @brief Constructor for TranslationY strategy.
   *
   * @param c Pointer to the controller managing transformations.
   */
  TranslationY(Controller *c) : controller(c) {}

  /**
   * @brief Applies translation along the Y axis.
   *
   * @param value Translation amount.
   */
  void transform(float value) override;

 private:
  Controller *controller;  ///< Pointer to the controller.
};

/**
 * @brief Strategy for translating along the Z axis.
 */
class TranslationZ : public TransformStrategy {
 public:
  /**
   * @brief Constructor for TranslationZ strategy.
   *
   * @param c Pointer to the controller managing transformations.
   */
  TranslationZ(Controller *c) : controller(c) {}

  /**
   * @brief Applies translation along the Z axis.
   *
   * @param value Translation amount.
   */
  void transform(float value) override;

 private:
  Controller *controller;  ///< Pointer to the controller.
};

}  // namespace s21

#endif  // STRATEGIES_H