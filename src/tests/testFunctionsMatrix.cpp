#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

struct testFunctionsMatrix : ::testing::Test {};

TEST_F(testFunctionsMatrix, testEqMatrix_and_operator_eq_1) {
  S21Matrix m1(8, 5);
  S21Matrix m2(5, 8);
  // если число строк или число стобцов матрицы m1 не равно числу строк или
  // числу столбцов матрицы m2, то резульатом сравнения матриц должно быть false
  ASSERT_NE((m1.getRows() != m2.getRows()) || (m1.getCols() != m2.getCols()),
            (m1 == m2));
  ASSERT_NE((m1.getRows() != m2.getRows()) || (m1.getCols() != m2.getCols()),
            m1.EqMatrix(m2));
}

TEST_F(testFunctionsMatrix, testEqMatrix_and_operator_eq_2) {
  S21Matrix m1(8, 5);
  S21Matrix m2(8, 8);
  ASSERT_NE((m1.getRows() != m2.getRows()) || (m1.getCols() != m2.getCols()),
            (m1 == m2));
  ASSERT_NE((m1.getRows() != m2.getRows()) || (m1.getCols() != m2.getCols()),
            m1.EqMatrix(m2));
}

TEST_F(testFunctionsMatrix, testEqMatrix_and_operator_eq_3) {
  S21Matrix m1(5, 8);
  S21Matrix m2(8, 8);
  ASSERT_NE((m1.getRows() != m2.getRows()) || (m1.getCols() != m2.getCols()),
            (m1 == m2));
  ASSERT_NE((m1.getRows() != m2.getRows()) || (m1.getCols() != m2.getCols()),
            m1.EqMatrix(m2));
}

TEST_F(testFunctionsMatrix, testEqMatrix_and_operator_eq_4) {
  bool res = true;
  S21Matrix m1(5, 11);
  m1.randomInitMatrix(-1000, 1000);
  S21Matrix m2(m1);
  for (int i = 0; i != 55; ++i) {
    if (m1.getMatrix()[i] != m2.getMatrix()[i]) {
      res = false;
    }
  }
  ASSERT_EQ(res, m1 == m2);
  ASSERT_EQ(res, m1.EqMatrix(m2));
}

TEST_F(testFunctionsMatrix, testEqMatrix_and_operator_eq_5) {
  bool res = true;
  S21Matrix m1(11, 5);
  m1.randomInitMatrix(-1000, 1000);
  S21Matrix m2(11, 5);
  m1.randomInitMatrix(-1000, 1000);
  for (int i = 0; i != 55; ++i) {
    if (m1.getMatrix()[i] != m2.getMatrix()[i]) {
      res = false;
      break;
    }
  }
  ASSERT_EQ(res, m1 == m2);
  ASSERT_EQ(res, m1.EqMatrix(m2));
}

TEST_F(testFunctionsMatrix, testSumMatrix_1) {
  S21Matrix m1(11, 5);
  S21Matrix m2(12, 7);
  ASSERT_ANY_THROW(m1.SumMatrix(m2));
}

TEST_F(testFunctionsMatrix, testSumMatrix_2) {
  S21Matrix m1(11, 5);
  S21Matrix m2(11, 7);
  ASSERT_ANY_THROW(m1.SumMatrix(m2));
}

TEST_F(testFunctionsMatrix, testSumMatrix_3) {
  S21Matrix m1(11, 7);
  S21Matrix m2(12, 7);
  ASSERT_ANY_THROW(m1.SumMatrix(m2));
}

TEST_F(testFunctionsMatrix, testSumMatrix_4) {
  int rows = 12;
  int cols = 7;
  S21Matrix m1(rows, cols);
  m1.randomInitMatrix(-10000, 10000);
  S21Matrix m2(rows, cols);
  m2.randomInitMatrix(-10000, 10000);
  S21Matrix m1Cpy(m1);
  m1.SumMatrix(m2);
  for (int i = 0; i != rows * cols; ++i) {
    ASSERT_DOUBLE_EQ(m1.getMatrix()[i],
                     m1Cpy.getMatrix()[i] + m2.getMatrix()[i]);
  }
}

