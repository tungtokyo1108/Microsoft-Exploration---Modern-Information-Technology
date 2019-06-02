/**
 * Microsoft - Modern Information Technology
 * https://github.com/microsoft/ELL/blob/master/libraries/math/test/include/Tensor_test.h
 *
 *  Created on: June 02, 2019
 *  Student (MIG Virtual Developer): Tung Dang
 */

#pragma once 

#include <testing/include/testing.h>
#include <math/include/Tensor.h>

using namespace ell;

template <typename ElementType, math::Dimension dimension0, math::Dimension dimension1, math::Dimension dimension2>
void TestTensorIndexer();

#pragma region implementation 

#include <math/include/TensorOperations.h>
#include <testing/include/testing.h>
#include <cstdlib>

template <typename ElementType, math::Dimension dimension0, math::Dimension dimension1, math::Dimension dimension2>
void TestTensorIndexer()
{
    auto T = math::Tensor<ElementType, dimension0, dimension1, dimension2> {
        {{1,2,3,4}, {1,2,3,4}, {1,2,3,4}},
        {{1,2,3,4}, {1,2,3,4}, {1,2,3,4}}
    };

    auto S = T.GetSubTensor({0,1,2}, {2,2,2});

    T(1,2,3) = 7;
    T(0,1,2) = 8;

    auto R1 = math::Tensor<ElementType, dimension0, dimension1, dimension2> {
        {{1,2,3,4}, {1,2,8,4}, {1,2,3,4}},
        {{1,2,3,4}, {1,2,3,4}, {1,2,3,7}}
    };

    auto R2 = math::Tensor<ElementType, dimension0, dimension1, dimension2> {
        {{8,4}, {3,4}},
        {{3,4}, {3,7}}
    };

    testing::ProcessTest("Tensor::operator()", T == R1 && S == R2);
}

#pragma endregion implementation 