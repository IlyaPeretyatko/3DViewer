#include "s21_viewer.h"

START_TEST(s21_cube_parser) {
  FILE *in = fopen("../test.txt", "r");
  if (in != NULL) {
    data_t *info = calloc(1, sizeof(data_t));
    parsing_obj(in, info);
    ck_assert_int_eq(info->count_of_vertexes, 8);
    ck_assert_int_eq(info->count_of_facets, 12);

    matrix_t A = {0};
    s21_create_matrix(9, 3, &A);
    A.matrix[0][0] = 0;
    A.matrix[0][1] = 0;
    A.matrix[0][2] = 0;

    A.matrix[1][0] = 1.0;
    A.matrix[1][1] = -1.0;
    A.matrix[1][2] = -1.0;

    A.matrix[2][0] = 1.0;
    A.matrix[2][1] = -1.0;
    A.matrix[2][2] = 1.0;

    A.matrix[3][0] = -1.0;
    A.matrix[3][1] = -1.0;
    A.matrix[3][2] = 1.0;

    A.matrix[4][0] = -1.0;
    A.matrix[4][1] = -1.0;
    A.matrix[4][2] = -1.0;

    A.matrix[5][0] = 1.0;
    A.matrix[5][1] = 1.0;
    A.matrix[5][2] = -1.0;

    A.matrix[6][0] = 0.999999;
    A.matrix[6][1] = 1.000000;
    A.matrix[6][2] = 1.000001;

    A.matrix[7][0] = -1.0;
    A.matrix[7][1] = 1.0;
    A.matrix[7][2] = 1.0;

    A.matrix[8][0] = -1.0;
    A.matrix[8][1] = 1.0;
    A.matrix[8][2] = -1.0;

    ck_assert_int_eq(info->matrix_3d.rows - 1, 8);
    ck_assert_int_eq(info->matrix_3d.columns, 3);
    int res = s21_eq_matrix(&A, &info->matrix_3d);
    ck_assert_int_eq(res, 1);

    ck_assert_int_eq(info->polygons[1].numbers_of_vertexes_in_facets, 3);
    ck_assert_int_eq(info->polygons[2].numbers_of_vertexes_in_facets, 3);
    ck_assert_int_eq(info->polygons[3].numbers_of_vertexes_in_facets, 3);
    ck_assert_int_eq(info->polygons[4].numbers_of_vertexes_in_facets, 3);
    ck_assert_int_eq(info->polygons[5].numbers_of_vertexes_in_facets, 3);
    ck_assert_int_eq(info->polygons[6].numbers_of_vertexes_in_facets, 3);
    ck_assert_int_eq(info->polygons[7].numbers_of_vertexes_in_facets, 3);
    ck_assert_int_eq(info->polygons[8].numbers_of_vertexes_in_facets, 3);
    ck_assert_int_eq(info->polygons[9].numbers_of_vertexes_in_facets, 3);
    ck_assert_int_eq(info->polygons[10].numbers_of_vertexes_in_facets, 3);
    ck_assert_int_eq(info->polygons[11].numbers_of_vertexes_in_facets, 3);
    ck_assert_int_eq(info->polygons[12].numbers_of_vertexes_in_facets, 3);

    ck_assert_int_eq(info->polygons[1].vertexes[0], 5);
    ck_assert_int_eq(info->polygons[1].vertexes[1], 1);
    ck_assert_int_eq(info->polygons[1].vertexes[2], 4);

    ck_assert_int_eq(info->polygons[2].vertexes[0], 5);
    ck_assert_int_eq(info->polygons[2].vertexes[1], 4);
    ck_assert_int_eq(info->polygons[2].vertexes[2], 8);

    ck_assert_int_eq(info->polygons[3].vertexes[0], 3);
    ck_assert_int_eq(info->polygons[3].vertexes[1], 7);
    ck_assert_int_eq(info->polygons[3].vertexes[2], 8);

    ck_assert_int_eq(info->polygons[4].vertexes[0], 3);
    ck_assert_int_eq(info->polygons[4].vertexes[1], 8);
    ck_assert_int_eq(info->polygons[4].vertexes[2], 4);

    ck_assert_int_eq(info->polygons[5].vertexes[0], 2);
    ck_assert_int_eq(info->polygons[5].vertexes[1], 6);
    ck_assert_int_eq(info->polygons[5].vertexes[2], 3);

    ck_assert_int_eq(info->polygons[6].vertexes[0], 6);
    ck_assert_int_eq(info->polygons[6].vertexes[1], 7);
    ck_assert_int_eq(info->polygons[6].vertexes[2], 3);

    ck_assert_int_eq(info->polygons[7].vertexes[0], 1);
    ck_assert_int_eq(info->polygons[7].vertexes[1], 5);
    ck_assert_int_eq(info->polygons[7].vertexes[2], 2);

    ck_assert_int_eq(info->polygons[8].vertexes[0], 5);
    ck_assert_int_eq(info->polygons[8].vertexes[1], 6);
    ck_assert_int_eq(info->polygons[8].vertexes[2], 2);

    ck_assert_int_eq(info->polygons[9].vertexes[0], 5);
    ck_assert_int_eq(info->polygons[9].vertexes[1], 8);
    ck_assert_int_eq(info->polygons[9].vertexes[2], 6);

    ck_assert_int_eq(info->polygons[10].vertexes[0], 8);
    ck_assert_int_eq(info->polygons[10].vertexes[1], 7);
    ck_assert_int_eq(info->polygons[10].vertexes[2], 6);

    ck_assert_int_eq(info->polygons[11].vertexes[0], 1);
    ck_assert_int_eq(info->polygons[11].vertexes[1], 2);
    ck_assert_int_eq(info->polygons[11].vertexes[2], 3);

    ck_assert_int_eq(info->polygons[12].vertexes[0], 1);
    ck_assert_int_eq(info->polygons[12].vertexes[1], 3);
    ck_assert_int_eq(info->polygons[12].vertexes[2], 4);

    s21_remove_matrix(&A);
    clear_memory(info);
    fclose(in);
  }
}
END_TEST

