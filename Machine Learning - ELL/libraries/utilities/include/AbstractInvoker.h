/**
 * Microsoft - Modern Information Technology
 * https://github.com/Microsoft/ELL/blob/master/libraries/utilities/include/AbstractInvoker.h
 *
 *  Created on: Dec 25, 2018
 *  Student (MIG Virtual Developer): Tung Dang
 */

#include "Exception.h"

namespace ell
{
    namespace utilities
    {
        /**
         * A helper class that casts a reference to a polymorphic base class into a reference to 
         * a derived class before sending the reference as the argument of a functor. 
         * Using the AbstractInvoker, we can call the templated function given a pointer to the base class
        */
        template <typename BaseType, typename... DerivedTypes>
        class AbstractInvoker;

        template <typename BaseType, typename DerivedType, typename... DerivedTypes>
        class AbstractInvoker<BaseType, DerivedType, DerivedTypes...>
        {
            public: 
            template <typename ReturnType, typename FunctorType>
            static ReturnType Invoke(const FunctorType& functor, const BaseType* basePointer);
        };

        template <typename BaseType>
        class AbstractInvoker<BaseType>
        {
            public: 
            template <typename ReturnType, typename FunctorType>
            static ReturnType Invoke(const FunctorType& functor, const BaseType* basePointer);
        };
    }
}

#pragma region implementation

namespace ell 
{
    namespace utilities
    {
        template <typename BaseType, typename DerivedType, typename... DerivedTypes>
        template <typename ReturnType, typename FunctorType>
        ReturnType AbstractInvoker<BaseType, DerivedType, DerivedTypes...>::Invoke(const FunctorType& functor, const BaseType* basePointer)
        {
            const DerivedType* ptr = dynamic_cast<const DerivedType*>(basePointer);
            if (ptr != nullptr)
            {
                return functor(ptr);
            }
            else
            {
                return AbstractInvoker<BaseType, DerivedTypes...>::template Invoke<ReturnType>(functor, basePointer);
            }
        }

        template <typename BaseType>
        template <typename ReturnType, typename FunctorType>
        ReturnType AbstractInvoker<BaseType>::Invoke(const FunctorType& /**/, const BaseType* /**/)
        {
            throw LogicException(LogicExceptionErrors::illegalState, "base type reference could not be matched with a derived type");
        }
    }
}

#pragma endregion implementation