TEST_F(testFunctionsMatrix, testSubMatrix_1) {
  S21Matrix m1(11, 5);
  S21Matrix m2(12, 7);
  ASSERT_ANY_THROW(m1.SubMatrix(m2));
}

TEST_F(testFunctionsMatrix, testSubMatrix_2) {
  S21Matrix m1(11, 7);
  S21Matrix m2(12, 7);
  ASSERT_ANY_THROW(m1.SubMatrix(m2));
}

TEST_F(testFunctionsMatrix, testSubMatrix_3) {
  S21Matrix m1(12, 5);
  S21Matrix m2(12, 7);
  ASSERT_ANY_THROW(m1.SubMatrix(m2));
}

TEST_F(testFunctionsMatrix, testSubMatrix_4) {
  int rows = 11;
  int cols = 8;
  S21Matrix m1(rows, cols);
  m1.randomInitMatrix(-10000, 10000);
  S21Matrix m2(rows, cols);
  m2.randomInitMatrix(-10000, 10000);
  S21Matrix m1Cpy(m1);
  m1.SubMatrix(m2);
  for (int i = 0; i != rows * cols; ++i) {
    ASSERT_DOUBLE_EQ(m1.getMatrix()[i],
                     m1Cpy.getMatrix()[i] - m2.getMatrix()[i]);
  }
}

TEST_F(testFunctionsMatrix, testMulNumber) {
  int rows = 11;
  int cols = 1123;
  double dnum = -3.1415926;
  S21Matrix m1(rows, cols);
  m1.randomInitMatrix(-10000, 10000);
  S21Matrix m1Cpy(m1);
  m1.MulNumber(dnum);
  for (int i = 0; i != rows * cols; ++i) {
    ASSERT_DOUBLE_EQ(m1.getMatrix()[i], m1Cpy.getMatrix()[i] * dnum);
  }
}

TEST_F(testFunctionsMatrix, testTranspose_1) {
  int rows = 1;
  int cols = 1;
  S21Matrix m1(rows, cols);
  m1.randomInitMatrix(-10000, 10000);
  S21Matrix mTrn = m1.Transpose();
  for (int i = 0; i != rows * cols; ++i) {
    ASSERT_DOUBLE_EQ(m1.getMatrix()[i], mTrn.getMatrix()[i]);
  }
}

TEST_F(testFunctionsMatrix, testTranspose_2) {
  int rows = 19;
  int cols = 111;
  S21Matrix m1(rows, cols);
  m1.randomInitMatrix(-10000, 10000);
  S21Matrix mTrn = m1.Transpose();
  for (int i = 0; i != rows; ++i) {
    for (int j = 0; j != cols; ++j) {
      ASSERT_DOUBLE_EQ(m1(i, j), mTrn(j, i));
    }
  }
}

TEST_F(testFunctionsMatrix, testTranspose_3) {
  int rows = 1;
  int cols = 11;
  S21Matrix m1(rows, cols);
  m1.randomInitMatrix(-10000, 10000);
  S21Matrix mTrn = m1.Transpose();
  for (int i = 0; i != rows; ++i) {
    for (int j = 0; j != cols; ++j) {
      ASSERT_DOUBLE_EQ(m1(i, j), mTrn(j, i));
    }
  }
}

TEST_F(testFunctionsMatrix, testTranspose_4) {
  int rows = 11;
  int cols = 2;
  S21Matrix m1(rows, cols);
  m1.randomInitMatrix(-10000, 10000);
  S21Matrix mTrn = m1.Transpose();
  for (int i = 0; i != rows; ++i) {
    for (int j = 0; j != cols; ++j) {
      ASSERT_DOUBLE_EQ(m1(i, j), mTrn(j, i));
    }
  }
}

