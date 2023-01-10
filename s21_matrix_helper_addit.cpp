#include "s21_matrix_oop.h"

int S21Matrix::is_valid_() const {
  int error = !(rows_ > 0 && columns_ > 0 && matrix_);
  return error;
}

int S21Matrix::is_valid_equal_(int rows, int columns) const {
  int error = is_valid_();
  if (!error)
    if (rows != rows_ || columns != columns_) error = OUT_OF_RANGE;
  return error;
}

int S21Matrix::is_valid_range_(int rows, int columns) const {
  int error = is_valid_();
  if (!error)
    if (0 > rows || rows >= rows_ || 0 > columns || columns >= columns_)
      error = OUT_OF_RANGE;
  return error;
}

int S21Matrix::is_valid_squad_() const {
  int error = is_valid_();
  if (!error)
    if (rows_ != columns_) error = OUT_OF_RANGE;
  return error;
}

int S21Matrix::is_valid_mul_(const S21Matrix& other) const {
  int error = is_valid_() || other.is_valid_();
  if (!error)
    if (columns_ != other.rows_) error = OUT_OF_RANGE;
  return error;
}