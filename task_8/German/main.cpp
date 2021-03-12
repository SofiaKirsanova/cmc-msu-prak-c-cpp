#include "matrix.h"

int main(int argc, char const *argv[])
{
	const unsigned int DIM1 = 3;
	const unsigned int DIM2 = 5;
	int x, y, z, size_diag, i, j;
	double g, scalar;
	char STR[] = "{{4.1, 5, 3, 0.999}, {2, 377, 1, 2} , {2, 2, 22, 0}}";
	double B[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
	while(1)
	{
		cout << "Enter number of rows: ";
		cin >> x;
		if(x > 1000000)
		{	
			perror("ERROR\n");
			exit(EXIT_FAILURE);
		}
		cout << "Enter number of colomns: ";
		cin >> y;
		if(y > 1000000)
		{	
			perror("ERROR\n");
			exit(EXIT_FAILURE);
		}
		double mas_x[x], mas_y[y];
		cout << "Enter double number: ";
		cin >> g;
		for(int i = 0; i < y; i++)
		{
			mas_x[i] = i;
		}
		for(int i = 0; i < x; i++)
		{
			mas_y[i] = i;
		}
		cout << "Input the size of the square matrix consisting of the ones: ";
		cin >> z;
		cout << "Input the size of the square diagonal matrix: ";
		cin >> size_diag;
		double vals[size_diag];
		cout << "Enter numbers to put on diag: ";
		for (int i = 0; i < size_diag; i++)
		{
			cin >> vals[i];
		}
		cout << "Enter a scalar: ";
		cin >> scalar;
		Matrix m1(x,y), m2(g), m3(mas_x, y), m4(x, mas_y), A(B, 10), C(STR);
		cout << "Matrix of zero: \n" << m1 << endl;
		cout << "Matrix 1x1: " << m2 << endl;
		cout << "Matrix-row 1xm: " << m3 << endl;
		cout << "Matrix-colomn nx1: \n" << m4 << endl;
		cout << "Transformed matrix: \n" << C << endl;
		Matrix::identity(z);
		Matrix::diagonal(vals, size_diag);
		cout << m1.rows_matr() << endl;
		cout << m1.cols_matr() << endl;
		A * scalar;
		cout << "Matrix multiply: \n" << A << endl;
		cout << "Matrix: \n" ;
		C[3].print();
		cout << endl;
	}
	return 0;
}
