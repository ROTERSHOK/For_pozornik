#include "../s21_matrix_oop.h"

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this == &other) {
    return *this;
  }

  for (int i = 0; i < rows_; ++i) {
    delete[] matrix_[i];
  }
  delete[] matrix_;

  rows_ = other.rows_;
  cols_ = other.cols_;

  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }

  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument(
        "Matrices must have the same dimensions for addition.");
  }

  S21Matrix result(*this);
  result.SumMatrix(other);

  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument(
        "Matrices must have the same dimensions for subtraction.");
  }

  S21Matrix result(*this);
  result.SubMatrix(other);

  return result;
}

S21Matrix S21Matrix::operator*(double num) const {
  S21Matrix result(*this);
  result.MulNumber(num);

  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "The number of columns in the first matrix must match the number of "
        "rows in the second matrix.");
  }

  S21Matrix result = *this;
  result *= other;

  return result;
}

bool S21Matrix::operator==(const S21Matrix& other) const {
  return EqMatrix(other);
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  this->SumMatrix(other);

  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  this->SubMatrix(other);

  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  this->MulMatrix(other);

  return *this;
}

S21Matrix& S21Matrix::operator*=(const double num) {
  this->MulNumber(num);

  return *this;
}

double& S21Matrix::operator()(int i, int j) {
  if ((i < 0 || i >= rows_) || (j < 0 || j >= cols_)) {
    throw std::out_of_range("Index out of range.");
  }

  return matrix_[i][j];
}

double* S21Matrix::operator[](int index) { return this->matrix_[index]; }