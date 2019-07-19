/**
 * Microsoft - Modern Information Technology
 * https://github.com/microsoft/ELL/blob/master/libraries/data/include/StlIndexValueIterator.h
 *
 *  Created on: July 18, 2019
 *  Student (MIG Virtual Developer): Tung Dang
 */

#pragma once 

#include "IndexValue.h"
#include <cstddef>
#include <type_traits>
#include <utility>
#include <vector>

namespace ell {
    namespace data {

        /* A read-only forward index-value iterator for STL container */
        template <IterationPolity policy, typename IteratorType>
        class StlIndexValueIterator;

        template <typename IteratorType>
        class StlIndexValueIterator<IterationPolity::skipZeros, IteratorType> : public IIndexValueIterator
        {
            public:
                StlIndexValueIterator(const IteratorType& begin, const IteratorType& end, size_t size);
                bool IsValid() const {return _current != _end && _index != _size;}
                void Next();
                IndexValue Get() const {return IndexValue{_index, (double)*_current};}
            protected: 
                IteratorType _current;
                IteratorType _end;
                size_t _size;
                size_t _index = 0;
                void SkipZeros();
        };

        /* A read-only forward index-value iterator for an STL container */
        template <typename IteratorType>
        class StlIndexValueIterator<IterationPolity::all, IteratorType> : public IIndexValueIterator
        {
            public: 
                StlIndexValueIterator(const IteratorType& begin, const IteratorType& end, size_t size);
                bool IsValid() const {return _index < _size;}
                void Next();
                IndexValue Get() const;

            protected: 
                IteratorType _current;
                IteratorType _end;
                size_t _size;
                size_t _index = 0;
        };

        template <IterationPolity policy, typename ElementType>
        using VectorIndexValueIterator = StlIndexValueIterator<policy, typename std::vector<ElementType>::const_iteator>;

        template <IterationPolity policy, typename ElementType>
        VectorIndexValueIterator<policy, ElementType> MakeVectorIndexValueIterator(const std::vector<ElementType>& container);

        template <IterationPolity policy, typename ElementType>
        VectorIndexValueIterator<policy, ElementType> MakeVectorIndexValueIterator(const std::vector<ElementType>& container, 
                                                                                    size_t size);
    }
}

#pragma region implementation 

namespace ell
{
    namespace data 
    {
        template <typename IteratorType>
        StlIndexValueIterator<IterationPolity::skipZeros, IteratorType>::StlIndexValueIterator(
            const IteratorType& begin, const IteratorType& end, size_t size) : 
            _current(begin),
            _end(end),
            _size(size),
            _index(0)
        {
            SkipZeros();
        } 

        template <typename IteratorType>
        void StlIndexValueIterator<IterationPolity::skipZeros, IteratorType>::Next()
        {
            ++_current;
            ++_index;
            SkipZeros();
        }

        template <typename IteratorType>
        void StlIndexValueIterator<IterationPolity::skipZeros, IteratorType>::SkipZeros()
        {
            while (_current < _end && *_current == 0)
            {
                ++_current;
                ++_index;
            }
        }

        template <typename IteratorType>
        StlIndexValueIterator<IterationPolity::all, IteratorType>::StlIndexValueIterator(
            const IteratorType& begin, const IteratorType& end, size_t size) : 
            _current(begin),
            _end(end),
            _size(size)
        {}

        template <typename IteratorType>
        void StlIndexValueIterator<IterationPolity::all, IteratorType>::Next()
        {
            ++_index;
            if (_current < _end)
            {
                ++_current;
            }
        }

        template <typename IteratorType>
        IndexValue StlIndexValueIterator<IterationPolity::all, IteratorType>::Get() const 
        {
            return _current < _end ? IndexValue{_index, (double)*_current} : IndexValue{_index, 0.0};
        }

        template <IterationPolity policy, typename ElementType>
        VectorIndexValueIterator<policy, ElementType> MakeVectorIndexValueIterator(const std::vector<ElementType>& vector)
        {
            return VectorIndexValueIterator<policy, ElementType>(vector.cbegin(), vector.cend(), vector.size());
        }

        template <IterationPolity policy, typename ElementType>
        VectorIndexValueIterator<policy, ElementType> MakeVectorIndexValueIterator(const std::vector<ElementType>& vector, size_t size)
        {
            return VectorIndexValueIterator<policy, ElementType>(vector.cbegin(), vector.cend(), size);
        }
    }
} // namespace ell


#pragma endregion implementation