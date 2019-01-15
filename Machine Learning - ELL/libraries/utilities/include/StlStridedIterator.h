/**
 * Microsoft - Modern Information Technology
 * https://github.com/Microsoft/ELL/blob/master/libraries/utilities/include/StlStridedIterator.h
 *
 *  Created on: Jan 11, 2019
 *  Student (MIG Virtual Developer): Tung Dang
 */
#pragma once

#include <cstddef>
#include <iterator>

namespace ell 
{
    namespace utilities
    {
        /**
         * A simple stl-type iterator adapter that advances an iterator by a given stride
        */
        template <typename IteratorType>
        class StlStridedIterator
        {
        public:
            using iterator_category = typename std::iterator_traits<IteratorType>::iterator_category;
            using value_type = typename std::iterator_traits<IteratorType>::value_type;
            using difference_type = typename std::iterator_traits<IteratorType>::difference_type;
            using size_type = size_t;
            using reference = typename std::iterator_traits<IteratorType>::reference;
            using const_reference = const reference;
            using pointer = typename std::iterator_traits<IteratorType>::pointer;
            using const_pointer = const pointer;

            StlStridedIterator (const IteratorType& iterator, difference_type stride);

            bool operator==(const StlStridedIterator<IteratorType>& other) const;
            bool operator!=(const StlStridedIterator<IteratorType>& other) const;
            reference operator*();
            const_reference operator*() const;
            pointer operator->();
            const_pointer operator->() const;
            StlStridedIterator<IteratorType>& operator++();
            StlStridedIterator<IteratorType> operator++(int);
            StlStridedIterator<IteratorType>& operator--();
            StlStridedIterator<IteratorType> operator--(int);
            StlStridedIterator<IteratorType>& operator+=(difference_type increment);
            StlStridedIterator<IteratorType>& operator-=(difference_type increment);
            bool operator>(const StlStridedIterator<IteratorType>& other) const;
            bool operator<(const StlStridedIterator<IteratorType>& other) const;
            bool operator>=(const StlStridedIterator<IteratorType>& other) const;
            bool operator<=(const StlStridedIterator<IteratorType>& other) const;
            reference operator[](size_type index);
            const_reference operator[](size_type index) const;

            IteratorType GetBaseIterator() const;
            difference_type GetStride() const;

        protected: 
            IteratorType _iterator;
            difference_type _stride;       
        };

        template <typename IteratorType>
        StlStridedIterator<IteratorType> operator+(const StlStridedIterator<IteratorType>& iterator, typename StlStridedIterator<IteratorType>::difference_type increment);

        template <typename IteratorType>
        StlStridedIterator<IteratorType> operator+(typename StlStridedIterator<IteratorType>::difference_type increment, const StlStridedIterator<IteratorType>& iterator);

        template <typename IteratorType>
        StlStridedIterator<IteratorType> operator-(const StlStridedIterator<IteratorType>& iterator, typename StlStridedIterator<IteratorType>::difference_type increment);

        template <typename IteratorType>
        typename StlStridedIterator<IteratorType>::difference_type operator -(const StlStridedIterator<IteratorType>& iterator1, const StlStridedIterator<IteratorType>& iterator2);

        template <typename IteratorType>
        StlStridedIterator<IteratorType> MakeStlStridedIterator(const IteratorType& iterator, ptrdiff_t stride); 
    }
}

#pragma region implementation

namespace ell
{
    namespace utilities
    {
        template <typename IteratorType>
        StlStridedIterator<IteratorType>::StlStridedIterator(const IteratorType& iterator, difference_type stride) : 
            _iterator(iterator),
            _stride(stride)
        {}

        template <typename IteratorType>
        bool StlStridedIterator<IteratorType>::operator==(const StlStridedIterator<IteratorType>& other) const 
        {
            return _iterator == other._iterator;
        }

        template <typename IteratorType>
        bool StlStridedIterator<IteratorType>::operator!=(const StlStridedIterator<IteratorType>& other) const 
        {
            return _iterator != other._iterator;
        }

        template <typename IteratorType>
        typename StlStridedIterator<IteratorType>::reference StlStridedIterator<IteratorType>::operator*()
        {
            return *_iterator;
        }

        template <typename IteratorType>
        typename StlStridedIterator<IteratorType>::const_reference StlStridedIterator<IteratorType>::operator*() const 
        {
            return *_iterator;
        }

        template <typename IteratorType>
        typename StlStridedIterator<IteratorType>::pointer StlStridedIterator<IteratorType>::operator->()
        {
            return _iterator;
        }

