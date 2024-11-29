#include <gtest/gtest.h>

#include <cmath>

#include "../s21_matrix_oop.h"

TEST(Constructor_default, Constructor_default) {
  S21Matrix matrix = S21Matrix();

  EXPECT_TRUE(matrix.getRows() == 0);
  EXPECT_TRUE(matrix.getCols() == 0);
  EXPECT_TRUE(matrix.getMatrix() == nullptr);
}

TEST(Constructor_rowscols, allocate) {
  S21Matrix matrix(100, 100);

  bool flag = true;
  for (int i = 0; (i < 100) && flag; ++i) {
    for (int j = 0; (j < 100) && flag; ++j) flag = matrix[i][j] == 0.0;
  }

  EXPECT_TRUE(flag);
}

TEST(Constructor_rowscols, invalid) {
  bool flag = false;

  try {
    S21Matrix matrix(0, 0);
  } catch (const std::exception& e) {
    flag = true;
  }

  EXPECT_TRUE(flag);
}

TEST(Constructor_copy, Constructor_copy) {
  S21Matrix matrix_1(1, 1);
  matrix_1[0][0] = 1.0;

  S21Matrix matrix_2(matrix_1);

  EXPECT_TRUE(matrix_2.getRows() == 1);
  EXPECT_TRUE(matrix_2.getCols() == 1);
  EXPECT_TRUE(matrix_2[0][0] = 1.0);
}

TEST(Constructor_move, Constructor_move) {
  S21Matrix matrix_1(1, 1);
  matrix_1[0][0] = 1.0;

  S21Matrix matrix_2 = std::move(matrix_1);

  EXPECT_TRUE(matrix_2[0][0] == 1.0);
  EXPECT_TRUE(matrix_1.getRows() == 0);
  EXPECT_TRUE(matrix_1.getCols() == 0);
  EXPECT_TRUE(matrix_1.getMatrix() == nullptr);
}

TEST(setRows, setRows) {
  S21Matrix matrix(1, 1);
  matrix[0][0] = 1.0;

  matrix.setRows(2);

  EXPECT_TRUE(matrix[0][0] == 1.0);
  EXPECT_TRUE(matrix[1][0] == 0.0);
}

TEST(setCols, setCols) {
  S21Matrix matrix(1, 1);
  matrix[0][0] = 1.0;

  matrix.setCols(2);

  EXPECT_TRUE(matrix[0][0] == 1.0);
  EXPECT_TRUE(matrix[0][1] == 0.0);
}

// EqMatrix

TEST(EqMatrix, different_sizes) {
  S21Matrix matrix_1(1, 2);
  S21Matrix matrix_2(1, 1);

  EXPECT_FALSE(matrix_1 == matrix_2);
}

TEST(EqMatrix, equal_matrices) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(2, 2);

  EXPECT_TRUE(matrix_1 == matrix_2);
}

TEST(NotEqMatrix, equal_matrices) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(3, 2);

  EXPECT_FALSE(matrix_1 == matrix_2);
}

// SumMatrix

TEST(SumMatrix, different_sizes) {
  S21Matrix matrix_1(1, 2);
  S21Matrix matrix_2(2, 2);

  bool flag = false;

  try {
    S21Matrix result = matrix_1 + matrix_2;
  } catch (const std::exception& e) {
    flag = true;
  }

  EXPECT_TRUE(flag);
}

TEST(SumMatrix, sum_test) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(2, 2);

  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      matrix_1[i][j] = 1.0;
      matrix_2[i][j] = 3.0;
    }
  }

  S21Matrix result = matrix_1 + matrix_2;

  bool result_ = true;

  for (int i = 0; (i < 2) && result_; ++i) {
    for (int j = 0; (j < 2) && result_; ++j) {
      result_ = result[i][j] == 4.0;
    }
  }

  EXPECT_TRUE(result_);
}

// SubMatrix

TEST(SubMatrix, different_sizes) {
  S21Matrix matrix_1(1, 2);
  S21Matrix matrix_2(2, 2);

  bool flag = false;

  try {
    S21Matrix result = matrix_1 - matrix_2;
  } catch (const std::exception& e) {
    flag = true;
  }

  EXPECT_TRUE(flag);
}

