#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

struct testCreateMatrix : ::testing::Test {};

TEST_F(testCreateMatrix, defaulConstructor) {
  S21Matrix matrix;
  ASSERT_EQ(matrix.getRows(), 0);
  ASSERT_EQ(matrix.getCols(), 0);
  ASSERT_TRUE(matrix.getMatrix() == nullptr);
}

TEST_F(testCreateMatrix, Constructor_with_Parameters_1x1) {
  int rows = 1;
  int cols = 1;
  S21Matrix matrix(rows, cols);
  ASSERT_EQ(matrix.getRows(), rows);
  ASSERT_EQ(matrix.getCols(), cols);
}

TEST_F(testCreateMatrix, Constructor_with_Parameters_0x1) {
  int rows = 0;
  int cols = 1;
  S21Matrix matrix(rows, cols);
  ASSERT_EQ(matrix.getRows(), rows);
  ASSERT_EQ(matrix.getCols(), cols);
}

TEST_F(testCreateMatrix, Constructor_with_Parameters_1x0) {
  int rows = 1;
  int cols = 0;
  S21Matrix matrix(rows, cols);
  ASSERT_EQ(matrix.getRows(), rows);
  ASSERT_EQ(matrix.getCols(), cols);
}

TEST_F(testCreateMatrix, Constructor_with_Parameters_3x3) {
  int rows = 3;
  int cols = 3;
  S21Matrix matrix(rows, cols);
  ASSERT_EQ(matrix.getRows(), rows);
  ASSERT_EQ(matrix.getCols(), cols);
}

TEST_F(testCreateMatrix, Constructor_with_Parameters_1x100) {
  int rows = 1;
  int cols = 100;
  S21Matrix matrix(rows, cols);
  ASSERT_EQ(matrix.getRows(), rows);
  ASSERT_EQ(matrix.getCols(), cols);
}

TEST_F(testCreateMatrix, Constructor_with_Parameters_100x1) {
  int rows = 100;
  int cols = 1;
  S21Matrix matrix(rows, cols);
  ASSERT_EQ(matrix.getRows(), rows);
  ASSERT_EQ(matrix.getCols(), cols);
}

TEST_F(testCreateMatrix, Constructor_with_Parameters_100x100) {
  int rows = 100;
  int cols = 100;
  S21Matrix matrix(rows, cols);
  ASSERT_EQ(matrix.getRows(), rows);
  ASSERT_EQ(matrix.getCols(), cols);
}

TEST_F(testCreateMatrix, Constructor_with_Parameters_Exceptions) {
  EXPECT_ANY_THROW(S21Matrix(3, -1));
  EXPECT_ANY_THROW(S21Matrix(-3, 1));
  EXPECT_ANY_THROW(S21Matrix(-100, -100));
  EXPECT_ANY_THROW(S21Matrix(0, -100));
  EXPECT_ANY_THROW(S21Matrix(-100, 0));
}

TEST_F(testCreateMatrix, ConstructorCopyMatrix_0x0) {
  S21Matrix m;
  S21Matrix mCpy(m);
  ASSERT_EQ(mCpy.getRows(), 0);
  ASSERT_EQ(mCpy.getCols(), 0);
}

TEST_F(testCreateMatrix, ConstructorCopyMatrix_1x1) {
  int rows = 1;
  int cols = 1;
  S21Matrix m(rows, cols);
  m.randomInitMatrix(-100, 100);
  S21Matrix mCpy(m);
  ASSERT_EQ(mCpy.getRows(), rows);
  ASSERT_EQ(mCpy.getCols(), cols);
  ASSERT_EQ(mCpy.getMatrix()[0], m.getMatrix()[0]);
}

TEST_F(testCreateMatrix, ConstructorCopyMatrix_1x100) {
  int rows = 1;
  int cols = 100;
  S21Matrix m(rows, cols);
  m.randomInitMatrix(-100, 100);
  S21Matrix mCpy(m);
  ASSERT_EQ(mCpy.getRows(), rows);
  ASSERT_EQ(mCpy.getCols(), cols);
  for (int i = 0; i < rows * cols; ++i) {
    ASSERT_EQ(mCpy.getMatrix()[i], m.getMatrix()[i]);
  }
}

TEST_F(testCreateMatrix, ConstructorCopyMatrix_100x1) {
  int rows = 100;
  int cols = 1;
  S21Matrix m(rows, cols);
  m.randomInitMatrix(-100, 100);
  S21Matrix mCpy(m);
  ASSERT_EQ(mCpy.getRows(), rows);
  ASSERT_EQ(mCpy.getCols(), cols);
  for (int i = 0; i < rows * cols; ++i) {
    ASSERT_EQ(mCpy.getMatrix()[i], m.getMatrix()[i]);
  }
}

