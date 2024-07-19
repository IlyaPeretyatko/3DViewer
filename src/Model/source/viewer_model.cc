#include "viewer_model.h"

using namespace s21;

// destructor

Model::~Model() { clear(); }

void Model::clear() {
  if (polygons != nullptr) {
    for (int i = 1; i < countOfFacets + 1; ++i) {
      if (polygons[i].vertices != nullptr) {
        delete[] polygons[i].vertices;
      }
    }
    delete[] polygons;
  }
  deleteMatrix();
}

// get

int Model::getCountOfVertices() const { return this->countOfVertices; }

int Model::getCountOfFacets() const { return this->countOfFacets; }

matrix_t Model::getMatrix_3d() const { return this->matrix_3d; }

polygon_t *Model::getPolygons() const { return this->polygons; }

// afine transformation
void Model::moveX(const double &a) {
  for (int i = 0; i < matrix_3d.rows; i++) matrix_3d.matrix[i][0] += a;
}

void Model::moveY(const double &a) {
  for (int i = 0; i < matrix_3d.rows; i++) matrix_3d.matrix[i][1] += a;
}

void Model::moveZ(const double &a) {
  for (int i = 0; i < matrix_3d.rows; i++) matrix_3d.matrix[i][2] += a;
}

void Model::rotationByOx(const double &angle) {
  for (int i = 0; i < matrix_3d.rows; i++) {
    double temp_y = matrix_3d.matrix[i][1];
    double temp_z = matrix_3d.matrix[i][2];
    matrix_3d.matrix[i][1] = cos(angle) * temp_y - sin(angle) * temp_z;
    matrix_3d.matrix[i][2] = sin(angle) * temp_y + cos(angle) * temp_z;
  }
}

void Model::rotationByOy(const double &angle) {
  for (int i = 0; i < matrix_3d.rows; i++) {
    double temp_x = matrix_3d.matrix[i][0];
    double temp_z = matrix_3d.matrix[i][2];
    matrix_3d.matrix[i][0] = cos(angle) * temp_x + sin(angle) * temp_z;
    matrix_3d.matrix[i][2] = -sin(angle) * temp_x + cos(angle) * temp_z;
  }
}

void Model::rotationByOz(const double &angle) {
  for (int i = 0; i < matrix_3d.rows; i++) {
    double temp_x = matrix_3d.matrix[i][0];
    double temp_y = matrix_3d.matrix[i][1];
    matrix_3d.matrix[i][0] = cos(angle) * temp_x - sin(angle) * temp_y;
    matrix_3d.matrix[i][1] = sin(angle) * temp_x + cos(angle) * temp_y;
  }
}

void Model::scaling(const double &x) {
  for (int i = 0; i < matrix_3d.rows; i++) {
    for (int j = 0; j < matrix_3d.columns; j++) {
      matrix_3d.matrix[i][j] *= x;
    }
  }
}

// matrix utils

void Model::createMatrix(const int &rows, const int &cols) {
  if (rows < 1 || cols < 1) {
    throw std::length_error("Wrong sizes of matrix.");
  }
  matrix_3d.rows = rows;
  matrix_3d.columns = cols;
  matrix_3d.matrix = new double *[rows];
  if (matrix_3d.matrix == nullptr) {
    throw std::length_error("Memory not allocated.");
  }
  for (int i = 0; i < rows; ++i) {
    matrix_3d.matrix[i] = new double[cols];
    if (matrix_3d.matrix[i] == nullptr) {
      throw std::length_error("Memory not allocated.");
    }
    for (int j = 0; j < cols; ++j) {
      matrix_3d.matrix[i][j] = 0;
    }
  }
}

void Model::deleteMatrix() {
  if (matrix_3d.matrix != nullptr) {
    for (int i = 0; i < matrix_3d.rows; ++i) {
      if (matrix_3d.matrix[i] != nullptr) {
        delete[] matrix_3d.matrix[i];
      } else {
        break;
      }
    }
    delete[] matrix_3d.matrix;
  }
}

// Parser funcs

