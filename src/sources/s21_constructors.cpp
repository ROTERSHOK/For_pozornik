#include "../s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::invalid_argument(
        "The number of rows or columns is less than zero.");
  }

  matrix_ = new double*[rows];

  for (int i = 0; i < rows; ++i) {
    matrix_[i] = new double[cols]();
  }
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = new double*[rows_];

  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]();

    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix::~S21Matrix() {
  for (int i = 0; i < rows_; ++i) {
    delete[] matrix_[i];
  }

  delete[] matrix_;
}

int S21Matrix::getRows() const { return rows_; }

int S21Matrix::getCols() const { return cols_; }

double** S21Matrix::getMatrix() const { return matrix_; };

void S21Matrix::setRows(int newRows) {
  if (newRows <= 0) {
    throw std::invalid_argument("Number of rows must be greater than zero.");
  }

  S21Matrix temp(newRows, cols_);

  for (int i = 0; i < std::min(rows_, newRows); ++i) {
    for (int j = 0; j < cols_; ++j) {
      temp.matrix_[i][j] = matrix_[i][j];
    }
  }

  *this = temp;
}

void S21Matrix::setCols(int newCols) {
  if (newCols <= 0) {
    throw std::invalid_argument("Number of columns must be greater than zero.");
  }

  S21Matrix temp(rows_, newCols);

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < std::min(cols_, newCols); ++j) {
      temp.matrix_[i][j] = matrix_[i][j];
    }
  }

  *this = temp;
}