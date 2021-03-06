#include "Matrix.h"

using namespace std;
namespace HCN
{
    template <class T>
    Matrix<T>::Matrix(int row, int col, int e = 0) : row(row), col(col)
    {
        a.resize(row, vector<T>(col, e));
    }
    template <class T>
    Matrix<T> Matrix<T>::operator*(const Matrix<T> &x)
    {
        Matrix<T> res(row, x.col);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < x.col; j++)
            {
                for (int k = 0; k < col; k++)
                {
                    res.a[i][j] = res.a[i][j] + a[i][k] * x.a[k][j];
                }
            }
        }
        return res;
    }
    template <class T>
    Matrix<T> Matrix<T>::operator+(const Matrix<T> &x)
    {
        Matrix<T> res(row, col);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                res.a[i][j] = a[i][j] + x.a[i][j];
            }
        }
        return res;
    }
    template <class T>
    Matrix<T> Matrix<T>::operator-(const Matrix<T> &x)
    {
        Matrix<T> res(row, col);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                res.a[i][j] = a[i][j] - x.a[i][j];
            }
        }
        return res;
    }
    template <class T>
    Matrix<T> Matrix<T>::operator!()
    {
        Matrix<T> res(row, col);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                res.a[i][j] = a[j][i];
            }
        }
        return res;
    }
    template <class T>
    ostream &operator<<(ostream &out, const Matrix<T> &res)
    {
        for (int i = 0; i < res.row; i++)
        {
            for (int j = 0; j < res.col; j++)
            {
                cout << res.a[i][j] << " ";
            }
            cout << endl;
        }
    }
    template <class T>
    Matrix<T>::~Matrix()
    {
    }
}