/**
 * Microsoft - Modern Information Technology
 * https://github.com/microsoft/ELL/blob/master/libraries/functions/include/LogLoss.h
 *
 *  Created on: June 14, 2019
 *  Student (MIG Virtual Developer): Tung Dang
 */

#pragma once 

#include <cstddef>

namespace ell 
{
    namespace functions
    {
        class LogLoss
        {
            public:
                constexpr static double GetSmoothness() {return 0.25;}
                double operator() (double prediction, double label) const;
                double GetDerivative(double prediction, double label) const;
                double Conjugate(double dual, double label) const;
                double ConjugateProx(double sigma, double dual, double label) const;
            
            private:
                static constexpr double _conjugateBoundary = 1.0e-12;
                static constexpr double _conjugateProxDesiredPrecision = 1.0e-6;
                static constexpr size_t _conjugateProxMaxIterations = 20;
        };
    }
}
