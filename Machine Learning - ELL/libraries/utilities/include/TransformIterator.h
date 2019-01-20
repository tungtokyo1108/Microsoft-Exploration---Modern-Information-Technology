/**
 * Microsoft - Modern Information Technology
 * https://github.com/Microsoft/ELL/blob/master/libraries/utilities/include/TransformIterator.h
 *
 *  Created on: Jan 16, 2019
 *  Student (MIG Virtual Developer): Tung Dang
 */

#pragma once 

namespace ell 
{
    namespace utilities
    {
        template <typename InputIteratorType, typename OutType, typename FuncType>
        class TransformIterator 
        {
            public: 
                TransformIterator(InputIteratorType& inIter, FuncType transformFunction);
                bool IsValid() const {return _inIter.IsValid();}
                void Next() {_inIter.Next();}
                OutType Get() const {return _transformFunction(_inIter.Get());}

            private: 
                InputIteratorType& _inIter;
                FuncType _transformFunction;
        };

        template <typename InputIteratorType, typename FuncType>
        auto MakeTransformIterator(InputIteratorType& inIterator, FuncType transformFunction) -> TransformIterator<InputIteratorType, decltype(transformFunction(inIterator.Get())), FuncType>;

    }
}

#pragma region implementation

namespace ell 
{
    namespace utilities
    {
        template <typename InputIteratorType, typename OutType, typename FuncType>
        TransformIterator<InputIteratorType, OutType, FuncType>::TransformIterator(InputIteratorType& inIter, FuncType transformFunction) : 
            _inIter(inIter),
            _transformFunction(transformFunction)
        {}

        template <typename InputIteratorType, typename FuncType>
        auto MakeTransformIterator(InputIteratorType& inIter, FuncType transformFunction) -> TransformIterator<InputIteratorType, decltype(transformFunction(inIter.Get())), FuncType>
        {
            using OutType = decltype(transformFunction(inIter.Get()));
            return TransformIterator<InputIteratorType, OutType, FuncType>(inIter, transformFunction);
        }
    }
}

#pragma endregion implementation