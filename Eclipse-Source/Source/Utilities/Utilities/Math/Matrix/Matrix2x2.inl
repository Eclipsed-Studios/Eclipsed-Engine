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

		for (int row = 1; row <= 2; row++)
		{
			for (int col = 1; col <= 2; col++)
			{
				float& valToAddMatrixNum = returnMatrix(row, col);
				for (int i = 1; i <= 2; i++)
				{
					float num0 = aMat0(row, i);
					float num1 = aMat1(i, col);
					valToAddMatrixNum += num0 * num1;
				}
			}
		}

		return returnMatrix;
	}

#pragma endregion


#pragma region Other

	template<class T>
	T& Matrix2x2<T>::operator()(int row, int column)
	{
		assert(column > 0 && row > 0 && column <= 2 && row <= 2 && "Index out of range");

		return arrData[row - 1][column - 1];
	}

#pragma endregion

}