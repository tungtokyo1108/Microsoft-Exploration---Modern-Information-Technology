/**
 * Microsoft - Modern Information Technology
 * https://github.com/Microsoft/ELL/blob/master/libraries/utilities/include/CStringParser.h
 *
 *  Created on: Dec 30, 2018
 *  Student (MIG Virtual Developer): Tung Dang
 */

#include <cctype>
#include <cerrno>
#include <cstdlib>
#include <string>

namespace ell 
{
    namespace utilities
    {
        /**
         * The results of the parse command:
         * success = Parsing succeeded 
         * badFormat = The string was not formatted correctly
         * endOfString = The poiter pStr points \0 or to whitespace followed by \0
         * outOfRange = The number was in correct format but its value exceeds the range of the specificed type 
         * beginComment = The pStr string starts with "//" or "#" perhap, with preceding before
        */
        enum class ParseResult 
        {
            success,
            badFormat,
            endOfString,
            outOfRange,
            beginComment 
        };

        /**
         * Parses numbers in a c-string and advances the string pointer 
        */
        template <typename ValueType>
        ParseResult Parse(const char*& pStr, ValueType& value);

        /**
         * Advances pStr until it points to a non-whilespace character
        */
        void TrimLeadingWhitespace(const char*& pStr);

        bool IsEndOfString(char c);
        bool IsWhiteSpace(char c);
        bool IsDigit(char c);
    }
}

#pragma region implementation 

namespace ell 
{
    namespace utilities
    {
        inline ParseResult cParse(const char* pStr, char*& pEnd, float& value)
        {
            
        }
    }
}

#pragma endregion implementation