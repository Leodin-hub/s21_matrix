#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(0), columns_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(const int rows_, const int columns_)
    : rows_(rows_), columns_(columns_) {
  if (rows_ < 1 || columns_ < 1) {
    throw std::out_of_range(ERROR_TEXT[1]);
  }
  malloc_matrix_();
  Zeros();
}

S21Matrix::S21Matrix(const int rows_) : S21Matrix(rows_, rows_) {}

S21Matrix::S21Matrix(const S21Matrix& other)
    : S21Matrix(other.rows_, other.columns_) {
  int error = other.is_valid_();
  if (error) {
    throw std::out_of_range(ERROR_TEXT[error - 1]);
  }
  copy_matrix_(other);
}

S21Matrix::S21Matrix(S21Matrix&& other)
    : rows_(other.rows_), columns_(other.columns_) {
  int error = other.is_valid_();
  if (error) {
    throw std::out_of_range(ERROR_TEXT[error - 1]);
  }
  matrix_ = other.matrix_;
  other.rows_ = other.columns_ = 0;
  other.matrix_ = nullptr;
}

void S21Matrix::operator=(const S21Matrix& other) {
  int error = other.is_valid_();
  if (error) {
    throw std::out_of_range(ERROR_TEXT[error - 1]);
  }
  clear_matrix_();
  rows_ = other.rows_;
  columns_ = other.columns_;
  malloc_matrix_();
  copy_matrix_(other);
}

void S21Matrix::operator=(S21Matrix&& other) {
  int error = other.is_valid_();
  if (error) {
    throw std::out_of_range(ERROR_TEXT[error - 1]);
  }
  clear_matrix_();
  rows_ = other.rows_;
  columns_ = other.columns_;
  matrix_ = other.matrix_;
  other.rows_ = other.columns_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
  clear_matrix_();
  rows_ = columns_ = 0;
}