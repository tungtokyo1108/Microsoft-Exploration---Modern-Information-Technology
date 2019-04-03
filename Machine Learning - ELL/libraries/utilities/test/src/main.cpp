/**
 * Microsoft - Modern Information Technology
 * https://github.com/Microsoft/ELL/blob/master/libraries/utilities/test/src/main.cpp
 *
 *  Created on: Dec 27, 2018
 *  Student (MIG Virtual Developer): Tung Dang
 */

#include "utilities/test/include/Files_test.h"
#include "utilities/test/include/Iterator_test.h"
#include "utilities/test/include/Hash_test.h"

#include <testing/include/testing.h>

#include <utilities/include/Exception.h>
#include <utilities/include/Files.h>
#include <utilities/include/Unused.h>

#include <iostream>
#include <numeric>
#include <string>
#include <thread>
#include <vector>

using namespace ell;

int main(int argc, char const *argv[])
{
    try 
    {
        std::string basePath = ell::utilities::GetDirectoryPath(argv[0]);

        TestIteratorAdapter();
        TestTransformIterator();
        TestParallelTransformIterator();
        TestStlStridedIterator();

        TestStringf();
        TestJoinPaths(basePath);
        #ifdef WIN32
        TestUnicodePaths(basePath);
        #endif

        // PrintBinaryTreeMap_Test<void>();
    }
    catch (const utilities::Exception& exception)
    {
        std::cerr << "Error, got ELL exception. Message:" << exception.GetMessage() << std::endl;
        throw;
    }
    if (testing::DidTestFail())
    {
        return 1;
    }
    return 0;
}
