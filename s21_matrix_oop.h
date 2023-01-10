#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <math.h>

#include <iostream>

const std::string ERROR_TEXT[3] = {"Ошибка, матрица не существует",
                                   "Ошибка размерности или индексации матрицы",
                                   "Ошибка вычисления"};

enum ErrorUrl {
  OK,
  NOT_EXIT,
  OUT_OF_RANGE,
  ERROR_CALC,
};

class S21Matrix {
 public:
  S21Matrix();
  S21Matrix(const int rows_, const int columns_);
  S21Matrix(const int rows_);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);

  void operator=(const S21Matrix& other);
  void operator=(S21Matrix&& other);

  ~S21Matrix();

  bool EqMatrix(const S21Matrix& other) const;
  bool operator==(const S21Matrix& other) const;

  void SumMatrix(const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other) const;
  void operator+=(const S21Matrix& other);

  void SubMatrix(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other) const;
  void operator-=(const S21Matrix& other);

  void MulNumber(const double num);
  friend S21Matrix operator*(const double num, S21Matrix& other);
  friend S21Matrix operator*(S21Matrix& other, const double num);
  void operator*=(const double num);

  void MulMatrix(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other) const;
  void operator*=(const S21Matrix& other);

  S21Matrix Transpose() const;

  S21Matrix CalcComplements() const;

  double Determinant() const;

  S21Matrix InverseMatrix() const;

  int GetRows() const;

  int GetColumns() const;

  void SetRows(int rows);

  void SetColumns(int columns);

  void SetSize(int rows, int columns);

  double& operator()(int x, int y);

  const double& operator()(int x, int y) const;

  // Устанавливает значения матрицы из вектора
  void operator()(double* source);

  // Индексация
  double*& operator[](int x);

  // Заполнение матрицы нулями
  void Zeros();

  // Заполнение матрицы единицами
  void Ones();

  // Заполнение матрицы значениями от min с шагом step
  // Или заполнение от 1 с шагом 1
  void Fill(double min = 0, double step = 0);

  // Заполнение матрицы рандомными значениями
  void Noise(int max = 100);

  void PrintMatrix() const;

 private:
  int rows_, columns_;
  double** matrix_;

  void malloc_matrix_();

  void clear_matrix_();

  void copy_matrix_(const S21Matrix& other);

  // Проверка является ли матрица треугольной
  int trian_matrix_equal_() const;

  // Нахождение произведения главной диагонали
  double main_iagonal_mul_() const;

  // Вычисление детерминанта матрицы 2х2
  double determinant_is_matrix_2x2_() const;

  // Вычисление детерминанта через разложение к треугольной матрице
  double determinant_is_LU_() const;

  // Нахождение минора матрицы по указанным значениям
  S21Matrix minor_(const int x, const int y) const;

  // Функция вычисления произведения двух матриц
  S21Matrix mul_matrix_(const S21Matrix& other) const;

  // Функция вычисления произведения числа на матрицу
  S21Matrix mul_number_(const double num) const;

  // Проверка валидности матрицы, проверяет наличие матрицы, и нормальные
  // значения rows_ и columns_.
  int is_valid_() const;

  // Проверка валидности матрицы, проверяет соответсвие переданных значений к
  // rows_ и columns_
  int is_valid_equal_(int rows, int columns) const;

  // Проверяет входит ли переданные значения в диапазон значений
  // rows_ и columns_
  int is_valid_range_(int rows, int columns) const;

  // Проверяет является ли матрица квадратной
  int is_valid_squad_() const;

  // Проверка валидности матрицы, проверяет подходят ли матрицы для умножения
  int is_valid_mul_(const S21Matrix& other) const;
};

#endif  // SRC_S21_MATRIX_OOP_H_