TEST_F(testFunctionsMatrix, testMulMatrix_1) {
  S21Matrix m1(2, 3);
  S21Matrix m2(3, 2);
  for (int i = 0; i != 6; ++i) {
    m1.getMatrix()[i] = i + 1;
    m2.getMatrix()[i] = 6 - i;
  }

  S21Matrix mRes(2, 2);
  mRes(0, 0) = 20;
  mRes(0, 1) = 14;
  mRes(1, 0) = 56;
  mRes(1, 1) = 41;

  m1.MulMatrix(m2);
  ASSERT_DOUBLE_EQ(m1.getRows(), 2);
  ASSERT_DOUBLE_EQ(m1.getCols(), 2);
  for (int i = 0; i != 2; ++i) {
    for (int j = 0; j != 2; ++j) {
      ASSERT_DOUBLE_EQ(m1(i, j), mRes(i, j));
    }
  }
}

TEST_F(testFunctionsMatrix, testMulMatrix_2) {
  S21Matrix m1(3, 2);
  S21Matrix m2(2, 3);
  for (int i = 0; i != 6; ++i) {
    m1.getMatrix()[i] = i + 1;
    m2.getMatrix()[i] = 6 - i;
  }

  S21Matrix mRes(3, 3);
  mRes(0, 0) = 12;
  mRes(0, 1) = 9;
  mRes(0, 2) = 6;
  mRes(1, 0) = 30;
  mRes(1, 1) = 23;
  mRes(1, 2) = 16;
  mRes(2, 0) = 48;
  mRes(2, 1) = 37;
  mRes(2, 2) = 26;

  m1.MulMatrix(m2);
  ASSERT_DOUBLE_EQ(m1.getRows(), 3);
  ASSERT_DOUBLE_EQ(m1.getCols(), 3);
  for (int i = 0; i != 3; ++i) {
    for (int j = 0; j != 3; ++j) {
      ASSERT_DOUBLE_EQ(m1(i, j), mRes(i, j));
    }
  }
}

TEST_F(testFunctionsMatrix, testMulMatrix_3) {
  S21Matrix m1(1, 7);
  S21Matrix m2(7, 1);
  for (int i = 0; i != 7; ++i) {
    m1.getMatrix()[i] = i + 1;
    m2.getMatrix()[i] = 7 - i;
  }

  S21Matrix mRes(1, 1);
  mRes(0, 0) = 84;

  m1.MulMatrix(m2);
  ASSERT_DOUBLE_EQ(m1.getRows(), 1);
  ASSERT_DOUBLE_EQ(m1.getCols(), 1);
  for (int i = 0; i != 1; ++i) {
    for (int j = 0; j != 1; ++j) {
      ASSERT_DOUBLE_EQ(m1(i, j), mRes(i, j));
    }
  }
}

TEST_F(testFunctionsMatrix, testMulMatrix_4) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  for (int i = 0; i != 4; ++i) {
    m1.getMatrix()[i] = i + 1;
    m2.getMatrix()[i] = 4 - i;
  }

  S21Matrix mRes(2, 2);
  mRes(0, 0) = 8;
  mRes(0, 1) = 5;
  mRes(1, 0) = 20;
  mRes(1, 1) = 13;

  m1.MulMatrix(m2);
  ASSERT_DOUBLE_EQ(m1.getRows(), 2);
  ASSERT_DOUBLE_EQ(m1.getCols(), 2);
  for (int i = 0; i != 2; ++i) {
    for (int j = 0; j != 2; ++j) {
      ASSERT_DOUBLE_EQ(m1(i, j), mRes(i, j));
    }
  }
}

TEST_F(testFunctionsMatrix, testMulMatrixException_1) {
  S21Matrix m1(2, 4);
  S21Matrix m2(2, 4);
  for (int i = 0; i != 8; ++i) {
    m1.getMatrix()[i] = i + 1;
    m2.getMatrix()[i] = 8 - i;
  }
  ASSERT_ANY_THROW(m1.MulMatrix(m2));
}

TEST_F(testFunctionsMatrix, testMulMatrixException_2) {
  S21Matrix m1(2, 4);
  S21Matrix m2(4, 8);
  for (int i = 0; i != 8; ++i) {
    m1.getMatrix()[i] = i + 1;
    m2.getMatrix()[i] = 8 - i;
  }
  ASSERT_NO_THROW(m1.MulMatrix(m2));
}

