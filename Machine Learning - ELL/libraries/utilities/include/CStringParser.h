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
            if (IsWhiteSpace(*pStr))
            {
                return ParseResult::badFormat;
            }

            auto tmp = errno;
            errno = 0;

            value = strtof(pStr, &pEnd);

            if (pStr == pEnd)
            {
                return ParseResult::badFormat;
            }
            if (errno == ERANGE)
            {
                return ParseResult::outOfRange;
            }

            errno = tmp;
            return ParseResult::success;
        }

        inline ParseResult cParse(const char* pStr, char*& pEnd, double& value)
        {
            if (IsWhiteSpace(*pStr))
            {
                return ParseResult::badFormat;
            }

            auto tmp = errno;
            errno = 0;

            value = std::strtod(pStr, &pEnd);

            if (pStr == pEnd)
            {
                return ParseResult::badFormat;
            }
            if (errno == ERANGE)
            {
                return ParseResult::outOfRange;
            }

            errno = tmp;
            return ParseResult::success;
        }

        inline ParseResult cParse(const char* pStr, char*& pEnd, unsigned int& value)
        {
            if (!IsDigit(*pStr))
            {
                return ParseResult::badFormat;
            }

            auto tmp = errno;
            errno = 0;

            auto x = strtoul(pStr, &pEnd, 0);
            if (x != static_cast<unsigned int>(x))
            {
                return ParseResult::outOfRange;
            }

            value = static_cast<unsigned int>(x);

            if (pStr == pEnd)
            {
                return ParseResult ::badFormat;
            }
            if (errno == ERANGE)
            {
                return ParseResult::badFormat;
            }

            errno = tmp;
            return ParseResult::success;
        }

        inline ParseResult cParse(const char* pStr, char*& pEnd, uint64_t& value)
        {
            if (!IsDigit(*pStr))
            {
                return ParseResult::badFormat;
            }

            auto tmp = errno;
            errno = 0;

            auto x = strtoul(pStr, &pEnd, 0);
            if (pStr == pEnd)
            {
                return ParseResult::badFormat;
            }
            if (errno == ERANGE)
            {
                return ParseResult::outOfRange;
            }
            if (x != static_cast<uint64_t>(x))
            {
                return ParseResult::outOfRange;
            }

            value = static_cast<uint64_t>(x);
            errno = tmp;
            return ParseResult::success;
        }

        inline ParseResult cParse(const char* pStr, char*& pEnd, int& value)
        {
            if (IsWhiteSpace(*pStr))
            {
                return ParseResult::badFormat;
            }

            auto tmp = errno;
            errno = 0;

            auto x = strtol(pStr, &pEnd, 0);
            if (pStr == pEnd)
            {
                return ParseResult::badFormat;
            }
            if (errno == ERANGE)
            {
                return ParseResult::outOfRange;
            }
            value = static_cast<int>(x);
            errno = tmp;
            return ParseResult::success;
        }

        inline ParseResult cParse(const char* pStr, char*& pEnd, long& value)
        {
            if (IsWhiteSpace(*pStr))
            {
                return ParseResult::badFormat;
            }

            auto tmp = errno;
            errno = 0;
            value = strtol(pStr, &pEnd, 0);

            if (pStr == pEnd)
            {
                return ParseResult::badFormat;
            }
            if (errno == ERANGE)
            {
                return ParseResult::outOfRange;
            }

            errno = tmp;
            return ParseResult::success;
        }

        inline ParseResult cParse(const char* pStr, char*& pEnd, unsigned short& value)
        {
            if (!IsDigit(*pStr))
            {
                return ParseResult::badFormat;
            }

            auto tmp = errno;
            errno = 0;

            auto x = strtoul(pStr, &pEnd, 0);

            if (pStr == pEnd)
            {
                return ParseResult::badFormat;
            }
            if (errno == ERANGE)
            {
                return ParseResult::outOfRange;
            }
            if (x != static_cast<unsigned short>(x))
            {
                return ParseResult::outOfRange;
            }
            value = static_cast<unsigned short>(x);

            errno = tmp;
            return ParseResult::success;
        }

        inline ParseResult cParse(const char* pStr, char*& pEnd, short& value)
        {
            if (IsWhiteSpace(*pStr))
            {
                return ParseResult::badFormat;
            }

            auto tmp = errno;
            errno = 0;

            long x = strtol(pStr, &pEnd, 0);

            if (pStr == pEnd)
            {
                return ParseResult::badFormat;
            }
            if (errno == ERANGE)
            {
                return ParseResult::outOfRange;
            }
            if (x != static_cast<short>(x))
            {
                return ParseResult::outOfRange;
            }

            value = static_cast<short>(x);

            errno = tmp;

            return ParseResult::success;
        }

        inline ParseResult cParse(const char* pStr, char*& pEnd, char& value)
        {
            value = *pStr;
            pEnd = const_cast<char*>(++pStr);
            return ParseResult::success;
        }

        inline ParseResult cParse(const char* pStr, char*& pEnd, std::string& value)
        {
            const char* iter = pStr;
            while (std::isalnum(*iter) || *iter == '_')
            {
                ++iter;
            }
            value = std::string(pStr,iter);
            pEnd = const_cast<char*>(iter);
            return ParseResult::success;
        }

        template<typename std::enable_if_t<!std::is_same<unsigned long, unsigned int>::value, int> = 0>
        inline ParseResult cParse(const char* pStr, char*& pEnd, unsigned long& value)
        {
            if (!IsDigit(*pStr))
            {
                return ParseResult::badFormat;
            }

            auto tmp = errno;
            errno = 0;

            value = strtoul(pStr, &pEnd, 0);

            if (pStr == pEnd)
            {
                return ParseResult::badFormat;
            }
            if (errno == ERANGE)
            {
                return ParseResult::outOfRange;
            }

            errno = tmp;
            return ParseResult::success;
        }

        template <typename ValueType>
        ParseResult Parse(const char*& pStr, ValueType& value)
        {
            if (IsEndOfString(*pStr))
            {
                return ParseResult::endOfString;
            }

            if(*pStr == '/')
            {
                if (*(pStr + 1) == '/')
                {
                    return ParseResult::beginComment;
                }
            }

            if (*pStr == '#')
            {
                return ParseResult::beginComment;
            }

            char* pEnd = nullptr;
            auto parseResult = cParse(pStr, pEnd, value);
            pStr = pEnd;

            return parseResult;
        }
    }
}

#pragma endregion implementation
