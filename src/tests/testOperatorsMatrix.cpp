#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

struct testOperatorsMatrix : ::testing::Test {};

TEST_F(testOperatorsMatrix, testOperatorPlus) {
  int rows = 15;
  int cols = 15;
  S21Matrix m1(rows, cols);
  m1.randomInitMatrix(-10000, 10000);
  S21Matrix m2(rows, cols);
  m2.randomInitMatrix(-10000, 10000);
  S21Matrix m3 = m1 + m2;
  for (int i = 0; i != rows * cols; ++i) {
    ASSERT_DOUBLE_EQ(m3.getMatrix()[i], m1.getMatrix()[i] + m2.getMatrix()[i]);
  }
}

TEST_F(testOperatorsMatrix, testOperatorPlusIsEq) {
  int rows = 8;
  int cols = 8;
  S21Matrix m1(rows, cols);
  m1.randomInitMatrix(-10000, 10000);
  S21Matrix m2(rows, cols);
  m2.randomInitMatrix(-10000, 10000);
  S21Matrix m1Cpy(m1);
  m1 += m2;
  for (int i = 0; i != rows * cols; ++i) {
    ASSERT_DOUBLE_EQ(m1.getMatrix()[i],
                     m1Cpy.getMatrix()[i] + m2.getMatrix()[i]);
  }
}

TEST_F(testOperatorsMatrix, testOperatorMinus) {
  int rows = 12;
  int cols = 19;
  S21Matrix m1(rows, cols);
  m1.randomInitMatrix(-10000, 10000);
  S21Matrix m2(rows, cols);
  m2.randomInitMatrix(-10000, 10000);
  S21Matrix m3 = m1 - m2;
  for (int i = 0; i != rows * cols; ++i) {
    ASSERT_DOUBLE_EQ(m3.getMatrix()[i], m1.getMatrix()[i] - m2.getMatrix()[i]);
  }
}

TEST_F(testOperatorsMatrix, testOperatorMinusIsEq) {
  int rows = 11;
  int cols = 23;
  S21Matrix m1(rows, cols);
  m1.randomInitMatrix(-10000, 10000);
  S21Matrix m2(rows, cols);
  m2.randomInitMatrix(-10000, 10000);
  S21Matrix m1Cpy(m1);
  m1 -= m2;
  for (int i = 0; i != rows * cols; ++i) {
    ASSERT_DOUBLE_EQ(m1.getMatrix()[i],
                     m1Cpy.getMatrix()[i] - m2.getMatrix()[i]);
  }
}

TEST_F(testOperatorsMatrix, testOperatorMulNumber) {
  int rows = 11;
  int cols = 111;
  double dnum = -3.1415926;
  S21Matrix m1(rows, cols);
  m1.randomInitMatrix(-10000, 10000);
  // S21Matrix m1Cpy(m1);
  S21Matrix m2 = m1 * dnum;
  for (int i = 0; i != rows * cols; ++i) {
    ASSERT_DOUBLE_EQ(m2.getMatrix()[i], m1.getMatrix()[i] * dnum);
  }
}

TEST_F(testOperatorsMatrix, testOperatorMulIsEqNum) {
  int rows = 100;
  int cols = 10;
  double dnum = -3.1415926;
  S21Matrix m1(rows, cols);
  m1.randomInitMatrix(-10000, 10000);
  S21Matrix m1Cpy(m1);
  m1 *= dnum;
  for (int i = 0; i != rows * cols; ++i) {
    ASSERT_DOUBLE_EQ(m1.getMatrix()[i], m1Cpy.getMatrix()[i] * dnum);
  }
}

TEST_F(testOperatorsMatrix, testOperatorBraketsThrow_1) {
  int rows = 11;
  int cols = 5;
  S21Matrix m1(rows, cols);
  m1.randomInitMatrix(-10000, 10000);
  ASSERT_ANY_THROW(m1(-1, 4));
}

TEST_F(testOperatorsMatrix, testOperatorBraketsThrow_2) {
  int rows = 11;
  int cols = 5;
  S21Matrix m1(rows, cols);
  m1.randomInitMatrix(-10000, 10000);
  ASSERT_ANY_THROW(m1(1, -3));
}

TEST_F(testOperatorsMatrix, testOperatorBraketsThrow_3) {
  int rows = 11;
  int cols = 5;
  S21Matrix m1(rows, cols);
  m1.randomInitMatrix(-10000, 10000);
  ASSERT_ANY_THROW(m1(3, 5));
}

TEST_F(testOperatorsMatrix, testOperatorBraketsThrow_4) {
  int rows = 11;
  int cols = 5;
  S21Matrix m1(rows, cols);
  m1.randomInitMatrix(-10000, 10000);
  ASSERT_ANY_THROW(m1(11, 4));
}

TEST_F(testOperatorsMatrix, testOperatorBraketsConstThrow_1) {
  int rows = 11;
  int cols = 5;
  const S21Matrix m1(rows, cols);
  ASSERT_ANY_THROW(m1(2, -5));
}

TEST_F(testOperatorsMatrix, testOperatorBraketsConstThrow_2) {
  int rows = 11;
  int cols = 5;
  const S21Matrix m1(rows, cols);
  ASSERT_ANY_THROW(m1(-3, 4));
}

