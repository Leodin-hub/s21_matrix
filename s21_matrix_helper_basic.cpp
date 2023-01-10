#include "s21_matrix_oop.h"

void S21Matrix::malloc_matrix_() {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) matrix_[i] = new double[columns_]();
}

void S21Matrix::clear_matrix_() {
  for (int i = 0; i < rows_; i++) delete[] matrix_[i];
  delete[] matrix_;
}

void S21Matrix::copy_matrix_(const S21Matrix& other) {
  int rows = rows_ < other.rows_ ? rows_ : other.rows_;
  int columns = columns_ < other.columns_ ? columns_ : other.columns_;
  for (int i = 0; i < rows; ++i)
    for (int j = 0; j < columns; ++j)
      matrix_[i][j] = other.matrix_[i][j];
}