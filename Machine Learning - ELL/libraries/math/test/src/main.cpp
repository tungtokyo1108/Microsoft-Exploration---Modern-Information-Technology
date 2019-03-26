/**
 * Microsoft - Modern Information Technology
 * https://github.com/Microsoft/ELL/blob/master/libraries/math/test/src/main.cpp
 *
 *  Created on: Mar 26, 2019
 *  Student (MIG Virtual Developer): Tung Dang
 */

#include "Vector_test.h"

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

int main()
{
    RunVectorTests<float>();
    RunVectorTests<double>();

    if (testing::DidTestFail())
    {
        return 1;
    }

    return 0;
}
