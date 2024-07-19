#include "commands.h"

using namespace s21;

void ProjectionTypeChange::execute() {
  controller->setProjectionType((ProjectionType)index);
}

void EdgesTypeChange::execute() { controller->setEdgeStyle((EdgeStyle)index); }

void VerticesTypeChange::execute() {
  controller->setVertexStyle((VertexStyle)index);
}

void VerticesThicknessChange::execute() {
  controller->setThicknessOfVertices(value);
}

void EdgesThicknessChange::execute() { controller->setThickness(value); }

void BackgroundColorChange::execute() {
  controller->setBackgroundColorR(color.redF());
  controller->setBackgroundColorG(color.greenF());
  controller->setBackgroundColorB(color.blueF());
}

void EdgesColorChange::execute() {
  controller->setEdgeColorR(color.redF());
  controller->setEdgeColorG(color.greenF());
  controller->setEdgeColorB(color.blueF());
}

void VerticesColorChange::execute() {
  controller->setVertexColorR(color.redF());
  controller->setVertexColorG(color.greenF());
  controller->setVertexColorB(color.blueF());
}
