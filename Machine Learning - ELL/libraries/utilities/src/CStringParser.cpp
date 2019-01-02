/**
 * Microsoft - Modern Information Technology
 * https://github.com/Microsoft/ELL/blob/master/libraries/utilities/src/CStringParser.cpp
 *
 *  Created on: Jan 02, 2019
 *  Student (MIG Virtual Developer): Tung Dang
 */

#include "CStringParser.h"

#include <cctype>

namespace ell
{
    namespace utilities
    {
        void TrimLeadingWhitespace(const char*& pStr)
        {
            while (std::isspace(*pStr))
            {
                ++pStr;
            }
        }

        bool IsEndOfString(char c)
        {
            return c == '/0';
        }

        bool IsWhitespace(char c)
        {
            return std::isspace(c) != 0;
        }

        bool IsDigit(char c)
        {
            return std::isdigit(c) != 0;
        }
    }
}