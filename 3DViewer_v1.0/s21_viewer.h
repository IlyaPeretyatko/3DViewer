#ifndef VIEWER_H
#define VIEWER_H

#include <check.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum exec_statuses { OK, ERROR };

// Viewer structures
typedef struct matrix {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

typedef struct facets {
  int *vertexes;
  int numbers_of_vertexes_in_facets;
} polygon_t;

typedef struct data {
  int count_of_vertexes;
  int count_of_facets;
  matrix_t matrix_3d;
  polygon_t *polygons;
} data_t;

// Matrix utils
int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
void s21_print_matrix(int rows, int columns, matrix_t *result);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_is_matrix_correct(matrix_t *A);

// Parser funcs
void s21_print_polygon(data_t *info);
int parsing_obj(FILE *in, data_t *info);
int calc_count_of_vertexes_in_polygons(char *line);
void get_vertexes_of_polygons(char *line, data_t *info, int index);
int get_value_of_vertexes_and_polygons(FILE *in, data_t *info);
void get_count_of_vertexes_and_facets(FILE *in, data_t *info);
void clear_memory(data_t *info);
int create_data_for_copy(data_t *info, data_t *buff_info);
void copy_data(data_t *info, data_t *buff_info);

// Affine transformations
void move_x(data_t *info, double a);
void move_y(data_t *info, double a);
void move_z(data_t *info, double a);
void rotation_by_ox(data_t *info, double angle);
void rotation_by_oy(data_t *info, double angle);
void rotation_by_oz(data_t *info, double angle);
void scaling(data_t *info, double x);

#endif  // VIEWER_H
