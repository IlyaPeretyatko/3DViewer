#include "s21_viewer.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int rv = 0;
  result->rows = rows;
  result->columns = columns;
  if (rows < 1 || columns < 1) {
    rv = 1;
  } else {
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (result->matrix == NULL) {
      rv = 1;
    } else {
      for (int i = 0; i < rows; ++i) {
        result->matrix[i] = (double *)calloc(columns, sizeof(double));
        if (result->matrix[i] == NULL) {
          rv = 0;
          break;
        }
      }
    }
    if (rv == 1) {
      s21_remove_matrix(result);
    }
  }
  return rv;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix != NULL) {
    for (int i = 0; i < A->rows; ++i) {
      if (A->matrix[i] != NULL) {
        free(A->matrix[i]);
      } else {
        break;
      }
    }
    free(A->matrix);
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int status = 1;
  if (!s21_is_matrix_correct(A) && !s21_is_matrix_correct(B) &&
      A->columns == B->columns && A->rows == B->rows) {
    for (int i = 0; i < A->rows && status; i++) {
      for (int j = 0; j < B->columns && status; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-07) {
          status = 0;
        }
      }
    }
  } else {
    status = 0;
  }
  return status;
}

int s21_is_matrix_correct(matrix_t *A) {
  int status = 0;
  if (A == NULL || A->matrix == NULL || A->rows <= 0 || A->columns <= 0)
    status = 1;
  return status;
}