TEST(SubMatrix, sum_test) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(2, 2);

  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      matrix_1[i][j] = 1.0;
      matrix_2[i][j] = 3.0;
    }
  }

  S21Matrix result_ = matrix_1 - matrix_2;

  bool result = true;

  for (int i = 0; (i < 2) && result; ++i) {
    for (int j = 0; (j < 2) && result; ++j) {
      result = result_[i][j] == -2.0;
    }
  }

  EXPECT_TRUE(result);
}

TEST(MulNumber, MulNumber) {
  S21Matrix matrix_1(2, 2);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) matrix_1[i][j] = 1.0;
  }

  S21Matrix result = matrix_1 * 3.0;

  bool flag = true;
  for (int i = 0; (i < 2) && flag; ++i) {
    for (int j = 0; (j < 2) && flag; ++j) flag = result[i][j] == 3.0;
  }

  EXPECT_TRUE(flag);
}

TEST(MulMatrix, incorrect_data) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(3, 3);

  bool flag = false;

  try {
    S21Matrix result = matrix_1 * matrix_2;
  } catch (const std::exception& e) {
    flag = true;
  }

  EXPECT_TRUE(flag);
}

TEST(MulMatrix, normal_values) {
  S21Matrix matrix_1(2, 1);
  S21Matrix matrix_2(1, 2);

  matrix_1[0][0] = 1;
  matrix_1[1][0] = 1;

  matrix_2[0][0] = 2;
  matrix_2[0][1] = 3;

  S21Matrix result(matrix_2 * matrix_1);

  EXPECT_EQ(result[0][0], 5.0);
}

TEST(Transpose, normal_values) {
  S21Matrix matrix_1(2, 2);

  matrix_1[0][0] = 1;
  matrix_1[0][1] = 2;
  matrix_1[1][0] = 3;
  matrix_1[1][1] = 4;

  S21Matrix matrix_2 = matrix_1.Transpose();

  EXPECT_TRUE(matrix_2[0][0] == 1);
  EXPECT_TRUE(matrix_2[0][1] == 3);
  EXPECT_TRUE(matrix_2[1][0] == 2);
  EXPECT_TRUE(matrix_2[1][1] == 4);
}

TEST(Calc_complements, invalid_value) {
  S21Matrix matrix(3, 2);

  bool flag = false;
  try {
    matrix.CalcComplements();
  } catch (const std::exception& e) {
    flag = true;
  }

  EXPECT_TRUE(flag);
}

TEST(Calc_complements, normal_values) {
  S21Matrix matrix(2, 2);

  matrix[0][0] = 1;
  matrix[0][1] = 2;
  matrix[1][0] = 5;
  matrix[1][1] = 6;

  S21Matrix complements = matrix.CalcComplements();

  EXPECT_TRUE(complements[0][0] = 6.0);
  EXPECT_TRUE(complements[0][1] == -5.0);
  EXPECT_TRUE(complements[1][0] == -2.0);
  EXPECT_TRUE(complements[1][1] == 1.0);
}

TEST(Calc_complemets, normal_values_2) {
  S21Matrix matrix(3, 3);

  matrix[0][0] = 5;
  matrix[0][1] = 7;
  matrix[0][2] = 1;

  matrix[1][0] = -4;
  matrix[1][1] = 1;
  matrix[1][2] = 0;

  matrix[2][0] = 2;
  matrix[2][1] = 0;
  matrix[2][2] = 3;

  S21Matrix complements = matrix.CalcComplements();

  EXPECT_TRUE(complements[0][0] == 3.0);
  EXPECT_TRUE(complements[0][1] == 12.0);
  EXPECT_TRUE(complements[0][2] == -2.0);

  EXPECT_TRUE(complements[1][0] == -21.0);
  EXPECT_TRUE(complements[1][1] == 13.0);
  EXPECT_TRUE(complements[1][2] == 14.0);

  EXPECT_TRUE(complements[2][0] == -1.0);
  EXPECT_TRUE(complements[2][1] == -4.0);
  EXPECT_TRUE(complements[2][2] == 33.0);
}

TEST(Determinant, invalid_values) {
  S21Matrix matrix(3, 2);

  bool flag = false;

  try {
    matrix.Determinant();
  } catch (const std::exception& e) {
    flag = true;
  }

  EXPECT_TRUE(flag);
}

