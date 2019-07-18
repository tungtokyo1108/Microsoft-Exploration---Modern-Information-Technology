/**
 * Microsoft - Modern Information Technology
 * https://github.com/microsoft/ELL/blob/master/libraries/data/include/IndexValue.h
 *
 *  Created on: July 18, 2019
 *  Student (MIG Virtual Developer): Tung Dang
 */

#pragma once

#include <cstddef>
#include <type_traits>
#include <vector>

namespace ell
{
    namespace data 
    {
        struct IndexValue
        {
            size_t index;
            double value;
        };

        struct IIndexValueIterator
        {
            /* data */
        };

        // Helper type for concepts
        template <typename IteratorType>
        using IsIndexValueIterator = typename std::enable_if_t<std::is_base_of<IIndexValueIterator, IteratorType>::value, bool>;

        enum class IterationPolity
        {
            all,
            skipZeros
        };        
    }
}
