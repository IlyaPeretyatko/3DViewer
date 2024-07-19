#include "settings.h"

using namespace s21;

Settings::Settings() {
  backgroundColorR = 0;
  backgroundColorG = 0;
  backgroundColorB = 0;
  edgeColorR = 255;
  edgeColorG = 255;
  edgeColorB = 255;
  vertexColorR = 255;
  vertexColorG = 255;
  vertexColorB = 255;
  edgeStyle = SOLID;
  vertexStyle = NONE;
  projectionType = CENTRAL;
  thickness = 1;
  thicknessOfVertices = 1;
}

void Settings::setBackgroundColorR(const float color) {
  this->backgroundColorR = color;
}

void Settings::setBackgroundColorG(const float color) {
  this->backgroundColorG = color;
}

void Settings::setBackgroundColorB(const float color) {
  this->backgroundColorB = color;
}

void Settings::setEdgeColorR(const float color) { this->edgeColorR = color; }

void Settings::setEdgeColorG(const float color) { this->edgeColorG = color; }

void Settings::setEdgeColorB(const float color) { this->edgeColorB = color; }

void Settings::setVertexColorR(const float color) {
  this->vertexColorR = color;
}

void Settings::setVertexColorG(const float color) {
  this->vertexColorG = color;
}

void Settings::setVertexColorB(const float color) {
  this->vertexColorB = color;
}

void Settings::setEdgeStyle(const EdgeStyle edgeStyle) {
  this->edgeStyle = edgeStyle;
}

void Settings::setVertexStyle(const VertexStyle vertexStyle) {
  this->vertexStyle = vertexStyle;
}

void Settings::setProjectionType(const ProjectionType projectionType) {
  this->projectionType = projectionType;
}

void Settings::setThickness(const float thickness) {
  this->thickness = thickness;
}

void Settings::setThicknessOfVertices(const float thicknessOfVertices) {
  this->thicknessOfVertices = thicknessOfVertices;
}

float Settings::getBackgroundColorR() const { return backgroundColorR; }

float Settings::getBackgroundColorG() const { return backgroundColorG; }

float Settings::getBackgroundColorB() const { return backgroundColorB; }

float Settings::getEdgeColorR() const { return edgeColorR; }

float Settings::getEdgeColorG() const { return edgeColorG; }

float Settings::getEdgeColorB() const { return edgeColorB; }

float Settings::getVertexColorR() const { return vertexColorR; }

float Settings::getVertexColorG() const { return vertexColorG; }

float Settings::getVertexColorB() const { return vertexColorB; }

EdgeStyle Settings::getEdgeStyle() const { return edgeStyle; }

VertexStyle Settings::getVertexStyle() const { return vertexStyle; }

ProjectionType Settings::getProjectionType() const { return projectionType; }

float Settings::getThickness() const { return thickness; }

float Settings::getThicknessOfVertices() const { return thicknessOfVertices; }
