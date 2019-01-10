/**
 * Microsoft - Modern Information Technology
 * https://github.com/Microsoft/ELL/blob/master/libraries/utilities/include/TypeName.h
 *
 *  Created on: Jan 07, 2019
 *  Student (MIG Virtual Developer): Tung Dang
 */
#pragma once

#include "TypeTraits.h"
#include <cstddef>
#include <memory>
#include <string>
#include <vector>

namespace ell 
{
    namespace utilities
    {
        class IArchivable;

        template <typename CheckType>
        class HasGetTypeName
        {
            template <typename>
            static constexpr std::false_type FindGetTypeName(...);

            template <typename T>
            static constexpr auto FindGetTypeName(T*) -> typename std::is_same<std::string, decltype(std::declval<T>().GetTypeName())>::type;

            typedef decltype(FindGetTypeName<CheckType>(nullptr)) type;

            public:
            static constexpr bool value = type::value;
        };

        template <typename Type>
        std::string GetTypeName();

        template <typename... Types>
        std::string GetCompositeTypeName(std::string baseType);
        std::string GetCompositeTypeName(std::string baseType, const std::vector<std::string>& subtypes);

        template <typename T, typename Enable = void>
        struct TypeName;

        template <typename T>
        struct TypeName<T, std::enable_if_t<HasGetTypeName<std::decay_t<T>>::value>>
        {
            static std::string GetName();
        };

        template <typename T>
        struct TypeName<T, std::enable_if_t<std::is_enum<std::decay_t<T>>::value>>
        {
            static std::string GetName();
        };
        
        /**
         * Class used to get information about pointer types 
        */
        template <typename T>
        struct TypeName<T*>
        {
            static std::string GetName();
        };

        template <typename T>
        struct TypeName<std::unique_ptr<T>> 
        {
            static std::string GetName();
        };

        template <typename T>
        struct TypeName<std::vector<T>>
        {
            static std::string GetName();
        };

        template <typename T>
        struct TypeName<const std::vector<T>&>
        {
            static std::string GetName();
        };

        template <typename... T>
        struct TypeName<std::tuple<T...>>
        {
            static std::string GetName()
            {
                return GetCompositeTypeName<std::decay_t<T>...>("tuple");
            }
        };

        template<>
        struct TypeName<bool>
        {
            static std::string GetName() {return "bool";}
        };

        template<>
        struct TypeName<char>
        {
            static std::string GetName() {return "char";}
        };

        template<>
        struct TypeName<int8_t>
        {
            static std::string GetName() {return "int8_t";}
        };

        template<>
        struct TypeName<uint8_t>
        {
            static std::string GetName() {return "uint8_t";}
        };

        // Get information about 16-bits integer type
        template<>
        struct TypeName<short>
        {
            static std::string GetName() {return "short";}
        };

        template<>
        struct TypeName<unsigned short>
        {
            static std::string GetName() {return "unsigned short";}
        };

        // Get information about 32-bit integer type 
        template<>
        struct TypeName<int>
        {
            static std::string GetName() {return "int";}
        };

        template<>
        struct TypeName<unsigned int>
        {
            static std::string GetName() {return "unsigned int";}
        };

        // Get information about 64-bit integer type 
        template<>
        struct TypeName<long>
        {
            static std::string GetName() {return "long";}
        };

        template<>
        struct TypeName<unsigned long>
        {
            static std::string GetName() {return "unsigned long";}
        };

        template<>
        struct TypeName<long long>
        {
            static std::string GetName() {return "long long";}
        };

        template<>
        struct TypeName<unsigned long long>
        {
            static std::string GetName() {return "unsigned long long";}
        };

        template<>
        struct TypeName<float>
        {
            static std::string GetName() {return "float";}
        };

        template<>
        struct TypeName<double>
        {
            static std::string GetName() {return "double";}
        };

        template<>
        struct TypeName<std::string>
        {
            static std::string GetName() {return "string";}
        };

        template<>
        struct TypeName<void>
        {
            static std::string GetName() {return "void";}
        };

        template<>
        struct TypeName<void*>
        {
            static std::string GetName() {return "void*";}
        };

        template<>
        struct TypeName<std::true_type>
        {
            static std::string GetName() {return "true_type";}
        };

        template<>
        struct TypeName<std::false_type>
        {
            static std::string GetName() {return "false_type";}
        };

        template<>
        struct TypeName<IArchivable>
        {
            static std::string GetName() {return "IArchivable";}
        };

        template<>
        struct TypeName<const IArchivable>
        {
            static std::string GetName() {return "Const IArchivable";}
        };
    }
}

#pragma region implementation

namespace ell
{
    namespace utilities
    {
        template <typename T>
        std::string TypeName<T, std::enable_if_t<HasGetTypeName<std::decay_t<T>>::value>>::GetName()
        {
            return std::string(std::decay_t<T>::GetTypeName());
        };

        template <typename T>
        std::string TypeName<T, std::enable_if_t<std::is_enum<std::decay_t<T>>::value>>::GetName()
        {
            return "enum";
        };

        template <typename T>
        std::string TypeName<T*>::GetName()
        {
            return GetCompositeTypeName<T>("ptr");
        }

        template <typename T>
        std::string TypeName<std::unique_ptr<T>>::GetName()
        {
            return GetCompositeTypeName<T>("unique_ptr");
        }

        template <typename T>
        std::string TypeName<std::vector<T>>::GetName()
        {
            return GetCompositeTypeName<T>("vector");
        }

        template <typename T>
        std::string TypeName<const std::vector<T>&>::GetName()
        {
            return GetCompositeTypeName<T>("vector");
        }

        template <typename Type>
        std::string GetTypeName() 
        {
            return TypeName<typename std::decay_t<Type>>::GetName();
        }

        template <typename... Types>
        std::string GetCompositeTypeName(std::string baseType)
        {
            auto typeStrings = std::vector<std::string>{ TypeName<Types>::GetName()... };
            return GetCompositeTypeName(baseType, typeStrings);
        }
    }
}

#pragma endregion implementation
