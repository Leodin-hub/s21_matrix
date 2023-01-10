#include "s21_matrix_oop.h"

void S21Matrix::SumMatrix(const S21Matrix& other) {
  int error = is_valid_equal_(other.rows_, other.columns_);
  if (error) {
    throw std::out_of_range(ERROR_TEXT[error - 1]);
  }
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < columns_; ++j)
      matrix_[i][j] += other.matrix_[i][j];
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

void S21Matrix::operator+=(const S21Matrix& other) { SumMatrix(other); }

void S21Matrix::SubMatrix(const S21Matrix& other) {
  int error = is_valid_equal_(other.rows_, other.columns_);
  if (error) {
    throw std::out_of_range(ERROR_TEXT[error - 1]);
  }
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < columns_; ++j)
      matrix_[i][j] -= other.matrix_[i][j];
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

void S21Matrix::operator-=(const S21Matrix& other) { SubMatrix(other); }

void S21Matrix::MulNumber(const double num) {
  int error = is_valid_();
  if (error) {
    throw std::out_of_range(ERROR_TEXT[error - 1]);
  }
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < columns_; ++j)
      matrix_[i][j] *= num;
}

S21Matrix operator*(const double num, S21Matrix& other) {
  return other.mul_number_(num);
}

S21Matrix operator*(S21Matrix& other, const double num) {
  return other.mul_number_(num);
}

void S21Matrix::operator*=(const double num) { MulNumber(num); }

void S21Matrix::MulMatrix(const S21Matrix& other) {
  int error = is_valid_mul_(other);
  if (error) {
    throw std::out_of_range(ERROR_TEXT[error - 1]);
  }
  S21Matrix temp(std::move(*this));
  *this = temp.mul_matrix_(other);
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  int error = is_valid_mul_(other);
  if (error) {
    throw std::out_of_range(ERROR_TEXT[error - 1]);
  }
  return mul_matrix_(other);
}

void S21Matrix::operator*=(const S21Matrix& other) { MulMatrix(other); }

S21Matrix S21Matrix::Transpose() const {
  int error = is_valid_();
  if (error) {
    throw std::out_of_range(ERROR_TEXT[error - 1]);
  }
  S21Matrix result(columns_, rows_);
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < columns_; ++j)
      result.matrix_[j][i] = matrix_[i][j];
  return result;
}

S21Matrix S21Matrix::CalcComplements() const {
  int error = is_valid_squad_();
  if (error) {
    throw std::out_of_range(ERROR_TEXT[error - 1]);
  }
  S21Matrix result(rows_, columns_);
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < columns_; ++j) {
      S21Matrix t_minor = minor_(i, j);
      double determ = t_minor.Determinant();
      result.matrix_[i][j] = determ * pow(-1.0, i + j);
  }
  return result;
}

double S21Matrix::Determinant() const {
  int error = is_valid_squad_();
  if (error) {
    throw std::out_of_range(ERROR_TEXT[error - 1]);
  }
  double result = 0;
  if (rows_ == 1) {
    result = matrix_[0][0];
  } else if (rows_ == 2) {
    result = determinant_is_matrix_2x2_();
  } else if (main_iagonal_mul_()) {
    result = determinant_is_LU_();
  } else {
    for (int col = 0; col < rows_; col++) {
      S21Matrix temp;
      temp = minor_(0, col);
      result += matrix_[0][col] * temp.Determinant() * pow(-1, col);
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() const {
  int error = is_valid_squad_();
  double determ = Determinant();
  if (!determ) {
    error = ERROR_CALC;
  }
  if (error) {
    throw std::out_of_range(ERROR_TEXT[error - 1]);
  }
  S21Matrix result = CalcComplements().Transpose();
  result *= 1.0 / determ;
  return result;
}