#include "s21_viewer.h"

void move_x(data_t *info, double a) {
  for (int i = 0; i < info->matrix_3d.rows; i++)
    info->matrix_3d.matrix[i][0] += a;
}

void move_y(data_t *info, double a) {
  for (int i = 0; i < info->matrix_3d.rows; i++)
    info->matrix_3d.matrix[i][1] += a;
}

void move_z(data_t *info, double a) {
  for (int i = 0; i < info->matrix_3d.rows; i++)
    info->matrix_3d.matrix[i][2] += a;
}

void rotation_by_ox(data_t *info, double angle) {
  for (int i = 0; i < info->matrix_3d.rows; i++) {
    double temp_y = info->matrix_3d.matrix[i][1];
    double temp_z = info->matrix_3d.matrix[i][2];
    info->matrix_3d.matrix[i][1] = cos(angle) * temp_y - sin(angle) * temp_z;
    info->matrix_3d.matrix[i][2] = sin(angle) * temp_y + cos(angle) * temp_z;
  }
}

void rotation_by_oy(data_t *info, double angle) {
  for (int i = 0; i < info->matrix_3d.rows; i++) {
    double temp_x = info->matrix_3d.matrix[i][0];
    double temp_z = info->matrix_3d.matrix[i][2];
    info->matrix_3d.matrix[i][0] = cos(angle) * temp_x + sin(angle) * temp_z;
    info->matrix_3d.matrix[i][2] = -sin(angle) * temp_x + cos(angle) * temp_z;
  }
}

void rotation_by_oz(data_t *info, double angle) {
  for (int i = 0; i < info->matrix_3d.rows; i++) {
    double temp_x = info->matrix_3d.matrix[i][0];
    double temp_y = info->matrix_3d.matrix[i][1];
    info->matrix_3d.matrix[i][0] = cos(angle) * temp_x - sin(angle) * temp_y;
    info->matrix_3d.matrix[i][1] = sin(angle) * temp_x + cos(angle) * temp_y;
  }
}

void scaling(data_t *info, double x) {
  for (int i = 0; i < info->matrix_3d.rows; i++) {
    for (int j = 0; j < info->matrix_3d.columns; j++) {
      info->matrix_3d.matrix[i][j] *= x;
    }
  }
}
