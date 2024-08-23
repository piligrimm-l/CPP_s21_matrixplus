#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

struct testRandomInitMatrix : ::testing::Test {};

TEST_F(testRandomInitMatrix, Init_from_0to1000) {
  int rows = 10;
  int cols = 100;
  S21Matrix m(rows, cols);
  m.randomInitMatrix(0, 1000);
  for (int i = 0; i != rows; ++i) {
    for (int j = 0; j != cols; ++j) {
      ASSERT_TRUE(m(i, j) > 0 && m(i, j) < 1000);
    }
  }
}

TEST_F(testRandomInitMatrix, Init_from_minus1000to1000) {
  int rows = 100;
  int cols = 100;
  S21Matrix m(rows, cols);
  m.randomInitMatrix(-1000, 1000);
  for (int i = 0; i != rows; ++i) {
    for (int j = 0; j != cols; ++j) {
      ASSERT_TRUE(m(i, j) > -1000 && m(i, j) < 1000);
    }
  }
}
TEST_F(testRandomInitMatrix, Init_from_minus1E299to1E299) {
  int rows = 100;
  int cols = 1000;
  S21Matrix m(rows, cols);
  m.randomInitMatrix(-1e299, 1e299);
  for (int i = 0; i != rows; ++i) {
    for (int j = 0; j != cols; ++j) {
      ASSERT_TRUE(m(i, j) > -1e299 && m(i, j) < 1e299);
    }
  }
}

TEST_F(testRandomInitMatrix, resetMatrix) {
  int rows = 10;
  int cols = 100;
  S21Matrix m(rows, cols);
  m.randomInitMatrix(-1e299, 1e299);
  m.resetMatrix();
  ASSERT_TRUE(m.getRows() == 0 && m.getCols() == 0 && m.getMatrix() == nullptr);
}

TEST_F(testRandomInitMatrix, getRandomNumber_from_minus1E299to1E299) {
  for (int i = 0; i != 10000; ++i) {
    ASSERT_TRUE(getRandomNumber(-1e299, 1e299) > -1e299 &&
                getRandomNumber(-1e299, 1e299) < 1e299);
  }
}

TEST_F(testRandomInitMatrix, getRandomNumber_from_minus1to1) {
  for (int i = 0; i != 10000; ++i) {
    ASSERT_TRUE(getRandomNumber(-1, 1) > -1 && getRandomNumber(-1, 1) < 1);
  }
}
