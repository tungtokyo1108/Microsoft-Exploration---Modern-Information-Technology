/**
 * Microsoft - Modern Information Technology
 * https://github.com/microsoft/ELL/blob/master/libraries/math/test/include/Matrix_test.h
 *
 *  Created on: June 01, 2019
 *  Student (MIG Virtual Developer): Tung Dang
 */

#pragma once 

#include <testing/include/testing.h>

#include <math/include/Matrix.h>
#include <math/include/MatrixOperations.h>
#include <math/include/Vector.h>
#include <sstream>

using namespace ell;

template <typename ElementType, math::MatrixLayout layout>
void TestMatrixNumRows();

#pragma region implementation 

template <typename ElementType, math::MatrixLayout layout>
void TestMatrixNumRows() 
{
    math::Matrix<ElementType, layout> M {
        {1,0,4,0},
        {0,0,0,0},
        {0,0,0,7}
    };

    auto N = M.GetSubMatrix(0,1,2,2);
    testing::ProcessTest("Matrix::Operator", M.NumRows() == 3 && N.NumRows() == 2);
}

#pragma endregion implementation