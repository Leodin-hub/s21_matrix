#include "s21_matrix_oop.h"

int S21Matrix::trian_matrix_equal_() const {
  double res = 0;
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < columns_ && !res; ++j)
      if (i - j > 0) res = matrix_[i][j];
  return !!res;
}

double S21Matrix::main_iagonal_mul_() const {
  double result = 1;
  for (int i = 0; i < columns_; ++i) result *= matrix_[i][i];
  return result;
}

double S21Matrix::determinant_is_matrix_2x2_() const {
  return matrix_[0][0] * matrix_[1][1] - matrix_[1][0] * matrix_[0][1];
}

double S21Matrix::determinant_is_LU_() const {
  S21Matrix temp(*this);
  for (int col = 1; col < temp.rows_ && temp.trian_matrix_equal_(); col++) {
    for (int i = col; i < temp.rows_; ++i) {
      double f = temp.matrix_[i][col - 1] / temp.matrix_[col - 1][col - 1];
      for (int j = col - 1; j < temp.rows_; ++j) {
        temp.matrix_[i][j] -= temp.matrix_[col - 1][j] * f;
      }
    }
  }
  double result = temp.main_iagonal_mul_();
  return result;
}

S21Matrix S21Matrix::minor_(const int x, const int y) const {
  S21Matrix result(rows_ - 1, columns_ - 1);
  for (int i = 0, z = 0; i < rows_; ++i)
    for (int j = 0; j < rows_; ++j)
      if (i != x && j != y) {
        result.matrix_[z / (rows_ - 1)][z % (rows_ - 1)] = matrix_[i][j];
        z++;
      }
  return result;
}

S21Matrix S21Matrix::mul_matrix_(const S21Matrix& other) const {
  S21Matrix result(rows_, other.columns_);
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < other.columns_; ++j)
      for (int k = 0; k < columns_; k++)
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
  return result;
}

S21Matrix S21Matrix::mul_number_(const double num) const {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}