void Model::parsingObj(FILE *in) {
  getCountOfVerticesAndFacets(in);
  fseek(in, 0, SEEK_SET);
  createMatrix(countOfVertices + 1, 3);
  polygons = new polygon_t[countOfFacets + 1];
  if (polygons == nullptr) {
    throw std::length_error("Array of polygons not allocated.");
  }
  getValueOfVerticesAndPolygons(in);
}

void Model::getCountOfVerticesAndFacets(FILE *in) {
  char *line = nullptr;
  size_t linecap = 0;
  countOfFacets = 0;
  countOfVertices = 0;
  while (getline(&line, &linecap, in) > 0) {
    if (line[0] == 'v' && line[1] == ' ') {
      countOfVertices += 1;
    }
    if (line[0] == 'f' && line[1] == ' ') {
      countOfFacets += 1;
    }
  }
  free(line);
}

void Model::getValueOfVerticesAndPolygons(FILE *in) {
  int iForVertices = 1;
  int iForPolygons = 1;
  char *line = nullptr;
  size_t linecap = 0;
  while (getline(&line, &linecap, in) > 0) {
    if (line[0] == 'v' && line[1] == ' ') {
      if (!sscanf(line + 1, "%lf %lf %lf", &(matrix_3d.matrix[iForVertices][0]),
                  &(matrix_3d.matrix[iForVertices][1]),
                  &(matrix_3d.matrix[iForVertices][2]))) {
        throw std::length_error("Wrong format of vertex.");
      }
      iForVertices++;
    } else if (line[0] == 'f' && line[1] == ' ') {
      polygons[iForPolygons].numbersOfVerticesInFacets =
          calcCountOfVerticesInPolygons(line);
      polygons[iForPolygons].vertices =
          new int[polygons[iForPolygons].numbersOfVerticesInFacets];
      if (polygons[iForPolygons].vertices != nullptr) {
        getVerticesOfPolygons(line, iForPolygons);
        iForPolygons++;
      } else {
        std::length_error("Memory not allocated.");
      }
    }
  }
  free(line);
}

int Model::calcCountOfVerticesInPolygons(const char *line) const {
  int count = 0;
  size_t i = 0;
  while (line[i] != '\n') {
    if (line[i] == ' ' && isdigit(line[i + 1])) {
      count++;
    }
    i++;
  }
  return count;
}

void Model::getVerticesOfPolygons(const char *line, const int &index) {
  int i = 0;
  int iForVerticesInPolygon = 0;
  while (line[i] != '\0') {
    if (line[i] == ' ' && isdigit(line[i + 1])) {
      sscanf(&line[i + 1], "%d",
             &(polygons[index].vertices[iForVerticesInPolygon]));
      iForVerticesInPolygon++;
    }
    i++;
  }
}

// copy

void Model::createDataForCopy(const Model &model) {
  createMatrix(model.countOfVertices + 1, 3);
  polygons = new polygon_t[model.countOfFacets + 1];
  if (polygons == nullptr) {
    std::length_error("Memory not allocated.");
  }
  for (int i = 1; i < model.countOfFacets + 1; ++i) {
    polygons[i].vertices = new int[model.polygons[i].numbersOfVerticesInFacets];
    if (polygons[i].vertices == nullptr) {
      std::length_error("Memory not allocated.");
    }
  }
}

void Model::copyData(const Model &model) {
  countOfVertices = model.countOfVertices;
  countOfFacets = model.countOfFacets;
  for (int i = 0; i < model.matrix_3d.rows; ++i) {
    for (int j = 0; j < model.matrix_3d.columns; j++) {
      matrix_3d.matrix[i][j] = model.matrix_3d.matrix[i][j];
    }
  }
  for (int i = 1; i < model.countOfFacets + 1; ++i) {
    polygons[i].numbersOfVerticesInFacets =
        model.polygons[i].numbersOfVerticesInFacets;
    for (int j = 0; j < model.polygons[i].numbersOfVerticesInFacets; j++) {
      polygons[i].vertices[j] = model.polygons[i].vertices[j];
    }
  }
}