TEST_F(testCreateMatrix, ConstructorCopyMatrix_5x5) {
  int rows = 5;
  int cols = 5;
  S21Matrix m(rows, cols);
  m.randomInitMatrix(-1005, 1005);
  S21Matrix mCpy(m);
  ASSERT_EQ(mCpy.getRows(), rows);
  ASSERT_EQ(mCpy.getCols(), cols);
  for (int i = 0; i < rows * cols; ++i) {
    ASSERT_EQ(mCpy.getMatrix()[i], m.getMatrix()[i]);
  }
}

TEST_F(testCreateMatrix, ConstructorMoveMatrix_0x0) {
  int rows = 0;
  int cols = 0;
  S21Matrix m(rows, cols);
  m.randomInitMatrix(-1005, 1005);
  S21Matrix mCpy(m);
  S21Matrix mMove = std::move(m);
  ASSERT_EQ(mMove.getRows(), rows);
  ASSERT_EQ(mMove.getCols(), cols);
  ASSERT_EQ(m.getRows(), 0);
  ASSERT_EQ(m.getCols(), 0);
  ASSERT_EQ(m.getMatrix(), nullptr);
}

TEST_F(testCreateMatrix, ConstructorMoveMatrix_1x1) {
  int rows = 1;
  int cols = 1;
  S21Matrix m(rows, cols);
  m.randomInitMatrix(-1005, 1005);
  S21Matrix mCpy(m);
  S21Matrix mMove = std::move(m);
  ASSERT_EQ(mMove.getRows(), rows);
  ASSERT_EQ(mMove.getCols(), cols);
  ASSERT_EQ(m.getRows(), 0);
  ASSERT_EQ(m.getCols(), 0);
  ASSERT_EQ(m.getMatrix(), nullptr);
  ASSERT_EQ(mMove.getMatrix()[0], mCpy.getMatrix()[0]);
}

TEST_F(testCreateMatrix, ConstructorMoveMatrix_1x100) {
  int rows = 1;
  int cols = 100;
  S21Matrix m(rows, cols);
  m.randomInitMatrix(-1005, 1005);
  S21Matrix mCpy(m);
  S21Matrix mMove = std::move(m);
  ASSERT_EQ(mMove.getRows(), rows);
  ASSERT_EQ(mMove.getCols(), cols);
  ASSERT_EQ(m.getRows(), 0);
  ASSERT_EQ(m.getCols(), 0);
  ASSERT_EQ(m.getMatrix(), nullptr);
  for (int i = 0; i < rows * cols; ++i) {
    ASSERT_EQ(mMove.getMatrix()[i], mCpy.getMatrix()[i]);
  }
}

TEST_F(testCreateMatrix, ConstructorMoveMatrix_100x1) {
  int rows = 100;
  int cols = 1;
  S21Matrix m(rows, cols);
  m.randomInitMatrix(-1005, 1005);
  S21Matrix mCpy(m);
  S21Matrix mMove = std::move(m);
  ASSERT_EQ(mMove.getRows(), rows);
  ASSERT_EQ(mMove.getCols(), cols);
  ASSERT_EQ(m.getRows(), 0);
  ASSERT_EQ(m.getCols(), 0);
  ASSERT_EQ(m.getMatrix(), nullptr);
  for (int i = 0; i < rows * cols; ++i) {
    ASSERT_EQ(mMove.getMatrix()[i], mCpy.getMatrix()[i]);
  }
}

TEST_F(testCreateMatrix, ConstructorMoveMatrix_5x5) {
  int rows = 5;
  int cols = 5;
  S21Matrix m(rows, cols);
  m.randomInitMatrix(-1005, 1005);
  S21Matrix mCpy(m);
  S21Matrix mMove = std::move(m);
  ASSERT_EQ(mMove.getRows(), rows);
  ASSERT_EQ(mMove.getCols(), cols);
  ASSERT_EQ(m.getRows(), 0);
  ASSERT_EQ(m.getCols(), 0);
  ASSERT_EQ(m.getMatrix(), nullptr);
  for (int i = 0; i < rows * cols; ++i) {
    ASSERT_EQ(mMove.getMatrix()[i], mCpy.getMatrix()[i]);
  }
}

TEST_F(testCreateMatrix, resetMatrix) {
  int rows = 100;
  int cols = 100;
  S21Matrix m(rows, cols);
  ASSERT_EQ(m.getRows(), rows);
  ASSERT_EQ(m.getCols(), cols);
  m.randomInitMatrix(1, 1005);
  ASSERT_TRUE((m(0, cols / 2) > 1) && (m(0, cols / 2) < 1005));
  m.resetMatrix();
  ASSERT_EQ(m.getRows(), 0);
  ASSERT_EQ(m.getCols(), 0);
  ASSERT_TRUE(m.getMatrix() == nullptr);
}
