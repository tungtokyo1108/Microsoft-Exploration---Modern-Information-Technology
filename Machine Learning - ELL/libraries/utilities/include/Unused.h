/**
 * Microsoft - Modern Information Technology
 * https://github.com/Microsoft/ELL/blob/master/libraries/utilities/include/Unused.h
 *
 *  Created on: Jan 11, 2019
 *  Student (MIG Virtual Developer): Tung Dang
 */

#pragma once

#include <utility>

namespace ell
{
namespace utilities
{
    /// <summary> Suppresses the unused parameter warning on a function parameter </summary>
    ///
    /// <typeparam name="T"> The type of the unused parameter. </param>
    /// <param name="t1"> The name of the parameter to mark as unused. </param>
    template <class T>
    inline constexpr void unused(T&& t1)
    {
        static_cast<void>(t1);
    }

    /// <summary> Suppresses the unused parameter warning on one or more function parameters </summary>
    ///
    /// <typeparam name="T1"> The type of the first unused parameter. </param>
    /// <typeparam name="Args"> List of parameter types to match against. </typeparam>
    /// <param name="t1"> The name of the first parameter to mark as unused. </param>
    /// <param name="args"> List of parameter names. </typeparam>
    template <typename T1, typename... Args>
    inline constexpr void unused(T1&& t1, Args&&... args)
    {
        static_cast<void>(t1);
        unused(std::forward<Args>(args)...);
    }

} // namespace utilities
} // namespace ell

#define UNUSED(...) ::ell::utilities::unused(__VA_ARGS__)

#if defined(NDEBUG)
#define DEBUG_USED(...) UNUSED(__VA_ARGS__)
#else
#define DEBUG_USED(...)
#endif // defined(NDEBUG)