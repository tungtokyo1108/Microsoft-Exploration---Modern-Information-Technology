/**
 * Microsoft - Modern Information Technology
 * https://github.com/microsoft/ELL/blob/master/libraries/functions/test/src/main.cpp
 *
 *  Created on: June 15, 2019
 *  Student (MIG Virtual Developer): Tung Dang
 */

#include <functions/include/LogLoss.h>

#include <testing/include/testing.h>

#include <math/include/Vector.h>
#include <math/include/VectorOperations.h>

#include <array>
#include <cmath>
#include <functional>
#include <iostream>
#include <random>
#include <string>

using namespace ell;
using Range = std::array<double, 3>;

void LogLossTest()
{
    functions::LogLoss logLoss;
    testing::ProcessTest("Testing function::LogLoss(2,1)", testing::IsEqual(logLoss(2,1), std::log(1 + std::exp(-2))));
    testing::ProcessTest("Testing function::LogLoss(-2,-1)", testing::IsEqual(logLoss(-2,-1), std::log(1 + std::exp(-2))));
    testing::ProcessTest("Testing functing::LogLoss(2,-1)", testing::IsEqual(logLoss(2,-1), std::log(1 + std::exp(2))));

    testing::ProcessTest("Testing function::LogLoss::GetDerivative(2,1)", testing::IsEqual(logLoss.GetDerivative(2,1), -1 / (1 + std::exp(2))));
    testing::ProcessTest("Testing function::LogLoss::GetDerivative(2,-1)", testing::IsEqual(logLoss.GetDerivative(2,-1), 1 / (1 + std::exp(-2))));
}

int main() 
{
    LogLossTest();

    if (testing::DidTestFail())
    {
        return 1;
    }

    return 0;
}
