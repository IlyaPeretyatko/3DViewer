#include "strategy.h"

using namespace s21;

void ContextStrategy::setStrategy(TransformStrategy *s) { strategy = s; }

void ContextStrategy::transform(float value) {
  if (strategy != nullptr) strategy->transform(value);
}
