//объявление функций
#ifndef matrix_h
#define matrix_h
#include <iostream>
#include <cstring>
#include <cstdlib>


using namespace std;

class Matrix{
	double **elem;
	int rows , cols; // count colom and rows
public:
	Matrix(int n, int m);
	Matrix(double a);
	Matrix(double *row, int m);
	Matrix(int n, double *col);
	Matrix(char *str);
	static Matrix identity(int n);
	static Matrix diagonal(double *vals, int n);
	int rows_matr();
	int cols_matr();
	void set(int i, int j, double val);
	void print();
	//Matrix(Matrix& a);
	friend Matrix operator *(Matrix &M, double scalar);
	Matrix operator [](int i) const;
	friend ostream& operator << (ostream& stream, Matrix& M);
	//~Matrix();
};

#endif