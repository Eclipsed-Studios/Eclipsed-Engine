#include "Matrix2x2.h"

#include <assert.h>

namespace Eclipse::Math
{
#pragma region operations

    template<class T>
    Matrix2x2<T>::Matrix2x2()
    {
        memset(data, 0, sizeof(Matrix2x2<T>));
        data[0] = 1;
        data[3] = 1;
    }
    template<class T>
    Matrix2x2<T>::Matrix2x2(Matrix2x2& aOther)
    {
        memcpy(data, aOther, sizeof(Matrix2x2<T>));
    }

#pragma endregion


#pragma region operations

    template<class T>
    Matrix2x2<T> operator*(const Matrix2x2<T>& aMat0, const Matrix2x2<T>& aMat1)
    {
        Matrix2x2<T> returnMatrix;

        {
            float num0 = aMat0(1, 1);
            float num1 = aMat1(1, 1);
            float mulAns0 = num0 * num1;

            float num2 = aMat0(1, 2);
            float num3 = aMat1(2, 1);
            float mulAns1 = num2 * num3;

            returnMatrix(1, 1) = mulAns0 + mulAns1;
        }
        {
            float num0 = aMat0(1, 1);
            float num1 = aMat1(1, 2);
            float mulAns0 = num0 * num1;

            float num2 = aMat0(1, 2);
            float num3 = aMat1(2, 2);
            float mulAns1 = num2 * num3;

            returnMatrix(1, 2) = mulAns0 + mulAns1;
        }
        {
            float num0 = aMat0(2, 1);
            float num1 = aMat1(1, 1);
            float mulAns0 = num0 * num1;

            float num2 = aMat0(2, 2);
            float num3 = aMat1(2, 1);
            float mulAns1 = num2 * num3;

            returnMatrix(2, 1) = mulAns0 + mulAns1;
        }
        {
            float num0 = aMat0(2, 1);
            float num1 = aMat1(1, 2);
            float mulAns0 = num0 * num1;

            float num2 = aMat0(2, 2);
            float num3 = aMat1(2, 2);
            float mulAns1 = num2 * num3;

            returnMatrix(2, 2) = mulAns0 + mulAns1;
        }

        return returnMatrix;
    }

#pragma endregion


#pragma region Other

    template<class T>
    T Matrix2x2<T>::operator()(int row, int column)
    {
        assert(column > 0 && row > 0 && column <= 2 && row <= 2 && "Index out of range");

        return arrData[row - 1][column - 1];
    }

#pragma endregion

}