START_TEST(s21_move) {
  FILE *in = fopen("../test.txt", "r");
  if (in != NULL) {
    data_t *info = calloc(1, sizeof(data_t));
    parsing_obj(in, info);

    move_x(info, 1);
    move_y(info, 2);
    move_z(info, 3);

    matrix_t A = {0};
    s21_create_matrix(9, 3, &A);
    A.matrix[0][0] = 1;
    A.matrix[0][1] = 2;
    A.matrix[0][2] = 3;

    A.matrix[1][0] = 2.0;
    A.matrix[1][1] = 1.0;
    A.matrix[1][2] = 2.0;

    A.matrix[2][0] = 2.0;
    A.matrix[2][1] = 1.0;
    A.matrix[2][2] = 4.0;

    A.matrix[3][0] = 0;
    A.matrix[3][1] = 1.0;
    A.matrix[3][2] = 4.0;

    A.matrix[4][0] = 0;
    A.matrix[4][1] = 1.0;
    A.matrix[4][2] = 2.0;

    A.matrix[5][0] = 2.0;
    A.matrix[5][1] = 3.0;
    A.matrix[5][2] = 2.0;

    A.matrix[6][0] = 1.999999;
    A.matrix[6][1] = 3.000000;
    A.matrix[6][2] = 4.000001;

    A.matrix[7][0] = 0;
    A.matrix[7][1] = 3.0;
    A.matrix[7][2] = 4.0;

    A.matrix[8][0] = 0;
    A.matrix[8][1] = 3.0;
    A.matrix[8][2] = 2.0;

    int res = s21_eq_matrix(&A, &info->matrix_3d);
    ck_assert_int_eq(res, 1);

    s21_remove_matrix(&A);
    clear_memory(info);
    fclose(in);
  }
}
END_TEST

START_TEST(s21_scaling) {
  FILE *in = fopen("../test.txt", "r");
  if (in != NULL) {
    data_t *info = calloc(1, sizeof(data_t));
    parsing_obj(in, info);
    scaling(info, 0);

    matrix_t A = {0};
    s21_create_matrix(9, 3, &A);
    A.matrix[0][0] = 0;
    A.matrix[0][1] = 0;
    A.matrix[0][2] = 0;

    A.matrix[1][0] = 0;
    A.matrix[1][1] = 0;
    A.matrix[1][2] = 0;

    A.matrix[2][0] = 0;
    A.matrix[2][1] = 0;
    A.matrix[2][2] = 0;

    A.matrix[3][0] = 0;
    A.matrix[3][1] = 0;
    A.matrix[3][2] = 0;

    A.matrix[4][0] = 0;
    A.matrix[4][1] = 0;
    A.matrix[4][2] = 0;

    A.matrix[5][0] = 0;
    A.matrix[5][1] = 0;
    A.matrix[5][2] = 0;

    A.matrix[6][0] = 0;
    A.matrix[6][1] = 0;
    A.matrix[6][2] = 0;

    A.matrix[7][0] = 0;
    A.matrix[7][1] = 0;
    A.matrix[7][2] = 0;

    A.matrix[8][0] = 0;
    A.matrix[8][1] = 0;
    A.matrix[8][2] = 0;

    int res = s21_eq_matrix(&A, &info->matrix_3d);
    ck_assert_int_eq(res, 1);

    s21_remove_matrix(&A);
    clear_memory(info);
    fclose(in);
  }
}
END_TEST

