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
    } // namespace data
    
}
