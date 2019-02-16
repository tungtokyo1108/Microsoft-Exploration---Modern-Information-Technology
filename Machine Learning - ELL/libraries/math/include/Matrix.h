/**
 * Microsoft - Modern Information Technology
 * https://github.com/tungtokyo1108/ELL/blob/master/libraries/math/include/Matrix.h
 *
 *  Created on: Feb 07, 2019
 *  Student (MIG Virtual Developer): Tung Dang
 */

#pragma once

#include "Vector.h"
#include <utilities/include/IArchivable.h>
#include <cstddef>
#include <limits>

namespace ell
{
    namespace math
    {
        template <typename ElementType>
        class CommonMatrixBase
        {
            public: 
                size_t NumRows() const {return _numRows;}
                size_t NumColumns() const {return _numColumns;}
                size_t Size() const {return NumRows() * NumColumns();}
                size_t GetIncrement() const {return _increment;}

            protected: 
                CommonMatrixBase(const ElementType* pData, size_t numRows, size_t numColumns, size_t increment);
                void Swap(CommonMatrixBase<ElementType>& other);
                size_t _numRows;
                size_t _numColumns;
                size_t _increment;
        };

        enum class MatrixLayout
        {
            columnMajor,
            rowMajor
        };

        enum class MatrixTranspose
        {
            noTranspose,
            transpose
        };
    }
} 
