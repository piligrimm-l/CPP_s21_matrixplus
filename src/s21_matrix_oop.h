#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <cstdlib>  // srand(), rand()
#include <cstring>  // memcpy()
#include <ctime>    // time(0)
#include <iostream>
#include <new>  // bad_alloc()
#include <stdexcept>
#include <utility>  // swap()

class S21Matrix {
 private:
  int rows_;
  int cols_;
  double *matrix_;

 public:
  const double EPSILON = 1e-7;
  S21Matrix() noexcept;                    // default constructor
  explicit S21Matrix(int rows, int cols);  // parameterized constructor
  S21Matrix(const S21Matrix &other);       // copy constructor
  S21Matrix(S21Matrix &&other) noexcept;   // move constructor
  ~S21Matrix();                            // destructor

  int getRows() const noexcept;
  int getCols() const noexcept;
  double *getMatrix() const noexcept;
  void setRows(int rows);
  void setCols(int cols);

  // some operators overloads
  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix operator*(const double num);
  friend S21Matrix operator*(double num, const S21Matrix &other);
  bool operator==(const S21Matrix &other);
  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator=(S21Matrix &&other);
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix &operator*=(const double num);
  friend S21Matrix operator*=(double num, const S21Matrix &other);
  double &operator()(int row, int col);
  double &operator()(int row, int col) const;

  // some public methods
  bool EqMatrix(const S21Matrix &other) noexcept;
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num) noexcept;
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose() const noexcept;

  S21Matrix CalcComplements() const;
  void SwapRows(int row1, int row2) noexcept;
  double Determinant() const;
  S21Matrix InverseMatrix() const;
  S21Matrix GetMinorMatrix(const int skipRow, const int skipCol) const;

  friend void handling_memalloc_exception(S21Matrix &m);
  void randomInitMatrix(double min, double max) noexcept;
  void resetMatrix();
};

double getRandomNumber(double min, double max);
#endif
