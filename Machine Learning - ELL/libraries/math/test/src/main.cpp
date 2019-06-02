/**
 * Microsoft - Modern Information Technology
 * https://github.com/Microsoft/ELL/blob/master/libraries/math/test/src/main.cpp
 *
 *  Created on: Mar 26, 2019
 *  Student (MIG Virtual Developer): Tung Dang
 */

#include "Vector_test.h"
#include "Matrix_test.h"
#include "Tensor_test.h"

using namespace ell;

template <typename ElementType>
void RunVectorTests()
{
    TestVectorIndexer<ElementType>();
    TestVectorSize<ElementType>();
    TestVectorGetDataPointer<ElementType>();
    TestVectorGetIncrement<ElementType>();
    TestVectorNorm0<ElementType>();
    TestVectorNorm1<ElementType>();
    TestVectorNorm2<ElementType>();
    TestVectorNorm2Squared<ElementType>();
    TestVectorToArray<ElementType>();
}

template <typename ElementType, math::MatrixLayout layout>
void RunLayoutMatrixTests()
{
    TestMatrixNumRows<ElementType, layout>();
}

template <typename ElementType>
void RunMatrixTests()
{
    RunLayoutMatrixTests<ElementType, math::MatrixLayout::columnMajor>();
    RunLayoutMatrixTests<ElementType, math::MatrixLayout::rowMajor>();
}


template <typename ElementType, math::Dimension dimension0, math::Dimension dimension1, math::Dimension dimension2>
void RunLayoutTensorTests()
{
    TestTensorIndexer<ElementType, dimension0, dimension1, dimension2>();
}

template <typename ElementType>
void RunTensorTests()
{
    RunLayoutTensorTests<ElementType, math::Dimension::column, math::Dimension::row, math::Dimension::channel>();
    RunLayoutTensorTests<ElementType, math::Dimension::channel, math::Dimension::column, math::Dimension::row>();
}

int main()
{
    RunVectorTests<float>();
    RunVectorTests<double>();

    RunMatrixTests<float>();
    RunMatrixTests<double>();

    RunTensorTests<float>();
    RunTensorTests<double>();


    if (testing::DidTestFail())
    {
        return 1;
    }

    return 0;
}
