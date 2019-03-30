/**
 * Microsoft - Modern Information Technology
 * https://github.com/Microsoft/ELL/blob/master/libraries/utilities/include/Hash.h
 *
 *  Created on: Mar 28, 2019
 *  Student (MIG Virtual Developer): Tung Dang
 */

#pragma once 

#include "Unused.h"

#include <tuple>
#include <utility>
#include <vector>

namespace ell 
{
    namespace utilities
    {
        namespace detail
        {
            inline void HashCombineImpl(size_t& seed, size_t value)
            {
                seed ^= value + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
        }

        template <typename T>
        inline void HashCombine(size_t& seed, const T& t);

        template <class Iterator>
        inline void HashRange(size_t& seed, Iterator first, Iterator last);

        template <class Iterator>
        [[nodiscard]] inline size_t HashRange(Iterator first, Iterator last);

        template <typename T>
        [[nodiscard]] auto HashValue(const T& t) -> decltype(std::hash<T>{}(t))
        {
            return std::hash<T>{}(t);
        }

        template <typename T, size_t N>
        [[nodiscard]] auto HashValue(const T (&a)[N])
        {
            return HashRange(a, a + N);
        }

        template <typename T, size_t N>
        [[nodiscard]] auto HashValue(T (&a)[N])
        {
            return HashRange(a, a + N);
        }

        template <typename T, typename Alloc>
        [[nodiscard]] auto HashValue(const std::vector<T, Alloc>& v)
        {
            size_t seed = 0;
            HashCombine(seed, v.size());
            HashRange(seed, v.begin(), v.end());
            return seed;
        }

        namespace detail
        {
            template <size_t Idx, typename Tuple>
            void HashTupleImpl(size_t& seed, const Tuple& tuple)
            {
                    HashCombine(seed, std::get<Idx>(tuple));
                    HashTupleImpl<Idx + 1>(seed, tuple);
            }

            template <typename Tuple>
            [[nodiscard]] size_t HashTuple(const Tuple& tuple)
            {
                size_t seed = 0;
                HashTupleImpl<0>(seed, tuple);
                return seed;
            }
        } 
        
        template <typename... Ts>
        [[nodiscard]] auto HashValue(const std::tuple<Ts...>& tuple)
        {
            return detail::HashTuple(tuple);
        }
    }
}

#pragma region implementation

namespace ell 
{
    namespace utilities 
    {
        template <typename T>
        inline void HashCombine(size_t& seed, const T& t)
        {
            detail::HashCombineImpl(seed, HashValue(t));
        }

        template <class Iterator>
        inline void HashRange(size_t& seed, Iterator first, Iterator last)
        {
            for (; first != last; ++first)
            {
                HashCombine<typename std::iterator_traits<Iterator>::value_type>(seed, *first);
            }
        }

        template <class Iterator>
        [[nodiscard]] inline size_t HashRange(Iterator first, Iterator last)
        {
            size_t seed = 0;
            HashRange(seed, first, last);
            return seed;
        }
    }
}

#pragma endregion implementation
