/**
 * Microsoft - Modern Information Technology
 * https://github.com/Microsoft/ELL/blob/master/libraries/math/include/MathConstants.h
 *
 *  Created on: Feb 10, 2019
 *  Student (MIG Virtual Developer): Tung Dang
 */

#pragma once 

namespace ell 
{
    namespace math  
    {
        template <typename ValueType>
        struct Constants 
        {
            constexpr static const ValueType pi = static_cast<ValueType>(3.14159265358979323846);
        };
    }   
}
