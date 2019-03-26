/**
 * Microsoft - Modern Information Technology
 * https://github.com/Microsoft/ELL/blob/master/libraries/math/test/include/Vector_test.h
 *
 *  Created on: Mar 26, 2019
 *  Student (MIG Virtual Developer): Tung Dang
 */

#pragma once 

#include <testing/include/testing.h>
#include <math/include/Vector.h>

using namespace ell;

template <typename ElementType>
void TestVectorIndexer();

template <typename ElementType>
void TestVectorSize();

template <typename ElementType>
void TestVectorGetDataPointer();

template <typename ElementType>
void TestVectorGetIncrement();

template <typename ElementType>
void TestVectorNorm0();

template <typename ElementType>
void TestVectorNorm1();

template <typename ElementType>
void TestVectorNorm2();

template <typename ElementType>
void TestVectorNorm2Squared();

template <typename ElementType>
void TestVectorToArray();



#pragma region implementation
#include <math/include/VectorOperations.h>
#include <testing/include/testing.h>
#include <sstream>

template <typename ElementType>
void TestVectorIndexer()
{
    math::RowVector<ElementType> v{1,2,3,4,5,6,7};
    auto u = v.GetSubVector(2,2);

    math::RowMatrix<ElementType> M{{1,2,3}, {4,5,6}, {7,8,9}};
    math::ColumnMatrix<ElementType> N(M);
    auto w = M.GetRow(1);
    auto z = N.GetRow(1);

    testing::ProcessTest("Vector::Operator[]", v[0] == 1 && v[1] == 2 && v[6] == 7 && u[0] == 3 && u[1] == 4 
                            && w[0] == 4 && w[1] == 5 && w[2] == 6 && z[0] == 4 && z[1] == 5 && z[2] == 6);
}

#pragma endregion implementation
