#include <gtest/gtest.h>
#include <stdio.h>

#include <iostream>

#include "viewer_model.h"

// Test parsingObj() function
TEST(ModelTest, ParsingObjValidFile) {
  s21::Model model;
  FILE *file = fopen("./Model/test/test.obj", "r");
  ASSERT_TRUE(file != nullptr);
  model.parsingObj(file);
  fclose(file);
  EXPECT_EQ(model.getCountOfVertices(), 8);
  EXPECT_EQ(model.getCountOfFacets(), 12);
  matrix_t ourMatrix = model.getMatrix_3d();

  double **resultMatrix = new double *[9];
  for (int i = 0; i < 9; ++i) {
    resultMatrix[i] = new double[3];
  }
  resultMatrix[0][0] = 0;
  resultMatrix[0][1] = 0;
  resultMatrix[0][2] = 0;

  resultMatrix[1][0] = 1.0;
  resultMatrix[1][1] = -1.0;
  resultMatrix[1][2] = -1.0;

  resultMatrix[2][0] = 1.0;
  resultMatrix[2][1] = -1.0;
  resultMatrix[2][2] = 1.0;

  resultMatrix[3][0] = -1.0;
  resultMatrix[3][1] = -1.0;
  resultMatrix[3][2] = 1.0;

  resultMatrix[4][0] = -1.0;
  resultMatrix[4][1] = -1.0;
  resultMatrix[4][2] = -1.0;

  resultMatrix[5][0] = 1.0;
  resultMatrix[5][1] = 1.0;
  resultMatrix[5][2] = -1.0;

  resultMatrix[6][0] = 0.999999;
  resultMatrix[6][1] = 1.000000;
  resultMatrix[6][2] = 1.000001;

  resultMatrix[7][0] = -1.0;
  resultMatrix[7][1] = 1.0;
  resultMatrix[7][2] = 1.0;

  resultMatrix[8][0] = -1.0;
  resultMatrix[8][1] = 1.0;
  resultMatrix[8][2] = -1.0;
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 3; ++j) {
      EXPECT_FLOAT_EQ(resultMatrix[i][j], ourMatrix.matrix[i][j]);
    }
  }
}

TEST(ModelTest, MoveXYZ) {
  s21::Model model;
  FILE *file = fopen("./Model/test/test.obj", "r");
  ASSERT_TRUE(file != nullptr);
  model.parsingObj(file);
  fclose(file);

  model.moveX(1);
  model.moveY(2);
  model.moveZ(3);

  matrix_t ourMatrix = model.getMatrix_3d();

  double **resultMatrix = new double *[9];
  for (int i = 0; i < 9; ++i) {
    resultMatrix[i] = new double[3];
  }
  resultMatrix[0][0] = 1;
  resultMatrix[0][1] = 2;
  resultMatrix[0][2] = 3;

  resultMatrix[1][0] = 2.0;
  resultMatrix[1][1] = 1.0;
  resultMatrix[1][2] = 2.0;

  resultMatrix[2][0] = 2.0;
  resultMatrix[2][1] = 1.0;
  resultMatrix[2][2] = 4.0;

  resultMatrix[3][0] = 0;
  resultMatrix[3][1] = 1.0;
  resultMatrix[3][2] = 4.0;

  resultMatrix[4][0] = 0;
  resultMatrix[4][1] = 1.0;
  resultMatrix[4][2] = 2.0;

  resultMatrix[5][0] = 2.0;
  resultMatrix[5][1] = 3.0;
  resultMatrix[5][2] = 2.0;

  resultMatrix[6][0] = 1.999999;
  resultMatrix[6][1] = 3.000000;
  resultMatrix[6][2] = 4.000001;

  resultMatrix[7][0] = 0;
  resultMatrix[7][1] = 3.0;
  resultMatrix[7][2] = 4.0;

  resultMatrix[8][0] = 0;
  resultMatrix[8][1] = 3.0;
  resultMatrix[8][2] = 2.0;

  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 3; ++j) {
      EXPECT_FLOAT_EQ(resultMatrix[i][j], ourMatrix.matrix[i][j]);
    }
  }
}

