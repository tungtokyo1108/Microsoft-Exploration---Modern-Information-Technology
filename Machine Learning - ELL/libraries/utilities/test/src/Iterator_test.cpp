/**
 * Microsoft - Modern Information Technology
 * https://github.com/Microsoft/ELL/blob/master/libraries/utilities/test/src/Iterator_test.cpp
 *
 *  Created on: Jan 16, 2019
 *  Student (MIG Virtual Developer): Tung Dang
 */

#include "utilities/test/include/Iterator_test.h"

#include <utilities/include/ParallelTransformIterator.h>
#include <utilities/include/StlContainerIterator.h>
#include <utilities/include/StlStridedIterator.h>
#include <utilities/include/TransformIterator.h>

#include <testing/include/testing.h>

#include <chrono>
#include <iostream>
#include <numeric>
#include <thread>

namespace ell 
{
    void TestIteratorAdapter()
    {
        std::vector<int> vec{1,2,3,4,5,6};
        auto it = utilities::MakeStlContainerReferenceIterator(vec.begin(), vec.end());
        bool passed = true;
        size_t index = 0;
        while (it.IsValid())
        {
            passed = passed && (it.Get() == vec[index]);
            it.Next();
            index++;
        }

        testing::ProcessTest("utilities::StlContainerReferenceIterator.Get", passed);
        testing::ProcessTest("utilities::StlContainerReferenceIteratorlength", index == vec.size());
    }
}



