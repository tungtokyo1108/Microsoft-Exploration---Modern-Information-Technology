/**
 * Microsoft - Modern Information Technology
 * https://github.com/Microsoft/ELL/blob/master/libraries/utilities/include/TypeTraits.h
 *
 *  Created on: Jan 07, 2019
 *  Student (MIG Virtual Developer): Tung Dang
 */

#include <type_traits>
#include <vector>

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
    }
}