#include "matrix.h"

/* 1) */
Matrix::Matrix(int n, int m)
{
	rows = n;
	cols = m;
	elem = new double *[rows];
	for(int i = 0; i < rows; i++)
	{
		elem[i] = new double [cols];
		for(int j = 0; j < cols; j++)
		{
			elem[i][j] = 0.0;
		}
	}
}

/* 2) */
Matrix::Matrix(double a)
{
	rows = 1;
	cols = 1;
	elem = new double *[rows];
	elem[0] = new double [cols];
	elem[0][0] = a;
		

}

/* 3) */
Matrix::Matrix(double *row, int m)
{
	rows = 1;
	cols = m;
	elem = new double *[rows];
	elem[0] = new double [cols];
	for(int j = 0; j < cols; j++)
	{
		elem[0][j] = row[j];
	}
}

/* 4) */
Matrix::Matrix(int n, double *col)
{
	rows = n;
	cols = 1;
	elem = new double *[rows];
	for(int j = 0; j < rows; j++)
	{
		elem[j] = new double [cols];
		elem[j][0] = col[j];
	}
}

/* 5) */

Matrix::Matrix(char* string_f)
{
    int stack = 0;
    int matx_n_f = 0;//quantity of rows
    int matx_m_f = 0;//quantity of columns
    int all_matr = 0;//quantity of numbers
    bool check = true;
    
    
    //SEQUENCE VALIDATION AND SEARCING FOR COLUMN AND ALL_NUMBER VALUE
    for(int i = 0; i < strlen(string_f); i++)
    {
        switch (string_f[i]){
            case '{': break;
                    
            case '}':
                check = false;
                stack--;
            break;
                    
            case ',': break;
                
            case ' ': break;

        default:
            if (string_f[i] >= '0' && string_f[i] <= '9')
            {
                if (check == true)
                {
                	matx_m_f++;
                }
                all_matr++;
                while ((string_f[i] >= '0' && string_f[i] <= '9') || string_f[i] == '.')
                {
                    i++;
                }
                i--;
            }
            else{
                cout << "WRONG_INPUT\n";
                i = strlen(string_f);
                matx_n_f = 0;
                matx_m_f = 0;
                stack = -1;
            }
        }
    }
    // Now we know matx_m_f and all_matr values
    
    if (stack < 0)//if there are "}" symbol => correct  sequence
    {
        stack = 0;
        
        //searching for quantity of STRINGS
        if ((all_matr % matx_m_f) == 0)
        {
            matx_n_f = all_matr/matx_m_f;
        }
        else
        {
            matx_n_f = all_matr/matx_m_f;
            matx_n_f ++;
        }
        
        //DEBUG
        //cout << "COLUMNS:" << matx_n_f << endl;
        
        //Buf to save all numbers
        double* M_BUF = new double [matx_n_f*matx_m_f];
        for(int i = 0; i < matx_n_f*matx_m_f; i++)
        {
            M_BUF[i] = 0;
        }
        // SPLITTING OF THE STRING IN ORDER TO EJECT NUMBERS TO SAVE THEM INTO THE BUF
        char sep[]= "/ ,}{";
        char *istr;
        istr = strtok (string_f ,sep);//ejection of a num
        //cout << "DEB_ISTR: "<<  istr << endl;
        double Num=0;
        Num = atof (istr);
        M_BUF[0] = Num;
        for(int i = 1; i < all_matr; i++)
        {

            istr = strtok (NULL ,sep);//ejection of a num
            double Num=0;
            Num = atof (istr);
            M_BUF[i] = Num;
            
        }
        
        //DEBUG
        /*
        for(int i = 0; i < matx_n_f*matx_m_f; i++)
        {
            cout <<  M_BUF[i] << " | ";
        }
         */
        
        //NOW WE CREATE MATRIX
        //WITH EXISTING VALUES AND SIZES
        Matrix M_F (matx_n_f,matx_m_f);
        rows = matx_n_f;
        cols = matx_m_f;
        
        elem = new double*[rows];
        for (int i = 0; i < rows; i++)
        {
            elem[i] = new double[cols];
            for(int j = 0; j < cols; j++)
            {
                elem[i][j] = M_BUF[i*cols + j];
            }
        }
        cout << endl;
        //cout << M_F;   
        
    }
    else
    {
        cout << "WRONG_INPUT\n";
        //i = strlen(string_f);
        matx_n_f = 0;
        matx_m_f = 0;
    }
}

/* 6) */

Matrix Matrix::identity(int n)
{
	
	Matrix ones(n,n);
	for(int i = 0; i < n; i++)
	{
		ones.set(i,i,1);
	}
	cout << "Matrix of ones: \n" << ones << endl;
	return ones;
}

/* 7) */

Matrix Matrix::diagonal(double *vals, int n)
{
	
	Matrix ones(n,n);
	for(int i = 0; i < n; i++)
	{
		ones.set(i, i, vals[i]);
	}
	cout << "Diagonal Matrix: \n" << ones << endl;
	return ones;
}

/* 8) */

int Matrix::rows_matr()
{
	printf("Number of rows: ");
	return rows;
}

/* 9) */

int Matrix::cols_matr()
{
	printf("Number of cols: ");
	return cols;
}

/* 10) */

void Matrix::set(int i, int j, double val)
{
	elem[i][j] = val;
}

/* 11) , 12) */

Matrix Matrix::operator [](int i) const
{
	if(i >= 1 && i <= rows)
	{
		Matrix res(1, cols);
		for(int j = 0; j < cols; j++)
		{
			res.elem[0][j] = elem[i - 1][j];
		}
		return res;
	}
	else if(i >= 1 && i <= cols)
	{
		Matrix res(rows, 1);
		for(int j = 0; j < rows; j++)
		{
			res.elem[j][0] = elem[j][i - 1];
		}
		return res;
	}
	else
	{
		throw("ERROR");

	}
} 

/* 13) */

Matrix operator *(Matrix &M, double scalar)
{
	Matrix buf(M.rows, M.cols);
	for(int i = 0; i < M.rows; i++)
	{
        for(int j=0; j < M.cols; j++)
        {
        	M.elem[i][j] *= scalar;
        }
    }
    return buf;
} 
/* 14) */
ostream& operator<< (ostream& stream, Matrix& matrix)
{
	for (int i = 0; i < matrix.rows; i++)
	{
		for (int j = 0; j < matrix.cols; j++)
		{
			stream << matrix.elem[i][j] << " ";	
		}
		stream << endl;
	}
	return stream;
}

void Matrix::print()
{
    //printf("00\n");
    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
        cout << elem[i][j] << ' ';
      cout << endl;
    }
}

/*Matrix::Matrix(Matrix& a)
{
    //printf("33\n");
    //printf("111111\n");
    cols = 3;
    rows = 4;

    //printf("0000\n");
    elem = new double*[rows];

    for (int i = 0; i < rows; i++)
        elem[i] = new double[cols];

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            elem[i][j] = a.elem[i][j];


}*/

/*Matrix::~Matrix()
{
	for(int i = 0; i < rows; i++)
	{
		delete [] elem[i];
	}
	delete [] elem;
}*/
