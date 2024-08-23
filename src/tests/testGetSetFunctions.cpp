#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

struct testGetSetFunctionsMatrix : ::testing::Test {};

TEST_F(testGetSetFunctionsMatrix, testGetRows) {
  int rows = 0;
  int cols = 100;
  for (int i = 0; i != 100; ++i) {
    S21Matrix m(rows, cols);
    ASSERT_EQ(m.getRows(), rows);
    ASSERT_EQ(m.getCols(), cols);
    m.resetMatrix();
    rows += 10;
  }
}

TEST_F(testGetSetFunctionsMatrix, testGetCols) {
  int rows = 100;
  int cols = 0;
  for (int i = 0; i != 100; ++i) {
    S21Matrix m(rows, cols);
    ASSERT_EQ(m.getRows(), rows);
    ASSERT_EQ(m.getCols(), cols);
    m.resetMatrix();
    cols += 10;
  }
}

TEST_F(testGetSetFunctionsMatrix, testGetMatrix) {
  S21Matrix m;
  ASSERT_EQ(m.getMatrix(), nullptr);
  m.~S21Matrix();

  int rows = 1;
  int cols = 1;
  for (int i = 0; i != 100; ++i) {
    S21Matrix m(rows, cols);
    ASSERT_EQ(m.getRows(), rows);
    ASSERT_EQ(m.getCols(), cols);
    double *cpy_matrix_ = m.getMatrix();
    S21Matrix mMove = std::move(m);
    ASSERT_EQ(mMove.getMatrix(), cpy_matrix_);
    mMove.resetMatrix();
    rows += 5;
    cols += 2;
  }
}

TEST_F(testGetSetFunctionsMatrix, testSetRows_negative) {
  int rows = 2;
  int cols = 5;
  S21Matrix m(rows, cols);
  ASSERT_EQ(m.getRows(), rows);
  ASSERT_EQ(m.getCols(), cols);
  EXPECT_ANY_THROW(m.setRows(-8));
}

TEST_F(testGetSetFunctionsMatrix, testSetCols_negative) {
  int rows = 7;
  int cols = 15;
  S21Matrix m(rows, cols);
  ASSERT_EQ(m.getRows(), rows);
  ASSERT_EQ(m.getCols(), cols);
  EXPECT_ANY_THROW(m.setCols(-3));
}

TEST_F(testGetSetFunctionsMatrix, testSetRows) {
  S21Matrix m;
  int newRows = 0;
  ASSERT_EQ(m.getRows(), 0);
  for (int i = 0; i != 1000; ++i) {
    m.setRows(newRows);
    ASSERT_EQ(m.getRows(), newRows);
    newRows += 5;
  }
}

TEST_F(testGetSetFunctionsMatrix, testSetCols) {
  S21Matrix m;
  int newCols = 0;
  ASSERT_EQ(m.getCols(), 0);
  for (int i = 0; i != 1000; ++i) {
    m.setCols(newCols);
    ASSERT_EQ(m.getCols(), newCols);
    newCols += 5;
  }
}

TEST_F(testGetSetFunctionsMatrix, testSetRows_element_value) {
  int rows = 3;
  int cols = 8;
  S21Matrix m(rows, cols);
  ASSERT_EQ(m.getRows(), rows);
  ASSERT_EQ(m.getCols(), cols);
  m.randomInitMatrix(-100, 100);
  S21Matrix mCpy(m);
  int newRows = 8;
  m.setRows(newRows);
  for (int i = 0; i != newRows; ++i) {
    for (int j = 0; j != cols; ++j) {
      if (i < rows) {
        ASSERT_EQ(m(i, j), mCpy(i, j));
      } else {
        ASSERT_EQ(m(i, j), 0);
      }
    }
  }
}

TEST_F(testGetSetFunctionsMatrix, testSetCols_element_value) {
  int rows = 8;
  int cols = 3;
  S21Matrix m(rows, cols);
  ASSERT_EQ(m.getRows(), rows);
  ASSERT_EQ(m.getCols(), cols);
  m.randomInitMatrix(-100, 100);
  S21Matrix mCpy(m);
  int newCols = 8;
  m.setCols(newCols);
  for (int i = 0; i != rows; ++i) {
    for (int j = 0; j != newCols; ++j) {
      if (j < cols) {
        ASSERT_EQ(m(i, j), mCpy(i, j));
      } else {
        ASSERT_EQ(m(i, j), 0);
      }
    }
  }
}
