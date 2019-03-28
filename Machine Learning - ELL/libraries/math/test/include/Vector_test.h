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

template <typename ElementType>
void TestVectorSize()
{
    math::RowVector<ElementType> u{};
    math::RowVector<ElementType> v{1,2,3,4,5,6,7};
    auto w = v.GetSubVector(2,3);

    testing::ProcessTest("Vector::Size", v.Size() == 7 && u.Size() == 0 && w.Size() == 3);
}

template <typename ElementType>
void TestVectorGetDataPointer()
{
    math::RowVector<ElementType> v{1,2,3,4,5,6,7};
    auto u = v.GetSubVector(2,2);

    testing::ProcessTest("Vector::GetDataPointer", &(v[0]) == v.GetDataPointer() && 
                            v.GetDataPointer() + 2 == u.GetDataPointer());
}

template <typename ElementType>
void TestVectorGetIncrement()
{
    math::RowVector<ElementType> v{1,2,3,4,5,6,7};
    auto u = v.GetSubVector(2,2);

    math::RowMatrix<ElementType> M{{1,2,3}, {4,5,6}, {7,8,9}};
    math::ColumnMatrix<ElementType> N(M);
    auto w = M.GetRow(1);
    auto z = N.GetRow(1);

    testing::ProcessTest("Vector::GetIncrement", v.GetIncrement() == 1 && u.GetIncrement() == 1
                            && w.GetIncrement() == 1 && z.GetIncrement() == 3);
}

template <typename ElementType>
void TestVectorNorm0()
{
    math::RowVector<ElementType> x{0,1,0,-2,0};
    auto v = x.GetSubVector(2,2);

    testing::ProcessTest("Vector::Norm0", x.Norm0() == 2 && v.Norm0() == 1);
}

template <typename ElementType>
void TestVectorNorm1()
{
    math::RowVector<ElementType> x{ 0, 1, 0, -2, 0 };
    auto v = x.GetSubVector(2, 2);

    testing::ProcessTest("Vector::Norm1", x.Norm1() == 3 && v.Norm2() == 2);
}

template <typename ElementType>
void TestVectorNorm2()
{
    math::RowVector<ElementType> x{ 0, 1, 0, -2, 0 };
    auto v = x.GetSubVector(2, 2);

    testing::ProcessTest("Vector::Norm2", testing::IsEqual(x.Norm2(), static_cast<ElementType>(std::sqrt(5))) && v.Norm2() == 2);
}

template <typename ElementType>
void TestVectorNorm2Squared()
{
    math::RowVector<ElementType> x{ 0, 1, 0, -2, 0 };
    auto v = x.GetSubVector(2, 2);

    testing::ProcessTest("Vector::Norm2Squared", x.Norm2Squared() == 5 && v.Norm2Squared() == 4);
}

template <typename ElementType>
void TestVectorToArray()
{
    std::vector<ElementType> r0{41,47,53,59};
    std::vector<ElementType> r1{15,25,23,33};

    math::RowVector<ElementType> p(r0);
    math::ColumnVector<ElementType> q(r1);

    math::Matrix<ElementType, math::MatrixLayout::rowMajor> A {
        {41, 47, 53, 59},
        {40, 45, 56, 61},
        {15, 25, 23, 33},
    };
    std::vector<ElementType> r(A.GetRow(0).ToArray());
    std::vector<ElementType> s(A.GetRow(2).ToArray());

    math::Matrix<ElementType, math::MatrixLayout::columnMajor> B(A);
    std::vector<ElementType> t(B.GetRow(0).ToArray());
    std::vector<ElementType> u(B.GetRow(2).ToArray());

    testing::ProcessTest("Vector::ToArray", p.ToArray() == r0 && q.ToArray() == r1 
                            && r == r0 && s == r1 && t == r0 && u == r1);
}

#pragma endregion implementation