TEST_F(testFunctionsMatrix, testGetMinorMatrix_1) {
  S21Matrix m1(2, 2);
  for (int i = 0; i != 4; ++i) {
    m1.getMatrix()[i] = i + 1;
  }
  for (int i = 0; i != 2; ++i) {
    for (int j = 0; j != 2; ++j) {
      S21Matrix mMinor = m1.GetMinorMatrix(i, j);
      ASSERT_EQ(mMinor.getRows(), m1.getRows() - 1);
      ASSERT_EQ(mMinor.getCols(), m1.getCols() - 1);
      ASSERT_EQ(mMinor.getMatrix()[0], m1(1 - i, 1 - j));
    }
  }
}

TEST_F(testFunctionsMatrix, testGetMinorMatrix_2) {
  S21Matrix m1(2, 2);
  for (int i = 0; i != 4; ++i) {
    m1.randomInitMatrix(-1000, 1000);
  }
  for (int i = 0; i != 2; ++i) {
    for (int j = 0; j != 2; ++j) {
      S21Matrix mMinor = m1.GetMinorMatrix(i, j);
      ASSERT_EQ(mMinor.getRows(), m1.getRows() - 1);
      ASSERT_EQ(mMinor.getCols(), m1.getCols() - 1);
      ASSERT_EQ(mMinor.getMatrix()[0], m1(1 - i, 1 - j));
    }
  }
}

TEST_F(testFunctionsMatrix, testDeterminantMatrix_1) {
  S21Matrix m1(3, 3);
  for (int i = 0; i != 9; ++i) {
    m1.getMatrix()[i] = 2 * i + 1;
  }
  ASSERT_DOUBLE_EQ(m1.Determinant(), 0);
}

TEST_F(testFunctionsMatrix, testDeterminantMatrix_2) {
  S21Matrix m1(2, 2);
  for (int i = 0; i != 4; ++i) {
    m1.getMatrix()[i] = i * i + 0.8;
  }
  ASSERT_TRUE((-0.8 - m1.Determinant()) <= m1.EPSILON);
}

TEST_F(testFunctionsMatrix, testDetInverseCalcComplMatrixException_1) {
  S21Matrix m1(2, 3);
  for (int i = 0; i != 6; ++i) {
    m1.getMatrix()[i] = i * i + 1;
  }
  ASSERT_ANY_THROW(m1.Determinant());
  ASSERT_ANY_THROW(m1.InverseMatrix());
  ASSERT_ANY_THROW(m1.CalcComplements());
}

TEST_F(testFunctionsMatrix, testDetInverseCalcComplMatrixException_2) {
  S21Matrix m1(4, 3);
  for (int i = 0; i != 12; ++i) {
    m1.getMatrix()[i] = i + 1;
  }
  ASSERT_ANY_THROW(m1.Determinant());
  ASSERT_ANY_THROW(m1.InverseMatrix());
  ASSERT_ANY_THROW(m1.CalcComplements());
}

TEST_F(testFunctionsMatrix, testDetInverseCalcComplMatrixException_3) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 25;
  m1(0, 1) = 24;
  m1(1, 0) = 20;
  m1(1, 1) = 19;

  ASSERT_NO_THROW(m1.Determinant());
  ASSERT_NO_THROW(m1.InverseMatrix());
  ASSERT_NO_THROW(m1.CalcComplements());
}

TEST_F(testFunctionsMatrix, testInverseMatrixException_DetEq0) {
  S21Matrix m1(3, 3);
  for (int i = 0; i != 9; ++i) {
    m1.getMatrix()[i] = i + 1;
  }
  ASSERT_ANY_THROW(m1.InverseMatrix());
}

TEST_F(testFunctionsMatrix, testInverseMatrix_1) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 25;
  m1(0, 1) = 24;
  m1(1, 0) = 20;
  m1(1, 1) = 19;

  S21Matrix mInv(2, 2);
  mInv(0, 0) = -3.8;
  mInv(0, 1) = 4.8;
  mInv(1, 0) = 4;
  mInv(1, 1) = -5;

  S21Matrix m2 = m1.InverseMatrix();
  for (int i = 0; i != 2; ++i) {
    for (int j = 0; j != 2; ++j) {
      ASSERT_TRUE((m2(i, j) - mInv(i, j)) < m1.EPSILON);
    }
  }
}