        template <typename IteratorType>
        typename StlStridedIterator<IteratorType>::const_pointer StlStridedIterator<IteratorType>::operator->() const
        {
            return _iterator;
        }

        template <typename IteratorType>
        StlStridedIterator<IteratorType>& StlStridedIterator<IteratorType>::operator++()
        {
            _iterator += _stride;
            return *this;
        }

        template <typename IteratorType>
        StlStridedIterator<IteratorType> StlStridedIterator<IteratorType>::operator++(int)
        {
            auto temp = _iterator;
            _iterator += _stride;
            return {temp, _stride};
        }

        template <typename IteratorType>
        StlStridedIterator<IteratorType>& StlStridedIterator<IteratorType>::operator--()
        {
            _iterator -= _stride;
            return *this;
        }

        template <typename IteratorType>
        StlStridedIterator<IteratorType> StlStridedIterator<IteratorType>::operator--(int)
        {
            auto temp = _iterator;
            _iterator -= _stride;
            return {temp, _stride};
        }

        template <typename IteratorType>
        StlStridedIterator<IteratorType>& StlStridedIterator<IteratorType>::operator+=(difference_type increment)
        {
            _iterator += increment * _stride;
            return *this;
        }

        template <typename IteratorType>
        StlStridedIterator<IteratorType>& StlStridedIterator<IteratorType>::operator-=(difference_type increment)
        {
            _iterator -= increment * _stride;
            return *this;
        }

        template <typename IteratorType>
        bool StlStridedIterator<IteratorType>::operator>(const StlStridedIterator<IteratorType>& other) const 
        {
            return _iterator > other._iterator;
        }

        template <typename IteratorType>
        bool StlStridedIterator<IteratorType>::operator<(const StlStridedIterator<IteratorType>& other) const 
        {
            return _iterator < other._iterator;
        }

        template <typename IteratorType>
        bool StlStridedIterator<IteratorType>::operator>=(const StlStridedIterator<IteratorType>& other) const 
        {
            return _iterator >= other._iterator;
        }

        template <typename IteratorType>
        bool StlStridedIterator<IteratorType>::operator<=(const StlStridedIterator<IteratorType>& other) const 
        {
            return _iterator <= other._iterator;
        }

        template <typename IteratorType>
        typename StlStridedIterator<IteratorType>::reference StlStridedIterator<IteratorType>::operator[](typename StlStridedIterator<IteratorType>::size_type index)
        {
            return _iterator[index * _stride];
        }

        template <typename IteratorType>
        typename StlStridedIterator<IteratorType>::const_reference StlStridedIterator<IteratorType>::operator[](typename StlStridedIterator<IteratorType>::size_type index) const
        {
            return _iterator[index * _stride];
        }

        template <typename IteratorType>
        IteratorType StlStridedIterator<IteratorType>::GetBaseIterator() const 
        {
            return _iterator;
        }

        template <typename IteratorType>
        typename StlStridedIterator<IteratorType>::difference_type StlStridedIterator<IteratorType>::GetStride() const 
        {
            return _stride;
        }

        template <typename IteratorType>
        StlStridedIterator<IteratorType> operator+(const StlStridedIterator<IteratorType>& iterator, typename StlStridedIterator<IteratorType>::difference_type increment) 
        {
            auto result = iterator;
            result += increment;
            return result;
        }

        template <typename IteratorType>
        StlStridedIterator<IteratorType> operator+(typename StlStridedIterator<IteratorType>::difference_type increment, const StlStridedIterator<IteratorType>& iterator)
        {
            auto result = iterator;
            result += increment;
            return result;
        }

        template <typename IteratorType>
        StlStridedIterator<IteratorType> operator-(const StlStridedIterator<IteratorType>& iterator, typename StlStridedIterator<IteratorType>::difference_type increment)
        {
            auto result = iterator;
            result -= increment;
            return result;
        }

        template <typename IteratorType>
        typename StlStridedIterator<IteratorType>::difference_type operator-(const StlStridedIterator<IteratorType>& iterator1, const StlStridedIterator<IteratorType>& iterator2)
        {
            auto p1 = iterator1.GetBaseIterator();
            auto p2 = iterator2.GetBaseIterator();
            return (p1 - p2)/iterator1.GetStride();
        }

        template <typename IteratorType>
        StlStridedIterator<IteratorType> MakeStlStridedIterator(const IteratorType& iterator, ptrdiff_t stride)
        {
            return {iterator, stride};
        }
    } 
}

#pragma endregion implementation