START_TEST(s21_rotate) {
  FILE *in = fopen("../test.txt", "r");
  if (in != NULL) {
    data_t *info = calloc(1, sizeof(data_t));
    parsing_obj(in, info);

    rotation_by_ox(info, M_PI);
    rotation_by_oy(info, M_PI);
    rotation_by_oz(info, M_PI);

    matrix_t A = {0};
    s21_create_matrix(9, 3, &A);
    A.matrix[0][0] = 0;
    A.matrix[0][1] = 0;
    A.matrix[0][2] = 0;

    A.matrix[1][0] = 1.0;
    A.matrix[1][1] = -1.0;
    A.matrix[1][2] = -1.0;

    A.matrix[2][0] = 1.0;
    A.matrix[2][1] = -1.0;
    A.matrix[2][2] = 1.0;

    A.matrix[3][0] = -1.0;
    A.matrix[3][1] = -1.0;
    A.matrix[3][2] = 1.0;

    A.matrix[4][0] = -1.0;
    A.matrix[4][1] = -1.0;
    A.matrix[4][2] = -1.0;

    A.matrix[5][0] = 1.0;
    A.matrix[5][1] = 1.0;
    A.matrix[5][2] = -1.0;

    A.matrix[6][0] = 0.999999;
    A.matrix[6][1] = 1.000000;
    A.matrix[6][2] = 1.000001;

    A.matrix[7][0] = -1.0;
    A.matrix[7][1] = 1.0;
    A.matrix[7][2] = 1.0;

    A.matrix[8][0] = -1.0;
    A.matrix[8][1] = 1.0;
    A.matrix[8][2] = -1.0;

    int res = s21_eq_matrix(&A, &info->matrix_3d);
    ck_assert_int_eq(res, 1);

    s21_remove_matrix(&A);
    clear_memory(info);
    fclose(in);
  }
}
END_TEST

