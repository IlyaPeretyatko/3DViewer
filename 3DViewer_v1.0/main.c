#include "s21_viewer.h"

int main() {
  const char *filename = "../src/models/cube.txt";
  FILE *in = fopen(filename, "r");
  if (in != NULL) {
    data_t *info = calloc(1, sizeof(data_t));
    parsing_obj(in, info);
    printf("%d %d\n\n", info->count_of_vertexes, info->count_of_facets);
    s21_print_matrix(info->matrix_3d.rows, info->matrix_3d.columns,
                     &info->matrix_3d);
    printf("\n\n");
    s21_print_polygon(info);
    clear_memory(info);
    fclose(in);
  } else {
    printf("Impossible to open the file!\n");
  }
  return 0;
}
