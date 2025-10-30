#pragma once

#include <cstring>

namespace Eclipse::Math
{
    template <class T>
    class Matrix2x2
    {
    public:
        Matrix2x2();
        ~Matrix2x2() = default;

        Matrix2x2(Matrix2x2& aOther);

        T operator()(int column, int row);

        union
        {
            T arrData[2][2];
            T data[4];
        };

    };

    typedef Matrix2x2<float> Matrix2x2f;
    typedef Matrix2x2<double> Matrix2x2d;
    typedef Matrix2x2<unsigned> Matrix2x2ui;
    typedef Matrix2x2<int> Matrix2x2i;

    typedef Matrix2x2f Mat2x2f;
    typedef Matrix2x2d Mat2x2d;
    typedef Matrix2x2ui Mat2x2ui;
    typedef Matrix2x2i Mat2x2i;
}

#include "Matrix2x2.inl"