TEST(ModelTest, Scaling) {
  s21::Model model;
  FILE *file = fopen("./Model/test/test.obj", "r");
  ASSERT_TRUE(file != nullptr);
  model.parsingObj(file);
  fclose(file);
  model.scaling(0);

  matrix_t ourMatrix = model.getMatrix_3d();

  double **resultMatrix = new double *[9];
  for (int i = 0; i < 9; ++i) {
    resultMatrix[i] = new double[3];
  }
  resultMatrix[0][0] = 0;
  resultMatrix[0][1] = 0;
  resultMatrix[0][2] = 0;

  resultMatrix[1][0] = 0;
  resultMatrix[1][1] = 0;
  resultMatrix[1][2] = 0;

  resultMatrix[2][0] = 0;
  resultMatrix[2][1] = 0;
  resultMatrix[2][2] = 0;

  resultMatrix[3][0] = 0;
  resultMatrix[3][1] = 0;
  resultMatrix[3][2] = 0;

  resultMatrix[4][0] = 0;
  resultMatrix[4][1] = 0;
  resultMatrix[4][2] = 0;

  resultMatrix[5][0] = 0;
  resultMatrix[5][1] = 0;
  resultMatrix[5][2] = 0;

  resultMatrix[6][0] = 0;
  resultMatrix[6][1] = 0;
  resultMatrix[6][2] = 0;

  resultMatrix[7][0] = 0;
  resultMatrix[7][1] = 0;
  resultMatrix[7][2] = 0;

  resultMatrix[8][0] = 0;
  resultMatrix[8][1] = 0;
  resultMatrix[8][2] = 0;

  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 3; ++j) {
      EXPECT_FLOAT_EQ(resultMatrix[i][j], ourMatrix.matrix[i][j]);
    }
  }
}

TEST(ModelTest, RotationByOxOyOz) {
  s21::Model model;
  FILE *file = fopen("./Model/test/test.obj", "r");
  ASSERT_TRUE(file != nullptr);
  model.parsingObj(file);
  fclose(file);

  model.rotationByOx(M_PI);
  model.rotationByOy(M_PI);
  model.rotationByOz(M_PI);

  matrix_t ourMatrix = model.getMatrix_3d();

  double **resultMatrix = new double *[9];
  for (int i = 0; i < 9; ++i) {
    resultMatrix[i] = new double[3];
  }
  resultMatrix[0][0] = 0;
  resultMatrix[0][1] = 0;
  resultMatrix[0][2] = 0;

  resultMatrix[1][0] = 1.0;
  resultMatrix[1][1] = -1.0;
  resultMatrix[1][2] = -1.0;

  resultMatrix[2][0] = 1.0;
  resultMatrix[2][1] = -1.0;
  resultMatrix[2][2] = 1.0;

  resultMatrix[3][0] = -1.0;
  resultMatrix[3][1] = -1.0;
  resultMatrix[3][2] = 1.0;

  resultMatrix[4][0] = -1.0;
  resultMatrix[4][1] = -1.0;
  resultMatrix[4][2] = -1.0;

  resultMatrix[5][0] = 1.0;
  resultMatrix[5][1] = 1.0;
  resultMatrix[5][2] = -1.0;

  resultMatrix[6][0] = 0.999999;
  resultMatrix[6][1] = 1.000000;
  resultMatrix[6][2] = 1.000001;

  resultMatrix[7][0] = -1.0;
  resultMatrix[7][1] = 1.0;
  resultMatrix[7][2] = 1.0;

  resultMatrix[8][0] = -1.0;
  resultMatrix[8][1] = 1.0;
  resultMatrix[8][2] = -1.0;

  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 3; ++j) {
      EXPECT_FLOAT_EQ(resultMatrix[i][j], ourMatrix.matrix[i][j]);
    }
  }
}

