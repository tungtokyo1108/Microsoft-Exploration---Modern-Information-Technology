/**
 * Microsoft - Modern Information Technology
 * https://github.com/Microsoft/ELL/blob/master/libraries/utilities/include/StringUtil.h
 *
 *  Created on: Dec 26, 2018
 *  Student (MIG Virtual Developer): Tung Dang
 */

#include <string>
#include <vector>

namespace ell 
{
    namespace utilities 
    {
        /**
         * Returns copy of std::string with 
         * - all lowercase characters 
         * - all uppercase characters 
        */
        std::string ToLowercase(const std::string& s);
        std::string ToUppercase(const std::string& s); 

        /**
         * A printf-style format string function 
        */
        template <typename Arg1, typename... Args>
        std::string FormatString(const char* format, Arg1&& arg1, Args&&... args) 
        {
            size_t size = std::snprintf(nullptr, 0, format, std::forward<Arg1>(arg1), std::forward<Args>(args)...) + 1;
            std::vector<char> buf(size);
            std::snprintf(buf.data(), buf.size(), format, std::forward<Arg1>(arg1), std::forward<Args>(args)...);
            return std::string(buf.data());
        }

        /* Replace all instances of the 'from' substring in 'str' with the value of the 'to' string */
        void ReplaceAll(std::string& str, const std::string& from, const std::string& to);

        /* Split a given string at each instance of the given separator character */
        std::vector<std::string> Split(const std::string& s, char separator);

        /* Join a vector of strings with a given separator charactor */
        std::string Join(const std::vector<std::string>& strings, const std::string& seperator); 
    }
}