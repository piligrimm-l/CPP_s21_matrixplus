#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() noexcept : rows_{0}, cols_{0}, matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_{rows}, cols_{cols} {
  if (rows_ < 0 || cols_ < 0) {
    throw std::length_error(
        "\nКоличество строк/столбцов матрицы должно быть\
>= 0\nThe number of rows and columns of the matrix must be >=0");
  }
  handling_memalloc_exception(*this);
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_{other.rows_}, cols_{other.cols_} {
  handling_memalloc_exception(*this);
  std::memcpy(matrix_, other.matrix_,
              other.rows_ * other.cols_ * sizeof(double));
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_{other.rows_}, cols_{other.cols_}, matrix_{other.matrix_} {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix::~S21Matrix() { delete[] matrix_; }

int S21Matrix::getRows() const noexcept { return rows_; }

int S21Matrix::getCols() const noexcept { return cols_; }

double* S21Matrix::getMatrix() const noexcept { return matrix_; }

void S21Matrix::setRows(int rows) {
  if (rows < 0) {
    throw std::length_error(
        "Количество строк матрицы не может быть\
отрицательным\nMatrix rows count must be non-negative\n");
  }
  int newRows = (rows >= rows_) ? rows_ : rows;
  S21Matrix tmp(rows, cols_);
  for (int i = 0; i != newRows; ++i) {
    for (int j = 0; j != cols_; ++j) {
      tmp(i, j) = (*this)(i, j);
    }
  }
  *this = std::move(tmp);
}

void S21Matrix::setCols(int cols) {
  if (cols < 0) {
    throw std::length_error(
        "Количество столбцов матрицы не может быть\
отрицательным\nMatrix cols count must be non-negative\n");
  }
  int newCols = (cols >= cols_) ? cols_ : cols;
  S21Matrix tmp(rows_, cols);
  for (int i = 0; i != rows_; ++i) {
    for (int j = 0; j != newCols; ++j) {
      tmp(i, j) = (*this)(i, j);
    }
  }
  *this = std::move(tmp);
}

bool S21Matrix::EqMatrix(const S21Matrix& other) noexcept {
  if (rows_ != other.rows_ || cols_ != other.cols_) return false;

  for (int i = 0; i != rows_ * cols_; ++i) {
    if (matrix_[i] != other.matrix_[i]) return false;
  }

  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Размеры матриц должны быть одинаковыми\n\
Incorrect input, matrices should have the same size");
  }

  for (auto i = 0; i < rows_ * cols_; ++i) {
    matrix_[i] += other.matrix_[i];
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Размеры матриц должны быть одинаковыми\n\
Incorrect input, matrices should have the same size");
  }
  for (auto i = 0; i < rows_ * cols_; ++i) {
    matrix_[i] -= other.matrix_[i];
  }
}

void S21Matrix::MulNumber(const double num) noexcept {
  for (int i = 0; i != rows_ * cols_; ++i) {
    matrix_[i] *= num;
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::logic_error(
        "Невозможно перемножить матрицы таких размеров\n\
Incorrect matrix size for Multiplication");
  }
  S21Matrix mMult(rows_, other.cols_);
  for (int i = 0; i != rows_; ++i) {
    for (int j = 0; j != other.cols_; ++j) {
      for (int k = 0; k != cols_; ++k) {
        mMult(i, j) += (*this)(i, k) * other(k, j);
      }
    }
  }
  *this = std::move(mMult);
}

S21Matrix S21Matrix::Transpose() const noexcept {
  S21Matrix trnMatrix(cols_, rows_);
  for (int i = 0; i != cols_; ++i) {
    for (int j = 0; j != rows_; ++j) {
      trnMatrix(i, j) = (*this)(j, i);
    }
  }
  return trnMatrix;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) {
    throw std::logic_error("Incorrect matrix size for CalcComplements");
  }
  S21Matrix result{rows_, cols_};
  for (int i = 0; i != rows_; ++i) {
    for (int j = 0; j != cols_; ++j) {
      S21Matrix mMinor = GetMinorMatrix(i, j);
      result(i, j) = mMinor.Determinant();
      if ((i + j) % 2 != 0) {
        result(i, j) = -result(i, j);
      }
    }
  }
  return result;
}

