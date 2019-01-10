/**
 * Microsoft - Modern Information Technology
 * https://github.com/Microsoft/ELL/blob/master/libraries/utilities/include/TypeFactory.h
 *
 *  Created on: Jan 07, 2019
 *  Student (MIG Virtual Developer): Tung Dang
 */

#include "Debug.h"
#include "Exception.h"

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

namespace ell 
{
    namespace utilities 
    {
        template <typename BaseType>
        class TypeFactory 
        {
            public:
            std::unique_ptr<BaseType> Construct(const std::string& typeName) const;
            template <typename RuntimeType>
            void AddType();

            template <typename RuntimeType>
            void AddType(const std::string& typeName);

            private: 
            std::unordered_map<std::string, std::function<std::unique_ptr<BaseType>()>> _typeMap;
        };

        class TypeConstructorBase 
        {
            public: 
            virtual ~TypeConstructorBase() = default;

            private: 
            friend class GenericTypeFactory;
            template <typename BaseType>
            std::unique_ptr<BaseType> Construct() const;
        };

        /*A factory object that can create new object given their type name and a base type to derive from*/
        class GenericTypeFactory
        {
            public: 
            template <typename BaseType>
            std::unique_ptr<BaseType> Construct(const std::string& typeName) const;

            template <typename BaseType, typename RuntimeType>
            void AddType();

            template <typename BaseType, typename RuntimeType>
            void AddType(const std::string& typenName);

            private:
            std::unordered_map<std::string, std::shared_ptr<TypeConstructorBase>> _typeConstructorMap;
        };
    }
}

#pragma region implementation 

namespace ell 
{
    namespace utilities
    {
        template <typename BaseType>
        std::unique_ptr<BaseType> TypeFactory<BaseType>::Construct(const std::string& typeName) const 
        {
            auto entry = _typeMap.find(typeName);
            if (entry == _typeMap.end())
            {
                throw utilities::InputException(utilities::InputExceptionErrors::invalidArgument, "type " + typeName + " not registered in TypeFactory<" + BaseType::GetTypeName() + ">");
            }
            return entry->second();
        }

        template <typename BaseType>
        template <typename RuntimeType>
        void TypeFactory<BaseType>::AddType()
        {
            std::string typeName = RuntimeType::GetTypeName();
            AddType<RuntimeType>(typeName);
        }

        template <typename BaseType>
        template <typename RuntimeType>
        void TypeFactory<BaseType>::AddType(const std::string& typeName)
        {
            static_assert(std::is_base_of<BaseType, RuntimeType>::value, "incompatible base and runtime types in TypeFactory::Add");
            DEBUG_THROW(_typeMap.find(typeName) != _typeMap.end(), std::logic_error(typeName + " has already been added to the type factory"));
            _typeMap[typeName] = []() ->std::unique_ptr<BaseType> {return (std::make_unique<RuntimeType>());};
        }

        template <typename BaseType>
        class TypeConstructorDerived : public TypeConstructorBase
        {
            public: 
                template <typename RuntimeType>
                static std::unique_ptr<TypeConstructorDerived<BaseType>> NewTypeConstructor()
                {
                    auto result = std::make_unique<TypeConstructorDerived<BaseType>>();
                    result->_createFunction = []() {
                        auto runtimePtr = new RuntimeType();
                        auto basePtr = dynamic_cast<BaseType*>(runtimePtr);
                        return std::unique_ptr<BaseType>(basePtr);
                    };
                    return result;
                }

                std::unique_ptr<BaseType> Construct() const 
                {
                    return _createFunction();
                }
            
            private: 
                std::function<std::unique_ptr<BaseType>()> _createFunction;
        };

        template <typename BaseType>
        std::unique_ptr<BaseType> TypeConstructorBase::Construct() const 
        {
            auto thisPtr = dynamic_cast<const TypeConstructorDerived<BaseType>*>(this);
            if (thisPtr == nullptr)
            {
                throw InputException(InputExceptionErrors::typeMismatch, std::string{ "TypeConstructorBase::Construct called with wrong type. BaseType: " } + BaseType::GetTypeName());
            }
            return thisPtr->Construct();
        }

        template <typename BaseType>
        std::unique_ptr<BaseType> GenericTypeFactory::Construct(const std::string& typeName) const 
        {
            auto baseTypeName = std::string{BaseType::GetTypeName()};
            auto key = baseTypeName + "__" + typeName;
            auto entry = _typeConstructorMap.find(key);
            if (entry == _typeConstructorMap.end())
            {
                throw utilities::InputException(utilities::InputExceptionErrors::invalidArgument, "type " + typeName + " not registered in TypeFactory<" + BaseType::GetTypeName() + ">");
            }
            return entry->second->Construct<BaseType>();
        }

        template <typename BaseType, typename RuntimeType>
        void GenericTypeFactory::AddType()
        {
            auto typeName = RuntimeType::GetTypeName();
            AddType<BaseType, RuntimeType>(typeName);
        }

        template <typename BaseType, typename RuntimeType>
        void GenericTypeFactory::AddType(const std::string& typeName)
        {
            auto baseTypeName = std::string{BaseType::GetTypeName()};
            auto key = baseTypeName + "__" + typeName;
            auto derivedCreator = TypeConstructorDerived<BaseType>::template NewTypeConstructor<RuntimeType>().release();
            _typeConstructorMap[key] = std::shared_ptr<TypeConstructorBase>(derivedCreator);
        }
    }
}
