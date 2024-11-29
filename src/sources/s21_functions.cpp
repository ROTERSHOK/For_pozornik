#include "../s21_matrix_oop.h"

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (matrix_[i][j] != other.matrix_[i][j]) {
        return false;
      }
    }
  }

  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument(
        "Matrices must have the same dimensions for addition.");
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument(
        "Matrices must have the same dimensions for subtraction.");
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (this->cols_ != other.rows_) {
    throw std::invalid_argument(
        "The number of columns in the first matrix must match the number of "
        "rows in the second matrix.");
  }

  S21Matrix result(rows_, other.cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }

  *this = result;

  cols_ = other.cols_;
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(rows_, cols_);

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      result.matrix_[i][j] = matrix_[j][i];
    }
  }

  return result;
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::invalid_argument("Matrix must be square.");
  }

  double result = 0.0;

  if (rows_ == 1) {
    result = matrix_[0][0];
  } else if (rows_ == 2) {
    result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    for (int col = 0; col < cols_; ++col) {
      S21Matrix minor(rows_ - 1, cols_ - 1);

      for (int i = 1; i < rows_; ++i) {
        int minor_col = 0;
        for (int j = 0; j < cols_; ++j) {
          if (j != col) {
            minor.matrix_[i - 1][minor_col] = matrix_[i][j];
            minor_col++;
          }
        }
      }

      result += (col % 2 == 0 ? 1 : -1) * matrix_[0][col] * minor.Determinant();
    }
  }

  return result;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) {
    throw std::invalid_argument("Matrix must be square.");
  }

  S21Matrix result(rows_, cols_);

  if (rows_ == 1 && cols_ == 1) {
    result.matrix_[0][0] = matrix_[0][0];
    return result;
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      S21Matrix minor(rows_ - 1, cols_ - 1);

      for (int mi = 0; mi < rows_; ++mi) {
        for (int mj = 0; mj < cols_; ++mj) {
          if (mi != i && mj != j) {
            int minor_i = mi < i ? mi : mi - 1;
            int minor_j = mj < j ? mj : mj - 1;
            minor.matrix_[minor_i][minor_j] = matrix_[mi][mj];
          }
        }
      }

      result.matrix_[i][j] = ((i + j) % 2 == 0 ? 1 : -1) * minor.Determinant();
    }
  }

  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Matrix must be square.");
  }

  double det = Determinant();
  if (det == 0) {
    throw std::invalid_argument("Matrix is singular and cannot be inverted.");
  }

  S21Matrix result = CalcComplements().Transpose();
  result.MulNumber(1.0 / det);

  return result;
}