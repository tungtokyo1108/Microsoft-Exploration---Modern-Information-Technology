/**
 * Microsoft - Modern Information Technology
 * https://github.com/microsoft/ELL/blob/master/libraries/data/include/TransformingIndexValueIterator.h
 *
 *  Created on: July 24, 2019
 *  Student (MIG Virtual Developer): Tung Dang
 */

#pragma once 

#include "IndexValue.h"
#include <memory>

namespace ell 
{
    namespace data
    {
        template <typename WrappedIndexValueIteratorType, typename TransformationType>
        class TransformingIndexValueIteator : public IIndexValueIterator
        {
            public: 
                TransformingIndexValueIteator(WrappedIndexValueIteratorType wrappedIterator, TransformationType transform);
                bool IsValid() const {return _wrappedIterator.IsValid();}
                void Next() {_wrappedIterator.Next();}
                IndexValue Get() const;

            protected: 
                WrappedIndexValueIteratorType _wrappedIterator;
                TransformationType _transform;
        };

        template <typename WrappedIndexValueIteratorType, typename TransformationType>
        TransformingIndexValueIteator<WrappedIndexValueIteratorType, TransformationType> MakeTransformingIndexValueIterator(
            WrappedIndexValueIteratorType wrappedIterator, TransformationType transform) 
        {
            return TransformingIndexValueIteator<WrappedIndexValueIteratorType, TransformationType>(
                std::move(wrappedIterator), std::move(transform));
        }
    } // namespace data
}

#pragma region implementation 

namespace ell {
    namespace data {
        template <typename WrappedIndexValueIteratorType, typename TransformationType>
        TransformingIndexValueIteator<WrappedIndexValueIteratorType, TransformationType>::TransformingIndexValueIteator(
            WrappedIndexValueIteratorType wrappedIterator, TransformationType transform) :  
            _wrappedIterator(std::move(wrappedIterator)),
            _transform(std::move(transform))
        {}

        template <typename WrappedIndexValueIteratorType, typename TransformationType>
        IndexValue TransformingIndexValueIteator<WrappedIndexValueIteratorType, TransformationType>::Get() const 
        {
            auto indexValue = _wrappedIterator.Get();
            return {indexValue.inde, _transform(indexValue)};
        }
    }
}

#pragma endregion implementation