TEST(Determinant, normal_values) {
  S21Matrix matrix(3, 3);

  matrix[0][0] = 3;
  matrix[0][1] = 2;
  matrix[0][2] = 1;

  matrix[1][0] = 10;
  matrix[1][1] = 12;
  matrix[1][2] = 13;

  matrix[2][0] = 5;
  matrix[2][1] = 6;
  matrix[2][2] = 4;

  double det = matrix.Determinant();

  EXPECT_TRUE(det == -40.0);
}

TEST(Complement, one_to_one) {
  S21Matrix matrix(1, 1);
  matrix[0][0] = 5;

  S21Matrix result = matrix.CalcComplements();

  EXPECT_EQ(result[0][0], 5);
}

TEST(S21MatrixTest, InverseMatrix_Valid) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 4;
  matrix(0, 1) = 7;
  matrix(1, 0) = 2;
  matrix(1, 1) = 6;

  S21Matrix expected(2, 2);
  expected(0, 0) = 0.6;
  expected(0, 1) = -0.7;
  expected(1, 0) = -0.2;
  expected(1, 1) = 0.4;

  S21Matrix result = matrix.InverseMatrix();

  EXPECT_NEAR(result(0, 0), expected(0, 0), 1e-9);
  EXPECT_NEAR(result(0, 1), expected(0, 1), 1e-9);
  EXPECT_NEAR(result(1, 0), expected(1, 0), 1e-9);
  EXPECT_NEAR(result(1, 1), expected(1, 1), 1e-9);
}

TEST(S21MatrixTest, InverseMatrix_NonSquare) {
  S21Matrix matrix(2, 3);  // Не квадратная матрица
  EXPECT_THROW(matrix.InverseMatrix(), std::invalid_argument);
}

TEST(S21MatrixTest, InverseMatrix_Singular) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 2;
  matrix(1, 1) = 4;  // Определитель равен нулю

  EXPECT_THROW(matrix.InverseMatrix(), std::invalid_argument);
}

// Тест на инверсию единичной матрицы
TEST(S21MatrixTest, InverseMatrix_Identity) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 0;
  matrix(1, 0) = 0;
  matrix(1, 1) = 1;

  S21Matrix result = matrix.InverseMatrix();

  EXPECT_EQ(result.getRows(), matrix.getRows());
  EXPECT_EQ(result.getCols(), matrix.getCols());

  for (int i = 0; i < result.getRows(); ++i) {
    for (int j = 0; j < result.getCols(); ++j) {
      EXPECT_EQ(result(i, j), matrix(i, j));
    }
  }
}

TEST(Operator_eq, normal_test) {
  S21Matrix a(2, 2);
  S21Matrix b(1, 1);

  b = a;
}

TEST(Operator_skobki, normal_values) {
  S21Matrix a(2, 2);
  a[0][0] = 1;
  a[0][1] = 2;
  a[1][0] = 3;
  a[1][1] = 4;

  bool flag = true;

  for (int i = 0; (i < 2) && flag; ++i) {
    for (int j = 0; (j < 2) && flag; ++j) flag = a[i][j] == a(i, j);
  }

  EXPECT_TRUE(flag);
}

TEST(Operator_skobki, invalid_values) {
  S21Matrix a(1, 1);

  bool flag = false;
  try {
    a(2, 2) = 2;
  } catch (const std::exception& e) {
    flag = true;
  }

  EXPECT_TRUE(flag);
}

TEST(Operators, plus_equal) {
  S21Matrix a(1, 1);
  a(0, 0) = 2;

  S21Matrix b(1, 1);
  b(0, 0) = 5;

  a += b;
  EXPECT_EQ(a(0, 0), 7);
  a -= b;
  EXPECT_EQ(a(0, 0), 2);
  a *= 5;
  EXPECT_EQ(a(0, 0), 10);
}

TEST(getRows, normal_values) {
  S21Matrix matrix(2, 2);

  EXPECT_EQ(matrix.getRows(), 2);
}

TEST(setRows, invalid_values) {
  S21Matrix matrix(2, 2);

  EXPECT_THROW(matrix.setRows(0), std::invalid_argument);
}

TEST(setCols, invalid_values) {
  S21Matrix matrix(2, 2);

  EXPECT_THROW(matrix.setCols(0), std::invalid_argument);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}