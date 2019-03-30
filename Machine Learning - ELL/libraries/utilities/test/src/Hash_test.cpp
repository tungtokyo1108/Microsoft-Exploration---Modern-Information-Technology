/**
 * Microsoft - Modern Information Technology
 * https://github.com/Microsoft/ELL/blob/master/libraries/utilities/test/src/Hash_test.cpp
 *
 *  Created on: Mar 29, 2019
 *  Student (MIG Virtual Developer): Tung Dang
 */

#include "utilities/test/include/Hash_test.h"

#include <testing/include/testing.h>
#include <utilities/include/Hash.h>

#include <tuple>
#include <utility>

namespace ell 
{
    void Hash_test1()
    {
        bool ok = true;
        ok &= testing::IsEqual(std::hash<int>{}(3), utilities::HashValue(3));
        {
            size_t seed = 0;
            utilities::HashCombine(seed, 3);
            // ok &= testing::IsEqual(seed, utilities::HashValue(std::tuple{3}));
        }
        // ok &= testing::IsTrue(utilities::HashValue(std::vector{1,2,3}) != utilities::HashValue(std::vector{3,2,1}));
        testing::ProcessTest("Hash utility test", ok);
    }
}

