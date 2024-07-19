#include "viewer_controller.h"

using namespace s21;

Controller::Controller() : model(new Model()), modelForTransform(new Model()) {}

Controller::~Controller() {
  if (model != nullptr) delete model;
  if (modelForTransform != nullptr) delete modelForTransform;
}

void Controller::setModel() const {
  model->clear();
  modelForTransform->clear();
}

void Controller::setMoveX(const double& a) {
  modelForTransform->copyData(*model);
  modelForTransform->moveX(a);
}

void Controller::setMoveY(const double& a) {
  modelForTransform->copyData(*model);
  modelForTransform->moveY(a);
}

void Controller::setMoveZ(const double& a) {
  modelForTransform->copyData(*model);
  modelForTransform->moveZ(a);
}

void Controller::setRotationByOx(const double& angle) {
  modelForTransform->copyData(*model);
  modelForTransform->rotationByOx(angle);
}

void Controller::setRotationByOy(const double& angle) {
  modelForTransform->copyData(*model);
  modelForTransform->rotationByOy(angle);
}

void Controller::setRotationByOz(const double& angle) {
  modelForTransform->copyData(*model);
  modelForTransform->rotationByOz(angle);
}

void Controller::setScaling(const double& x) {
  modelForTransform->copyData(*model);
  modelForTransform->scaling(x);
}

void Controller::runParsingObj(FILE* in) const {
  model->parsingObj(in);
  modelForTransform->createDataForCopy(*model);
  modelForTransform->copyData(*model);
}

int Controller::getCountOfVertices() {
  return modelForTransform->getCountOfVertices();
}

int Controller::getCountOfFacets() {
  return modelForTransform->getCountOfFacets();
}

matrix_t Controller::getMatrix() { return modelForTransform->getMatrix_3d(); }

polygon_t* Controller::getPolygons() {
  return modelForTransform->getPolygons();
}

void Controller::setBackgroundColorR(const float color) {
  settings.setBackgroundColorR(color);
}

void Controller::setBackgroundColorG(const float color) {
  settings.setBackgroundColorG(color);
}

void Controller::setBackgroundColorB(const float color) {
  settings.setBackgroundColorB(color);
}

void Controller::setEdgeColorR(const float color) {
  settings.setEdgeColorR(color);
}

void Controller::setEdgeColorG(const float color) {
  settings.setEdgeColorG(color);
}

void Controller::setEdgeColorB(const float color) {
  settings.setEdgeColorB(color);
}

void Controller::setVertexColorR(const float color) {
  settings.setVertexColorR(color);
}

void Controller::setVertexColorG(const float color) {
  settings.setVertexColorG(color);
}

void Controller::setVertexColorB(const float color) {
  settings.setVertexColorB(color);
}

void Controller::setEdgeStyle(const EdgeStyle edgeStyle) {
  settings.setEdgeStyle(edgeStyle);
}

void Controller::setVertexStyle(const VertexStyle vertexStyle) {
  settings.setVertexStyle(vertexStyle);
}

void Controller::setProjectionType(const ProjectionType projectionType) {
  settings.setProjectionType(projectionType);
}

void Controller::setThickness(const float thickness) {
  settings.setThickness(thickness);
}

void Controller::setThicknessOfVertices(const float thicknessOfVertices) {
  settings.setThicknessOfVertices(thicknessOfVertices);
}

float Controller::getBackgroundColorR() const {
  return settings.getBackgroundColorR();
}

float Controller::getBackgroundColorG() const {
  return settings.getBackgroundColorG();
}

float Controller::getBackgroundColorB() const {
  return settings.getBackgroundColorB();
}

float Controller::getEdgeColorR() const { return settings.getEdgeColorR(); }

float Controller::getEdgeColorG() const { return settings.getEdgeColorG(); }

float Controller::getEdgeColorB() const { return settings.getEdgeColorB(); }

float Controller::getVertexColorR() const { return settings.getVertexColorR(); }

float Controller::getVertexColorG() const { return settings.getVertexColorG(); }

float Controller::getVertexColorB() const { return settings.getVertexColorB(); }

EdgeStyle Controller::getEdgeStyle() const { return settings.getEdgeStyle(); }

VertexStyle Controller::getVertexStyle() const {
  return settings.getVertexStyle();
}

ProjectionType Controller::getProjectionType() const {
  return settings.getProjectionType();
}

float Controller::getThickness() const { return settings.getThickness(); }

float Controller::getThicknessOfVertices() const {
  return settings.getThicknessOfVertices();
}
