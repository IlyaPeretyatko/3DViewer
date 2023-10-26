#include "s21_viewer.h"

int parsing_obj(FILE *in, data_t *info) {
  int return_value = 0;
  get_count_of_vertexes_and_facets(in, info);
  fseek(in, 0, SEEK_SET);
  if (s21_create_matrix(info->count_of_vertexes + 1, 3, &(info->matrix_3d))) {
    return_value = 1;
  }
  info->polygons =
      (polygon_t *)calloc(info->count_of_facets + 1, sizeof(polygon_t));
  if (info->polygons == NULL) {
    return_value = 1;
  }
  return_value = get_value_of_vertexes_and_polygons(in, info);
  return return_value;
}

void get_count_of_vertexes_and_facets(FILE *in, data_t *info) {
  char *line = NULL;
  size_t linecap = 0;
  while (getline(&line, &linecap, in) > 0) {
    if (line[0] == 'v' && line[1] == ' ') {
      info->count_of_vertexes += 1;
    }
    if (line[0] == 'f' && line[1] == ' ') {
      info->count_of_facets += 1;
    }
  }
  free(line);
}

int get_value_of_vertexes_and_polygons(FILE *in, data_t *info) {
  int return_value = 0;
  int i_for_vertexes = 1;
  int i_for_polygons = 1;
  char *line = NULL;
  size_t linecap = 0;
  while (getline(&line, &linecap, in) > 0) {
    if (line[0] == 'v' && line[1] == ' ') {
      if (!sscanf(line + 1, "%lf %lf %lf",
                  &(info->matrix_3d.matrix[i_for_vertexes][0]),
                  &(info->matrix_3d.matrix[i_for_vertexes][1]),
                  &(info->matrix_3d.matrix[i_for_vertexes][2]))) {
        return_value = 1;
      }
      i_for_vertexes++;
    } else if (line[0] == 'f' && line[1] == ' ') {
      info->polygons[i_for_polygons].numbers_of_vertexes_in_facets =
          calc_count_of_vertexes_in_polygons(line);
      info->polygons[i_for_polygons].vertexes = (int *)malloc(
          info->polygons[i_for_polygons].numbers_of_vertexes_in_facets *
          sizeof(int));
      if (info->polygons[i_for_polygons].vertexes) {
        get_vertexes_of_polygons(line, info, i_for_polygons);
        i_for_polygons++;
      } else {
        return_value = 1;
      }
    }
  }
  free(line);
  return return_value;
}

int calc_count_of_vertexes_in_polygons(char *line) {
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

void get_vertexes_of_polygons(char *line, data_t *info, int index) {
  int i = 0;
  int i_for_vertexes_in_polygon = 0;
  while (line[i] != '\0') {
    if (line[i] == ' ' && isdigit(line[i + 1])) {
      sscanf(&line[i + 1], "%d",
             &(info->polygons[index].vertexes[i_for_vertexes_in_polygon]));
      i_for_vertexes_in_polygon++;
    }
    i++;
  }
}

void clear_memory(data_t *info) {
  if (info != NULL) {
    if (info->polygons != NULL) {
      for (int i = 0; i < info->count_of_facets + 1; ++i) {
        if (info->polygons[i].vertexes != NULL) {
          free(info->polygons[i].vertexes);
        }
      }
      free(info->polygons);
    }
    s21_remove_matrix(&(info->matrix_3d));
    free(info);
  }
}

int create_data_for_copy(data_t *info, data_t *buff_info) {
  int return_value = 0;
  if (s21_create_matrix(buff_info->count_of_vertexes + 1, 3,
                        &(info->matrix_3d))) {
    return_value = 1;
  }
  info->polygons =
      (polygon_t *)calloc(buff_info->count_of_facets + 1, sizeof(polygon_t));
  if (info->polygons == NULL) {
    return_value = 1;
  }
  for (int i = 1; i < buff_info->count_of_facets + 1; ++i) {
    info->polygons[i].vertexes = (int *)malloc(
        buff_info->polygons[i].numbers_of_vertexes_in_facets * sizeof(int));
    if (info->polygons[i].vertexes == NULL) {
      return_value = 1;
    }
  }
  return return_value;
}

void copy_data(data_t *info, data_t *buff_info) {
  info->count_of_vertexes = buff_info->count_of_vertexes;
  info->count_of_facets = buff_info->count_of_facets;
  for (int i = 0; i < buff_info->matrix_3d.rows; ++i) {
    for (int j = 0; j < buff_info->matrix_3d.columns; j++) {
      info->matrix_3d.matrix[i][j] = buff_info->matrix_3d.matrix[i][j];
    }
  }
  for (int i = 1; i < buff_info->count_of_facets + 1; ++i) {
    info->polygons[i].numbers_of_vertexes_in_facets =
        buff_info->polygons[i].numbers_of_vertexes_in_facets;
    for (int j = 0; j < buff_info->polygons[i].numbers_of_vertexes_in_facets;
         j++) {
      info->polygons[i].vertexes[j] = buff_info->polygons[i].vertexes[j];
    }
  }
}
