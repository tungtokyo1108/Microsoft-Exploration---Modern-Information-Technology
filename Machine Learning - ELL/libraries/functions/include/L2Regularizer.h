/**
 * Microsoft - Modern Information Technology
 * https://github.com/microsoft/ELL/blob/master/libraries/functions/include/L2Regularizer.h
 *
 *  Created on: June 20, 2019
 *  Student (MIG Virtual Developer): Tung Dang
 */

#pragma once 
#include <math/include/Vector.h>

namespace ell 
{
    namespace functions
    {
        class L2Regularizer
        {
            public: 
                double operator()(math::ConstColumnVectorReference<double> w, double b = 0) const;
                double Conjugate(math::ConstColumnVectorReference<double> v, double d = 0) const;
                void ConjugateGradient(math::ConstColumnVectorReference<double> v, math::ColumnVectorReference<double> w) const;
                void ConjugateGradient(math::ConstColumnVectorReference<double> v, double d, math::ColumnVectorReference<double> w, 
                                        double& b) const;
        };
    }
}