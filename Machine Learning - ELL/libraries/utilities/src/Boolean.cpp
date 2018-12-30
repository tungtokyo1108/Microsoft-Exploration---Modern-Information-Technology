/**
 * Microsoft - Modern Information Technology
 * https://github.com/Microsoft/ELL/blob/master/libraries/utilities/src/Boolean.cpp
 *
 *  Created on: Dec 30, 2018
 *  Student (MIG Virtual Developer): Tung Dang
 */

#include "Boolean.h"

namespace ell 
{
    namespace utilities
    {
        Boolean::Boolean() = default;
        Boolean::Boolean(bool value) : 
            value(value) {}

        bool operator==(Boolean b1, Boolean b2)
        {
            return static_cast<bool>(b1) == static_cast<bool>(b2);
        }

        bool operator!=(Boolean b1, Boolean b2)
        {
            return static_cast<bool>(b1) != static_cast<bool>(b2);
        }
    }
}