START_TEST(s21_copy) {
  FILE *in = fopen("../test.txt", "r");
  if (in != NULL) {
    data_t *info = calloc(1, sizeof(data_t));
    data_t *copy_info = calloc(1, sizeof(data_t));
    parsing_obj(in, info);
    create_data_for_copy(copy_info, info);
    copy_data(copy_info, info);
    ck_assert_int_eq(copy_info->count_of_vertexes, 8);
    ck_assert_int_eq(copy_info->count_of_facets, 12);

    matrix_t A = {0};
    s21_create_matrix(9, 3, &A);
    A.matrix[0][0] = 0;
    A.matrix[0][1] = 0;
    A.matrix[0][2] = 0;

    A.matrix[1][0] = 1.0;
    A.matrix[1][1] = -1.0;
    A.matrix[1][2] = -1.0;

    A.matrix[2][0] = 1.0;
    A.matrix[2][1] = -1.0;
    A.matrix[2][2] = 1.0;

    A.matrix[3][0] = -1.0;
    A.matrix[3][1] = -1.0;
    A.matrix[3][2] = 1.0;

    A.matrix[4][0] = -1.0;
    A.matrix[4][1] = -1.0;
    A.matrix[4][2] = -1.0;

    A.matrix[5][0] = 1.0;
    A.matrix[5][1] = 1.0;
    A.matrix[5][2] = -1.0;

    A.matrix[6][0] = 0.999999;
    A.matrix[6][1] = 1.000000;
    A.matrix[6][2] = 1.000001;

    A.matrix[7][0] = -1.0;
    A.matrix[7][1] = 1.0;
    A.matrix[7][2] = 1.0;

    A.matrix[8][0] = -1.0;
    A.matrix[8][1] = 1.0;
    A.matrix[8][2] = -1.0;

    ck_assert_int_eq(copy_info->matrix_3d.rows - 1, 8);
    ck_assert_int_eq(copy_info->matrix_3d.columns, 3);
    int res = s21_eq_matrix(&A, &copy_info->matrix_3d);
    ck_assert_int_eq(res, 1);

    ck_assert_int_eq(copy_info->polygons[1].numbers_of_vertexes_in_facets, 3);
    ck_assert_int_eq(copy_info->polygons[2].numbers_of_vertexes_in_facets, 3);
    ck_assert_int_eq(copy_info->polygons[3].numbers_of_vertexes_in_facets, 3);
    ck_assert_int_eq(copy_info->polygons[4].numbers_of_vertexes_in_facets, 3);
    ck_assert_int_eq(copy_info->polygons[5].numbers_of_vertexes_in_facets, 3);
    ck_assert_int_eq(copy_info->polygons[6].numbers_of_vertexes_in_facets, 3);
    ck_assert_int_eq(copy_info->polygons[7].numbers_of_vertexes_in_facets, 3);
    ck_assert_int_eq(copy_info->polygons[8].numbers_of_vertexes_in_facets, 3);
    ck_assert_int_eq(copy_info->polygons[9].numbers_of_vertexes_in_facets, 3);
    ck_assert_int_eq(copy_info->polygons[10].numbers_of_vertexes_in_facets, 3);
    ck_assert_int_eq(copy_info->polygons[11].numbers_of_vertexes_in_facets, 3);
    ck_assert_int_eq(copy_info->polygons[12].numbers_of_vertexes_in_facets, 3);

    ck_assert_int_eq(copy_info->polygons[1].vertexes[0], 5);
    ck_assert_int_eq(copy_info->polygons[1].vertexes[1], 1);
    ck_assert_int_eq(info->polygons[1].vertexes[2], 4);

    ck_assert_int_eq(copy_info->polygons[2].vertexes[0], 5);
    ck_assert_int_eq(copy_info->polygons[2].vertexes[1], 4);
    ck_assert_int_eq(copy_info->polygons[2].vertexes[2], 8);

    ck_assert_int_eq(copy_info->polygons[3].vertexes[0], 3);
    ck_assert_int_eq(copy_info->polygons[3].vertexes[1], 7);
    ck_assert_int_eq(copy_info->polygons[3].vertexes[2], 8);

    ck_assert_int_eq(copy_info->polygons[4].vertexes[0], 3);
    ck_assert_int_eq(copy_info->polygons[4].vertexes[1], 8);
    ck_assert_int_eq(copy_info->polygons[4].vertexes[2], 4);

    ck_assert_int_eq(copy_info->polygons[5].vertexes[0], 2);
    ck_assert_int_eq(copy_info->polygons[5].vertexes[1], 6);
    ck_assert_int_eq(copy_info->polygons[5].vertexes[2], 3);

    ck_assert_int_eq(copy_info->polygons[6].vertexes[0], 6);
    ck_assert_int_eq(copy_info->polygons[6].vertexes[1], 7);
    ck_assert_int_eq(copy_info->polygons[6].vertexes[2], 3);

    ck_assert_int_eq(copy_info->polygons[7].vertexes[0], 1);
    ck_assert_int_eq(copy_info->polygons[7].vertexes[1], 5);
    ck_assert_int_eq(copy_info->polygons[7].vertexes[2], 2);

    ck_assert_int_eq(copy_info->polygons[8].vertexes[0], 5);
    ck_assert_int_eq(copy_info->polygons[8].vertexes[1], 6);
    ck_assert_int_eq(copy_info->polygons[8].vertexes[2], 2);

    ck_assert_int_eq(copy_info->polygons[9].vertexes[0], 5);
    ck_assert_int_eq(copy_info->polygons[9].vertexes[1], 8);
    ck_assert_int_eq(copy_info->polygons[9].vertexes[2], 6);

    ck_assert_int_eq(copy_info->polygons[10].vertexes[0], 8);
    ck_assert_int_eq(copy_info->polygons[10].vertexes[1], 7);
    ck_assert_int_eq(copy_info->polygons[10].vertexes[2], 6);

    ck_assert_int_eq(copy_info->polygons[11].vertexes[0], 1);
    ck_assert_int_eq(copy_info->polygons[11].vertexes[1], 2);
    ck_assert_int_eq(copy_info->polygons[11].vertexes[2], 3);

    ck_assert_int_eq(copy_info->polygons[12].vertexes[0], 1);
    ck_assert_int_eq(copy_info->polygons[12].vertexes[1], 3);
    ck_assert_int_eq(copy_info->polygons[12].vertexes[2], 4);

    s21_remove_matrix(&A);
    clear_memory(info);
    clear_memory(copy_info);
    fclose(in);
  }
}
END_TEST

int main() {
  Suite *s1 = suite_create("Core");
  TCase *tc_core = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;
  suite_add_tcase(s1, tc_core);

  tcase_add_test(tc_core, s21_cube_parser);
  tcase_add_test(tc_core, s21_move);
  tcase_add_test(tc_core, s21_copy);
  tcase_add_test(tc_core, s21_rotate);
  tcase_add_test(tc_core, s21_scaling);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf ? 1 : 0;
}
