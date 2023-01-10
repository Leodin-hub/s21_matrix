#include "s21_matrix_oop.h"

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  int error = is_valid_() || other.is_valid_();
  if (error) {
    throw std::out_of_range(ERROR_TEXT[error - 1]);
  }
  int result = !is_valid_equal_(other.rows_, other.columns_);
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < columns_ && result; ++j)
      result = matrix_[i][j] == other.matrix_[i][j];
  return result;
}

bool S21Matrix::operator==(const S21Matrix& other) const {
  return this->EqMatrix(other);
}

int S21Matrix::GetRows() const { return rows_; }

int S21Matrix::GetColumns() const { return columns_; }

void S21Matrix::SetRows(int rows) {
  int error = rows < 1 ? OUT_OF_RANGE : 0;
  if (error) {
    throw std::out_of_range(ERROR_TEXT[error - 1]);
  }
  S21Matrix temp(rows, columns_);
  temp.copy_matrix_(*this);
  *this = temp;
}

void S21Matrix::SetColumns(int columns) {
  int error = columns < 1 ? OUT_OF_RANGE : 0;
  if (error) {
    throw std::out_of_range(ERROR_TEXT[error - 1]);
  }
  S21Matrix temp(rows_, columns);
  temp.copy_matrix_(*this);
  *this = temp;
}

void S21Matrix::SetSize(int rows, int columns) {
  S21Matrix temp(rows, columns);
  temp.copy_matrix_(*this);
  *this = temp;
}

double& S21Matrix::operator()(int x, int y) {
  int error = is_valid_range_(x, y);
  if (error) {
    throw std::out_of_range(ERROR_TEXT[error - 1]);
  }
  return matrix_[x][y];
}

const double& S21Matrix::operator()(int x, int y) const {
  int error = is_valid_range_(x, y);
  if (error) {
    throw std::out_of_range(ERROR_TEXT[error - 1]);
  }
  return matrix_[x][y];
}

void S21Matrix::operator()(double* source) {
  int error = is_valid_();
  if (error) {
    throw std::out_of_range(ERROR_TEXT[error - 1]);
  }
  try {
    source[rows_ * columns_ - 1] = source[rows_ * columns_ - 1];
  } catch (std::exception const& err) {
    error = OUT_OF_RANGE;
  }
  if (error) {
    throw std::out_of_range(ERROR_TEXT[error - 1]);
  }
  int c = 0;
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < columns_; ++j) {
      matrix_[i][j] = source[c];
      ++c;
  }
}

double*& S21Matrix::operator[](int x) {
  int error = is_valid_range_(x, 0);
  if (error) {
    throw std::out_of_range(ERROR_TEXT[error - 1]);
  }
  return matrix_[x];
}

void S21Matrix::Zeros() {
  int error = is_valid_();
  if (error) {
    throw std::out_of_range(ERROR_TEXT[error - 1]);
  }
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < columns_; ++j)
      matrix_[i][j] = 0;
}

void S21Matrix::Ones() {
  int error = is_valid_();
  if (error) {
    throw std::out_of_range(ERROR_TEXT[error - 1]);
  }
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < columns_; ++j)
      matrix_[i][j] = 1;
}

void S21Matrix::Fill(double min, double step) {
  int error = is_valid_();
  if (error) {
    throw std::out_of_range(ERROR_TEXT[error - 1]);
  }
  min = !min ? 1 : min;
  step = !step ? 1 : step;
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < columns_; ++j) {
      matrix_[i][j] = min;
      min += step;
  }
}

void S21Matrix::Noise(int max) {
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < columns_; ++j)
      matrix_[i][j] = rand() % max;
}

void S21Matrix::PrintMatrix() const {
  for (int i = 0; i < rows_; printf("\n"), ++i)
    for (int j = 0; j < columns_; ++j) {
      printf("%lf", matrix_[i][j]);
      j < columns_ - 1 ? printf(" ") : 0;
  }
}