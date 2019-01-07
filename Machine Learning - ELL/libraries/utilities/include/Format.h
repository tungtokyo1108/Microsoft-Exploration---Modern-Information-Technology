/**
 * Microsoft - Modern Information Technology
 * https://github.com/Microsoft/ELL/blob/master/libraries/utilities/include/Format.h
 *
 *  Created on: Jan 06, 2019
 *  Student (MIG Virtual Developer): Tung Dang
 */

#include "CStringParser.h"
#include "Exception.h"

#include <cctype>
#include <iomanip>
#include <ostream>
#include <sstream>
#include <string>
#include <type_traits>

namespace ell 
{
    namespace utilities
    {
        const char substitutionSymbol = '%';
        const char whitespaceSymbol = '^';

        /*Print formatted text to an ostream*/
        template <typename ArgType, typename... ArgTypes>
        void PrintFormat(std::ostream& os, const char* format, const ArgType& arg, const ArgTypes&... args);
        void PrintFormat(std::ostream& os, const char* format);
        template <typename... ArgTypes>
        std::string PrintFormat(const char* format, const ArgTypes&... args);

        class Match 
        {
            public: 
            inline explicit Match(const char* pStr);
            inline explicit Match(const std::string& str);
            inline operator const char*();

            private: 
            const char* _pStr;
        };

        enum class MatchResult 
        {
            success,
            earlyEndOfContent,
            mismatch,
            parseError,
            missingArgument,
            unexpectedPercentSymbol
        };

        /*Matches content to a format, allowing arbitrary whitespace until a % character is encountered*/
        MatchResult MatchToSubstitutionSymbol(const char*& content, const char*& format);
        
        /*Match content to a format, while parsing values in the position where the format contains the character %*/
        template <typename... ArgTypes>
        MatchResult MatchFormat(const char*& content, const char* format, Match match, ArgTypes&... args);

        template <typename ArgType, typename... ArgTypes>
        MatchResult MatchFormat(const char*& content, const char* format, ArgType& arg, ArgTypes&... args);

        MatchResult MatchFormat(const char*& content, const char* format);

        template <typename... ArgTypes>
        void MatchFormatThrowsExceptions(const char*& content, const char* format, ArgTypes&... args);
    }
}

#pragma region implementation 

namespace ell 
{
    namespace utilities
    {
        Match::Match(const char* pStr) : 
            _pStr(pStr)
        {}

        Match::Match(const std::string& str) : 
            _pStr(str.c_str())
        {}

        Match::operator const char *()
        {
            return _pStr;
        }

        template <typename ArgType, typename... ArgTypes>
        void PrintFormat(std::ostream& os, const char* format, const ArgType& arg, const ArgTypes&... args)
        {
            if (*format == '\0')
            {
                return;
            }

            while (*format != substitutionSymbol && *format != '\0')
            {
                if (*format != whitespaceSymbol)
                {
                    os << *format;
                }
                ++format;
            }

            if (*format == substitutionSymbol)
            {
                ++format;
                os << arg;
            }

            PrintFormat(os,format,args...);
        }

        template <typename... ArgTypes>
        std::string PrintFormat(const char* format, const ArgTypes&... args)
        {   
            std::stringstream ss;
            PrintFormat(ss, format, args...);
            return ss.str();
        }

        template <typename... ArgTypes>
        MatchResult MatchFormat(const char*& content, const char* format, Match match, ArgTypes&... args)
        {
            auto matchResult = MatchToSubstitutionSymbol(content, format);
            if (matchResult != MatchResult::success)
            {
                return matchResult;
            }
            if (*format == '\0')
            {
                return MatchResult::success;
            }

            ++format;
            const char* cStr = match;
            matchResult = MatchToSubstitutionSymbol(content, cStr);
            if (matchResult != MatchResult::success)
            {
                return matchResult;
            }
            if (*cStr != '\0')
            {
                return MatchResult::unexpectedPercentSymbol;
            }
            return MatchFormat(content, format, args...);
        }

        template <typename ArgType, typename... ArgTypes>
        MatchResult MatchFormat(const char*& content, const char* format, ArgType& arg, ArgTypes&... args)
        {
            auto matchResult = MatchToSubstitutionSymbol(content, format);

            if (matchResult != MatchResult::success)
            {
                return matchResult;
            }
            if (*format == '\0')
            {
                return MatchResult::success;
            }

            // *format = substitutionSymbol
            ++format;

            auto parserResult = Parse<std::remove_reference_t<ArgType>>(content, arg);
            if (parserResult != ParseResult::success)
            {   
                return MatchResult::parseError;
            }

            return MatchFormat(content, format, args...);
        }

        template <typename... ArgTypes>
        void MatchFormatThrowsExceptions(const char*& content, const char* format, ArgTypes&... args) 
        {
            auto result = MatchFormat(content, format, args...);
            if (result == MatchResult::success)
            {
                return;
            }

            std::string contentSnippet(content, 30);
            std::string formatSnippet(format, 30);
            auto snippets = "\"" + contentSnippet + "\" and \"" + formatSnippet + "\"";

            switch (result)
            {
                case MatchResult::earlyEndOfContent:
                    throw utilities::InputException(utilities::InputExceptionErrors::badStringFormat, "content ended before format near: \"" + formatSnippet + "\"" );
                case MatchResult::mismatch:
                    throw utilities::InputException(utilities::InputExceptionErrors::badStringFormat, "mismatch between content and format near: " + snippets);
                case MatchResult::parseError: 
                    throw utilities::InputException(utilities::InputExceptionErrors::badStringFormat, "parser error near: " + snippets);
                case MatchResult::missingArgument: 
                    throw utilities::InputException(utilities::InputExceptionErrors::badStringFormat, "missing argument near: " + snippets);
                case MatchResult::missingArgument: 
                    throw utilities::InputException(utilities::InputExceptionErrors::badStringFormat, "unexpected symbol '" + std::to_string(substitutionSymbol) + "' in string argument near: " + snippets);
                case MatchResult::success:;    
            }
        }
    }
}

#pragma endregion implementation