/**
 * Microsoft - Modern Information Technology
 * https://github.com/Microsoft/ELL/blob/master/libraries/utilities/src/TypeName.cpp
 *
 *  Created on: Jan 07, 2019
 *  Student (MIG Virtual Developer): Tung Dang
 */

#include "TypeName.h"

#include <string>
#include <vector>

namespace ell 
{
    namespace utilities
    {
        std::string GetCompositeTypeName(std::string baseType, const std::vector<std::string>& subtypes)
        {
            if (subtypes.size() == 0)
            {
                return baseType;
            }

            std::string result = baseType + "<";
            for (size_t index = 0; index < subtypes.size(); ++index)
            {
                if (index != 0)
                {
                    result += ",";
                }
                result += subtypes[index];
            }
            result += ">";
            return result;
        }
    }
}