TEST_F(testOperatorsMatrix, testOperatorBraketsConstThrow_3) {
  int rows = 11;
  int cols = 5;
  const S21Matrix m1(rows, cols);
  ASSERT_ANY_THROW(m1(10, 5));
}

TEST_F(testOperatorsMatrix, testOperatorBraketsConstThrow_4) {
  int rows = 11;
  int cols = 5;
  const S21Matrix m1(rows, cols);
  ASSERT_ANY_THROW(m1(11, 4));
}

TEST_F(testOperatorsMatrix, testOperatorBraketsConstThrow_5) {
  int rows = 11;
  int cols = 5;
  const S21Matrix m1(rows, cols);
  double dnum = m1(0, 0);
  ASSERT_DOUBLE_EQ(m1(0, 0), dnum);
}

TEST_F(testOperatorsMatrix, testOperatorIsEq_1) {
  int rows = 11;
  int cols = 5;
  S21Matrix m1(rows, cols);
  S21Matrix m2;
  m2 = m1;
  ASSERT_TRUE(m1 == m2);
}

TEST_F(testOperatorsMatrix, testOperatorIsEq_2) {
  int rows = 8;
  int cols = 23;
  S21Matrix m1(rows, cols);
  S21Matrix m1Cpy(m1);
  m1 = m1;
  ASSERT_TRUE(m1 == m1Cpy);
}

TEST_F(testOperatorsMatrix, testOperatorMulIsEqMatrix_1) {
  S21Matrix m1(2, 5);
  S21Matrix m2(5, 2);
  for (int i = 0; i != 10; ++i) {
    m1.getMatrix()[i] = i + 1;
    m2.getMatrix()[i] = 10 - i;
  }

  S21Matrix mRes(2, 2);
  mRes(0, 0) = 70;
  mRes(0, 1) = 55;
  mRes(1, 0) = 220;
  mRes(1, 1) = 180;

  m1 *= m2;
  ASSERT_DOUBLE_EQ(m1.getRows(), 2);
  ASSERT_DOUBLE_EQ(m1.getCols(), 2);
  for (int i = 0; i != 2; ++i) {
    for (int j = 0; j != 2; ++j) {
      ASSERT_DOUBLE_EQ(m1(i, j), mRes(i, j));
    }
  }
}

TEST_F(testOperatorsMatrix, testOperatorMulIsEqMatrix_2) {
  S21Matrix m1(3, 4);
  S21Matrix m2(4, 3);
  for (int i = 0; i != 12; ++i) {
    m1.getMatrix()[i] = i + 1;
    m2.getMatrix()[i] = 12 - i;
  }

  S21Matrix mRes(3, 3);
  mRes(0, 0) = 60;
  mRes(0, 1) = 50;
  mRes(0, 2) = 40;
  mRes(1, 0) = 180;
  mRes(1, 1) = 154;
  mRes(1, 2) = 128;
  mRes(2, 0) = 300;
  mRes(2, 1) = 258;
  mRes(2, 2) = 216;

  m1 *= m2;
  ASSERT_DOUBLE_EQ(m1.getRows(), 3);
  ASSERT_DOUBLE_EQ(m1.getCols(), 3);
  for (int i = 0; i != 3; ++i) {
    for (int j = 0; j != 3; ++j) {
      ASSERT_DOUBLE_EQ(m1(i, j), mRes(i, j));
    }
  }
}

TEST_F(testOperatorsMatrix, testOperatorMulMatrix_1) {
  S21Matrix m1(1, 5);
  S21Matrix m2(5, 1);
  for (int i = 0; i != 5; ++i) {
    m1.getMatrix()[i] = 2 * i + 1;
    m2.getMatrix()[i] = 5 - i;
  }

  S21Matrix mRes(1, 1);
  mRes(0, 0) = 55;

  S21Matrix m3 = m1 * m2;
  ASSERT_DOUBLE_EQ(m3.getRows(), 1);
  ASSERT_DOUBLE_EQ(m3.getCols(), 1);
  for (int i = 0; i != 1; ++i) {
    for (int j = 0; j != 1; ++j) {
      ASSERT_DOUBLE_EQ(m3(i, j), mRes(i, j));
    }
  }
}

TEST_F(testOperatorsMatrix, testOperatorMulMatrix_2) {
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

  S21Matrix m3 = m1 * m2;
  ASSERT_DOUBLE_EQ(m3.getRows(), 2);
  ASSERT_DOUBLE_EQ(m3.getCols(), 2);
  for (int i = 0; i != 2; ++i) {
    for (int j = 0; j != 2; ++j) {
      ASSERT_DOUBLE_EQ(m3(i, j), mRes(i, j));
    }
  }
}

TEST_F(testOperatorsMatrix, testOperatorMulIsEqMatrixException_1) {
  S21Matrix m1(1, 8);
  S21Matrix m2(2, 4);
  for (int i = 0; i != 8; ++i) {
    m1.getMatrix()[i] = i + 1;
    m2.getMatrix()[i] = 8 - i;
  }
  ASSERT_ANY_THROW(m1 *= m2);
}

TEST_F(testOperatorsMatrix, testMulIsEqMatrixException_2) {
  S21Matrix m1(2, 4);
  S21Matrix m2(4, 8);
  for (int i = 0; i != 8; ++i) {
    m1.getMatrix()[i] = i + 1;
    m2.getMatrix()[i] = 8 - i;
  }
  ASSERT_NO_THROW(m1 *= m2);
}
