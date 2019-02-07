/**
 * Microsoft - Modern Information Technology
 * https://github.com/Microsoft/ELL/blob/master/libraries/utilities/include/TypeTraits.h
 *
 *  Created on: Jan 07, 2019
 *  Student (MIG Virtual Developer): Tung Dang
 */

#pragma once

#include <type_traits>
#include <vector>
#include <iostream>

namespace ell 
{
    namespace utilities 
    {
        namespace detail
        {
            template <typename T>
            struct IsVectorType : std::false_type
            {};

            template <typename T, typename A>
            struct IsVectorType<std::vector<T,A>> : std::true_type
            {};
        }

        template <typename ValueType>
        using IsBoolean = std::enable_if_t<std::is_same<std::decay_t<ValueType>, bool>::value, bool>;

        /*Enabled if the two classes are different*/
        template <typename T, typename S>
        using IsDifferent = std::enable_if_t<!std::is_same<T,S>::value, bool>;

        /**
         * Enabled if ValueType 
         * - is an enum
         * - is an floating point type
         * - is or is not a fundamental type
         * - is an integer type
         * - is an integer value that is not a boolean 
         * - is or is not specialization of std::vector
        */
        template <typename ValueType>
        using IsEnum = std::enable_if_t<std::is_enum<ValueType>::value, bool>;

        template <typename ValueType>
        using IsFloatingPoint = std::enable_if_t<std::is_floating_point<std::decay_t<ValueType>>::value, bool>;

        template <typename ValueType>
        using IsFundamental = std::enable_if_t<std::is_fundamental<std::decay_t<ValueType>>::value, bool>;

        template <typename ValueType>
        using IsNotFundamental = std::enable_if_t<!std::is_fundamental<std::decay_t<ValueType>>::value, bool>;

        template <typename ValueType>
        using IsIntegral = std::enable_if_t<std::is_integral<std::decay_t<ValueType>>::value, bool>;

        template <typename ValueType>
        using IsNonBoolIntegral = std::enable_if_t<std::is_integral<std::decay_t<ValueType>>::value && !std::is_same<std::decay_t<ValueType>, bool>::value, bool>;

        template <typename ValueType>
        using IsSignedIntegral = std::enable_if_t<std::is_integral<std::decay_t<ValueType>>::value && std::is_signed<std::decay_t<ValueType>>::value, bool>;

        template <typename ValueType>
        using IsUnsignedIntegral = std::enable_if_t<std::is_integral<std::decay_t<ValueType>>::value && std::is_unsigned<std::decay_t<ValueType>>::value, bool>;

        template <typename T, typename S>
        using IsSame = std::enable_if_t<std::is_same<T,S>::value, bool>;

        template <typename ValueType>
        using IsVector = std::enable_if_t<detail::IsVectorType<std::decay_t<ValueType>>{}, bool>;

        template <typename ValueType>
        using IsNotVector = std::enable_if_t<detail::IsVectorType<std::decay_t<ValueType>>{}, bool>;

        template <typename T>
        struct IdentityType 
        {
            using Type = T;
        };

        template <typename T>
        using IdentityTypeT = typename IdentityType<T>::Type;

        namespace detail 
        {
            // template <typename T, bool = std::is_pointer_v<T>>
            template <typename T, bool = std::is_pointer<T>::value>
            struct RemoveAllPointers 
            {
                static constexpr size_t NumPointers = 1 + RemoveAllPointers<std::remove_pointer_t<T>>::NumPointers;
                using Type = typename RemoveAllPointers<std::remove_pointer_t<T>>::Type;
            };

            template <typename T>
            struct RemoveAllPointers<T, false>
            {
                static constexpr size_t NumPointers = 0;
                using Type = T;
            };
        }

        template <typename T>
        using RemoveAllPointersT = typename detail::RemoveAllPointers<T>::Type;

        /*Provides a count of the number of pointers a given type has*/
        template <typename T>
        inline constexpr size_t CountOfPointers = detail::RemoveAllPointers<T>::NumPointers;

        template <typename... T>
        struct VariantVisitor : T... 
        {
            using T::operator()...;
        };

        // template <typename... T>
        // VariantVisitor(T...)->VariantVisitor<T...>;

        /*namespace detail
        {
            template <typename T, typename... Ts>
            struct IsOneOf : template<> std::disjunction<std::is_same<T,Ts...>...>
            {};
        }

        template <typename T, typename... TypesToCheckAgainst>
        inline constexpr bool IsOneOf = detail::IsOneOf<T, TypesToCheckAgainst...>::value;

        namespace detail
        {
            template <typename T1, typename... Ts>
            struct AllSame : std::conjunction<std::is_same<T1,Ts>...>
            {};
        }

        template <typename T, typename... RestOfTypes>
        inline constexpr bool AllSame = detail::AllSame<T, RestOfTypes...>::value;
        */
    }
}
