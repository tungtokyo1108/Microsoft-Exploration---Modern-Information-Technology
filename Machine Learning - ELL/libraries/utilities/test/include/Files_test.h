/**
 * Microsoft - Modern Information Technology
 * https://github.com/Microsoft/ELL/blob/master/libraries/utilities/test/include/Files_test.h
 *
 *  Created on: Dec 27, 2018
 *  Student (MIG Virtual Developer): Tung Dang
 */

#include <string>

namespace ell 
{
    void TestStringf();
    void TestJoinPaths(const std::string& basePath);
    #ifdef WIN32
    void TestUnicodePaths(const std::string& basePath);
    #endif
}
