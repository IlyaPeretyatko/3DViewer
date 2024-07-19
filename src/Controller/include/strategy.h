#ifndef SRC_CONTROLLER_STRATEGY_COMMAND_H_
#define SRC_CONTROLLER_STRATEGY_COMMAND_H_

/**
 * @brief The TransformStrategy class defines an interface for transforming a
 * float value.
 *
 * Subclasses of TransformStrategy implement specific transformation strategies.
 */
class TransformStrategy {
 public:
  /**
   * @brief Virtual destructor (defaulted).
   */
  virtual ~TransformStrategy() = default;

  /**
   * @brief Virtual function to transform a float value.
   *
   * Subclasses must implement this method to define the transformation logic.
   *
   * @param value The float value to be transformed.
   */
  virtual void transform(float value) = 0;
};

namespace s21 {

/**
 * @brief The ContextStrategy class manages a TransformStrategy and uses it to
 * transform values.
 *
 * This class allows dynamically changing the strategy used for transformation.
 */
class ContextStrategy {
 public:
  /**
   * @brief Default constructor.
   */
  ContextStrategy() = default;

  /**
   * @brief Constructor that initializes the strategy.
   *
   * @param s Pointer to a TransformStrategy object.
   */
  ContextStrategy(TransformStrategy *s) : strategy(s) {}

  /**
   * @brief Sets the strategy to be used for transformation.
   *
   * @param s Pointer to a TransformStrategy object.
   */
  void setStrategy(TransformStrategy *s);

  /**
   * @brief Transforms a float value using the current strategy.
   *
   * @param value The float value to be transformed.
   */
  void transform(float value);

 private:
  TransformStrategy
      *strategy;  ///< Pointer to the current TransformStrategy object.
};

}  // namespace s21

#endif  // SRC_CONTROLLER_STRATEGY_COMMAND_H_