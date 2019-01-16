/**
 * Microsoft - Modern Information Technology
 * https://github.com/Microsoft/ELL/blob/master/libraries/utilities/include/StlContainerIterator.h
 *
 *  Created on: Jan 16, 2019
 *  Student (MIG Virtual Developer): Tung Dang
 */

#pragma once 

#include <cstddef>
#include <vector>

namespace ell
{
    namespace utilities
    {
        /**
         * An adapter that transforms a begin/end pair of STL iterators into a read-only forward itertor
         * with IsValid, Next, and Get Funtions 
        */
       template <typename IteratorType>
       class StlContainerIteratorBase
       {
           public: 
            StlContainerIteratorBase() = default;
            StlContainerIteratorBase(IteratorType begin, IteratorType end);
            bool IsValid() const {return _current != _end;}
            bool HasSize() const {return true;}
            size_t NumItemsLeft() const {return _end - _current;}
            void Next();

           protected: 
            IteratorType _current;
            IteratorType _end; 
       };

       template <typename IteratorType, typename ValueType = typename std::iterator_traits<std::decay_t<IteratorType>>::value_type>
       class StlContainerIterator : public StlContainerIteratorBase<IteratorType>
       {
           using BaseType = StlContainerIteratorBase<IteratorType>;

           public: 
            using BaseType::BaseType;
            ValueType Get() const {return *_current;}

           protected: 
            using BaseType::_current; 
       };

       template <typename ValueType>
       using VectorIterator = StlContainerIterator<typename std::vector<ValueType>::const_iterator>;

       template <typename IteratorType>
       auto MakeStlContainerIterator(IteratorType begin, IteratorType end) -> StlContainerIterator<IteratorType>;

       template <typename ContainerType>
       auto MakeStlContainerIterator(ContainerType& container) -> StlContainerIterator<typename ContainerType::iterators, typename ContainerType::value_type>;

       /**
        * An adapter that transforms a begin/end pair of STL iterators into 
        * a read-only forward iterator with IsValid, Next and Get Function  
       */
       template <typename IteratorType, typename ValueType = typename std::iterator_traits<std::decay_t<IteratorType>>::value_type>
       class StlContainerReferenceIterator : public StlContainerIteratorBase<IteratorType>
       {
           using BaseType = StlContainerIteratorBase<IteratorType>;

           public: 
            using BaseType::BaseType;
            const ValueType& Get() const {return *_current;}

           protected: 
            using BaseType::_current; 
       };

       template <typename ValueType>
       using VectorReferenceIterator = StlContainerReferenceIterator<typename std::vector<ValueType>::const_iterator>;

       template <typename IteratorType>
       auto MakeStlContainerReferenceIterator(IteratorType begin, IteratorType end) -> StlContainerReferenceIterator<IteratorType>;

       template <typename ContainerType>
       auto MakeStlContainerReferenceIterator(ContainerType& container) -> StlContainerReferenceIterator<typename ContainerType::iterator, typename ContainerType::value_type>;
    }
}

#pragma region implementation

namespace ell
{
    namespace utilities
    {
        template <typename IteratorType>
        StlContainerIteratorBase<IteratorType>::StlContainerIteratorBase(IteratorType begin, IteratorType end) : 
            _current(begin),
            _end(end)
        {}

        template <typename IteratorType>
        void StlContainerIteratorBase<IteratorType>::Next()
        {
            if (IsValid())
            {
                ++_current;
            }
        }

        template <typename IteratorType>
        StlContainerIterator<IteratorType> MakeStlContainerIterator(IteratorType begin, IteratorType end) 
        {
            return StlContainerIterator<IteratorType>(begin, end);
        }

        template <typename ContainerType>
        StlContainerIterator<typename ContainerType::iterator, typename ContainerType::value_type> MakeStlContainerIterator(ContainerType& container) 
        {
            return StlContainerIterator<typename ContainerType::iterator, typename ContainerType::value_type>(container.begin(), container.end());
        }

        template <typename IteratorType>
        StlContainerReferenceIterator<IteratorType> MakeStlContainerReferenceIterator(IteratorType begin, IteratorType end)
        {
            return StlContainerReferenceIterator<IteratorType>(begin, end);
        }

        template <typename ContainerType>
        StlContainerReferenceIterator<typename ContainerType::iterator, typename ContainerType::value_type> MakeStlContainerReferenceIterator(ContainerType& container)
        {
            return StlContainerReferenceIterator<typename ContainerType::iterator, typename ContainerType::value_type>(container.begin(), container.end());
        }
    }
}

#pragma endregion implementation