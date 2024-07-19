#include "strategies.h"

using namespace s21;

void RotateX::transform(float value) {
  controller->setRotationByOx(value * M_PI / 180.0f);
}

void RotateY::transform(float value) {
  controller->setRotationByOy(value * M_PI / 180.0f);
}

void RotateZ::transform(float value) {
  controller->setRotationByOz(value * M_PI / 180.0f);
}

void Scale::transform(float value) {
  if (value) {
    if (value < 0) {
      value *= -1;
      value = 1 / value;
    }
    controller->setScaling(value);
  }
}

void TranslationX::transform(float value) { controller->setMoveX(value / 20); }

void TranslationY::transform(float value) { controller->setMoveY(value / 20); }

void TranslationZ::transform(float value) { controller->setMoveZ(value / 20); }