TEST(ModelTest, CopyValidFile) {
  s21::Model model;
  FILE *file = fopen("./Model/test/test.obj", "r");
  ASSERT_TRUE(file != nullptr);
  model.parsingObj(file);
  fclose(file);
  s21::Model copyModel;
  copyModel.createDataForCopy(model);
  copyModel.copyData(model);
  EXPECT_EQ(copyModel.getCountOfVertices(), 8);
  EXPECT_EQ(copyModel.getCountOfFacets(), 12);
  matrix_t copyMatrix = copyModel.getMatrix_3d();

  double **resultMatrix = new double *[9];
  for (int i = 0; i < 9; ++i) {
    resultMatrix[i] = new double[3];
  }
  resultMatrix[0][0] = 0;
  resultMatrix[0][1] = 0;
  resultMatrix[0][2] = 0;

  resultMatrix[1][0] = 1.0;
  resultMatrix[1][1] = -1.0;
  resultMatrix[1][2] = -1.0;

  resultMatrix[2][0] = 1.0;
  resultMatrix[2][1] = -1.0;
  resultMatrix[2][2] = 1.0;

  resultMatrix[3][0] = -1.0;
  resultMatrix[3][1] = -1.0;
  resultMatrix[3][2] = 1.0;

  resultMatrix[4][0] = -1.0;
  resultMatrix[4][1] = -1.0;
  resultMatrix[4][2] = -1.0;

  resultMatrix[5][0] = 1.0;
  resultMatrix[5][1] = 1.0;
  resultMatrix[5][2] = -1.0;

  resultMatrix[6][0] = 0.999999;
  resultMatrix[6][1] = 1.000000;
  resultMatrix[6][2] = 1.000001;

  resultMatrix[7][0] = -1.0;
  resultMatrix[7][1] = 1.0;
  resultMatrix[7][2] = 1.0;

  resultMatrix[8][0] = -1.0;
  resultMatrix[8][1] = 1.0;
  resultMatrix[8][2] = -1.0;

  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 3; ++j) {
      EXPECT_FLOAT_EQ(resultMatrix[i][j], copyMatrix.matrix[i][j]);
    }
  }
  for (int i = 1; i < 13; ++i) {
    EXPECT_FLOAT_EQ(copyModel.getPolygons()[i].numbersOfVerticesInFacets, 3);
  }

  EXPECT_FLOAT_EQ(copyModel.getPolygons()[1].vertices[0], 5);
  EXPECT_FLOAT_EQ(copyModel.getPolygons()[1].vertices[1], 1);
  EXPECT_FLOAT_EQ(copyModel.getPolygons()[1].vertices[2], 4);

  EXPECT_FLOAT_EQ(copyModel.getPolygons()[2].vertices[0], 5);
  EXPECT_FLOAT_EQ(copyModel.getPolygons()[2].vertices[1], 4);
  EXPECT_FLOAT_EQ(copyModel.getPolygons()[2].vertices[2], 8);

  EXPECT_FLOAT_EQ(copyModel.getPolygons()[3].vertices[0], 3);
  EXPECT_FLOAT_EQ(copyModel.getPolygons()[3].vertices[1], 7);
  EXPECT_FLOAT_EQ(copyModel.getPolygons()[3].vertices[2], 8);

  EXPECT_FLOAT_EQ(copyModel.getPolygons()[4].vertices[0], 3);
  EXPECT_FLOAT_EQ(copyModel.getPolygons()[4].vertices[1], 8);
  EXPECT_FLOAT_EQ(copyModel.getPolygons()[4].vertices[2], 4);

  EXPECT_FLOAT_EQ(copyModel.getPolygons()[5].vertices[0], 2);
  EXPECT_FLOAT_EQ(copyModel.getPolygons()[5].vertices[1], 6);
  EXPECT_FLOAT_EQ(copyModel.getPolygons()[5].vertices[2], 3);

  EXPECT_FLOAT_EQ(copyModel.getPolygons()[6].vertices[0], 6);
  EXPECT_FLOAT_EQ(copyModel.getPolygons()[6].vertices[1], 7);
  EXPECT_FLOAT_EQ(copyModel.getPolygons()[6].vertices[2], 3);

  EXPECT_FLOAT_EQ(copyModel.getPolygons()[7].vertices[0], 1);
  EXPECT_FLOAT_EQ(copyModel.getPolygons()[7].vertices[1], 5);
  EXPECT_FLOAT_EQ(copyModel.getPolygons()[7].vertices[2], 2);

  EXPECT_FLOAT_EQ(copyModel.getPolygons()[8].vertices[0], 5);
  EXPECT_FLOAT_EQ(copyModel.getPolygons()[8].vertices[1], 6);
  EXPECT_FLOAT_EQ(copyModel.getPolygons()[8].vertices[2], 2);

  EXPECT_FLOAT_EQ(copyModel.getPolygons()[9].vertices[0], 5);
  EXPECT_FLOAT_EQ(copyModel.getPolygons()[9].vertices[1], 8);
  EXPECT_FLOAT_EQ(copyModel.getPolygons()[9].vertices[2], 6);

  EXPECT_FLOAT_EQ(copyModel.getPolygons()[10].vertices[0], 8);
  EXPECT_FLOAT_EQ(copyModel.getPolygons()[10].vertices[1], 7);
  EXPECT_FLOAT_EQ(copyModel.getPolygons()[10].vertices[2], 6);

  EXPECT_FLOAT_EQ(copyModel.getPolygons()[11].vertices[0], 1);
  EXPECT_FLOAT_EQ(copyModel.getPolygons()[11].vertices[1], 2);
  EXPECT_FLOAT_EQ(copyModel.getPolygons()[11].vertices[2], 3);

  EXPECT_FLOAT_EQ(copyModel.getPolygons()[12].vertices[0], 1);
  EXPECT_FLOAT_EQ(copyModel.getPolygons()[12].vertices[1], 3);
  EXPECT_FLOAT_EQ(copyModel.getPolygons()[12].vertices[2], 4);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