void S21Matrix::SwapRows(int row1, int row2) noexcept {
  if (row1 != row2) {
    for (int i = 0; i != cols_; ++i) {
      std::swap((*this)(row1, i), (*this)(row2, i));
    }
  }
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::logic_error("Incorrect matrix size for Determinant");
  }

  double result = 1.0;
  S21Matrix tmp{*this};
  int size = rows_;

  for (int i = 0; i < size; ++i) {
    int pivoting = i;
    for (int j = i + 1; j < size; ++j) {
      if (std::abs(tmp(j, i)) > std::abs(tmp(pivoting, i))) {
        pivoting = j;
      }
    }

    if (std::abs(tmp(pivoting, i)) < EPSILON) {
      return 0.0;
    }

    tmp.SwapRows(i, pivoting);

    result *= tmp(i, i);

    if (i != pivoting) {
      result = -result;
    }

    for (int j = i + 1; j != size; ++j) {
      double koef = tmp(j, i) / tmp(i, i);
      for (int k = i; k != size; ++k) {
        tmp(j, k) -= tmp(i, k) * koef;
      }
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() const {
  if (rows_ != cols_) {
    throw std::logic_error("Incorrect matrix size for Inverse");
  }

  double det = Determinant();

  if (std::abs(det) < EPSILON) {
    throw std::logic_error("Determinant must be non-zero to calculate Inverse");
  }

  return Transpose().CalcComplements() * (1.0 / det);
}

S21Matrix S21Matrix::GetMinorMatrix(const int skipRow,
                                    const int skipCol) const {
  S21Matrix mMinor{rows_ - 1, cols_ - 1};

  for (int i = 0, k = 0; i != rows_; ++i, ++k) {
    if (i == skipRow) {
      --k;
      continue;
    }
    for (int j = 0, l = 0; j != cols_; ++j, ++l) {
      if (j == skipCol) {
        --l;
        continue;
      }
      mMinor(k, l) = (*this)(i, j);
    }
  }

  return mMinor;
}

// operator+ overload
S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix mCpy(*this);
  mCpy.SumMatrix(other);
  return mCpy;
}

// operator+= overload
S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  this->SumMatrix(other);
  return *this;
}

// operator- overload
S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix mCpy(*this);
  mCpy.SubMatrix(other);
  return mCpy;
}

// operator-= overload
S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  this->SubMatrix(other);
  return *this;
}

// operator* overload
S21Matrix S21Matrix::operator*(const double dnum) {
  S21Matrix mCpy(*this);
  mCpy.MulNumber(dnum);
  return mCpy;
}

// operator*= overload
S21Matrix& S21Matrix::operator*=(const double dnum) {
  this->MulNumber(dnum);
  return *this;
}

// operator* overload
S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix mCpy(*this);
  mCpy.MulMatrix(other);
  return mCpy;
}

// operator*= overload
S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  this->MulMatrix(other);
  return *this;
}

// operator() overload
double& S21Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix_[row * cols_ + col];
}

// operator() overload
double& S21Matrix::operator()(int row, int col) const {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix_[row * cols_ + col];
}

// operator== overload
bool S21Matrix::operator==(const S21Matrix& other) { return EqMatrix(other); }

// operator= overload
S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (matrix_ == other.getMatrix()) {
    return *this;
  }
  resetMatrix();
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = new double[rows_ * cols_];
  for (int i = 0; i != rows_ * cols_; ++i) {
    matrix_[i] = other.matrix_[i];
  }
  return *this;
}

// operator= overload
S21Matrix& S21Matrix::operator=(S21Matrix&& other) {
  if (this != &other) {
    resetMatrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    std::swap(matrix_, other.matrix_);
  }
  return *this;
}

void handling_memalloc_exception(S21Matrix& m) {
  try {
    m.matrix_ = new double[m.rows_ * m.cols_]{};
  } catch (std::bad_alloc& ba) {
    std::cerr << "bad_alloc caught: " << ba.what() << '\n';
  }
}

void S21Matrix::resetMatrix() {
  if (matrix_) {
    delete[] matrix_;
    matrix_ = nullptr;
    rows_ = 0;
    cols_ = 0;
  }
}

void S21Matrix::randomInitMatrix(double min, double max) noexcept {
  for (int i = 0; i != rows_ * cols_; ++i) {
    matrix_[i] = getRandomNumber(min, max);
  }
}

double getRandomNumber(double min, double max) {
  double res = 0;
  srand(static_cast<unsigned int>(time(0)));
  static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
  do {
    res = static_cast<double>(rand() * fraction * (max - min + 1) + min);
  } while (res < min || res > max);
  return res;
}
