/**
 * Microsoft - Modern Information Technology
 * https://github.com/tungtokyo1108/ELL/blob/master/libraries/math/include/Vector.h
 *
 *  Created on: Feb 07, 2019
 *  Student (MIG Virtual Developer): Tung Dang
 */

#pragma once

#include <utilities/include/IArchivable.h>
#include <utilities/include/StlStridedIterator.h>

#include <cmath>
#include <limits>
#include <vector>

namespace ell 
{
    namespace math 
    {
        enum class VectorOrientation
        {
            column,
            row
        };

        template <VectorOrientation orientation>
        struct TransposeVectorOrientation;

        template <>
        struct TransposeVectorOrientation<VectorOrientation::row>
        {
            static constexpr VectorOrientation value = VectorOrientation::column;
        };

        template <>
        struct TransposeVectorOrientation<VectorOrientation::column>
        {
            static constexpr VectorOrientation value = VectorOrientation::row;
        };

        template <typename ElementType>
        class UnorientedConstVectorBase
        {
            public: 
                UnorientedConstVectorBase(const ElementType* pData, size_t size, size_t increment = 1);
                UnorientedConstVectorBase(const UnorientedConstVectorBase&) = default;

                inline const ElementType& operator[] (size_t index) const;
                size_t Size() const {return _size;}
                const ElementType* GetConstDataPointer() const {return _pData;}
                size_t GetIncrement() const {return _increment;}

                /* Determines if this Vector is stored in contiguous memory */
                bool IsContiguous() const {return _increment == 1;}
                void Swap(UnorientedConstVectorBase<ElementType>& other);

                ElementType Norm0() const;
                ElementType Norm1() const;
                ElementType Norm2() const;
                ElementType Norm2Squared() const;
                ElementType NormInfinity() const;

                template <typename MapperType>
                ElementType Aggregate(MapperType mapper) const;

                std::vector<ElementType> ToArray() const;

            protected: 
                const ElementType* _pData;
                size_t _size;
                size_t _increment;
        };

        template <typename ElementType, VectorOrientation orientation>
        class ConstVectorReference : public UnorientedConstVectorBase<ElementType>
        {
            ConstVectorReference(const ElementType* pData, size_t size, size_t increment = 1);
            void Swap(ConstVectorReference<ElementType, orientation>& other);
            bool IsEqual(ConstVectorReference<ElementType, orientation> other, ElementType tolerance = 1.0e-8) const;
            bool operator==(const ConstVectorReference<ElementType, orientation>& other) const;
            bool operator==(const ConstVectorReference<ElementType, TransposeVectorOrientation<orientation>::value>&) const {return false;}
            bool operator!=(const ConstVectorReference<ElementType, orientation>& other) const;
            bool operator!=(const ConstVectorReference<ElementType, TransposeVectorOrientation<orientation>::value>&) const {return true;}

            ConstVectorReference<ElementType, orientation> GetConstDataPointer() const {return *this;}
            ConstVectorReference<ElementType, orientation> GetSubVector(size_t offset, size_t size) const;
            auto Transpose() const -> ConstVectorReference<ElementType, TransposeVectorOrientation<orientation>::value>
            {
                return ConstVectorReference<ElementType, TransposeVectorOrientation<orientation>::value>(this->GetConstDataPointer(), this->Size(), this->GetIncrement());
            }
        };

        template <typename ElementType, VectorOrientation oerientation>
        class VectorReference : public ConstVectorReference<ElementType, orientation>
        {
            public: 
                VectorReference(const ElementType* pData, size_t size, size_t increment = 1);

                using ConstVectorReference<ElementType, orientation>::operator[];
                using ConstVectorReference<ElementType, orientation>::GetSubVector;
                using ConstVectorReference<ElementType, orientation>::Transpose;

                inline ElementType& operator[](size_t index);
                ElementType* GetDataPointer() {return const_cast<ElementType*>(this->_pData);}
                void Swap(VectorReference<ElementType, orientation>& other);
                
                template <typename OtherElementType>
                void CopyFrom(ConstVectorReference<OtherElementType, orientation> other);
                
                void Reset();
                void Fill(ElementType value);
                
                template <typename GeneratorType>
                void Generate(GeneratorType generator);

                template <typename TransformationType>
                void Transform(TransformationType transformation);

                VectorReference<ElementType, orientation> GetReference();
                VectorReference<ElementType, orientation> GetSubVector(size_t offset, size_t size);

                auto Transpose() -> VectorReference<ElementType, TransposeVectorOrientation<orientation>::value>
                {
                    return VectorReference<ElementType, TransposeVectorOrientation<orientation>::value>(this->GetDataPointer(), this->Size(), this->GetIncrement());
                }
        };

        template <typename ElementType, VectorOrientation orientation>
        class Vector : public VectorReference<ElementType, orientation>
        {
            public: 
                // Constructs an all-zeros vector of a given size
                Vector(size_t size = 0);
                
                // Constructs a vector by copying a std::vector 
                Vector(std::vector<ElementType> data);
                
                // Constructs a vector from an initializer list
                Vector(std::initializer_list<ElementType> list);

                // Move constructor
                Vector(Vector<ElementType, orientation>&& other);

                // Copy Constructor 
                Vector(const Vector<ElementType, orientation>& other);
                Vector(ConstVectorReference<ElementType, orientation>& other);

                // Copy a vector of the opposite orientation 
                Vector(ConstVectorReference<ElementType, TransposeVectorOrientation<orientation>::value>& other);

                // Assignment operator 
                Vector<ElementType, orientation>& operator=(Vector<ElementType, orientation> other);

                void Resize(size_t size);
                void Swap(Vector<ElementType, orientation>& other);

            private: 
                using ConstVectorReference<ElementType, orientation>::_pData;
                using ConstVectorReference<ElementType, orientation>::_size;
                using ConstVectorReference<ElementType, orientation>::_increment;

                template<typename T, VectorOrientation O>
                friend auto begin(Vector<T,O>& vector) -> utilities::StlStridedIterator<typename std::vector<T>::iterator>;

                template<typename T, VectorOrientation O>
                friend auto end(Vector<T,O>& vector) -> utilities::StlStridedIterator<typename std::vector<T>::iterator>;

                template<typename T, VectorOrientation O>
                friend auto begin(const Vector<T,O>& vector) -> utilities::StlStridedIterator<typename std::vector<T>::const_iterator>;

                template<typename T, VectorOrientation O>
                friend auto end(const Vector<T,O>& vector) -> utilities::StlStridedIterator<typename std::vector<T>::const_iterator>;

                std::vector<ElementType> _data;
        };

        // Get iterator to the beginning of a vector 
        template <typename ElementType, VectorOrientation orientation>
        auto begin(Vector<ElementType, orientation>& vector) -> utilities::StlStridedIterator<typename std::vector<ElementType>::iterator>;

        template <typename ElementType, VectorOrientation orientation>
        auto begin(const Vector<ElementType, orientation>& vector) -> utilities::StlStridedIterator<typename std::vector<ElementType>::const_iterator>;

        // Get iterator to the end of a vector 
        template <typename ElementType, VectorOrientation orientation>
        auto end(Vector<ElementType, orientation>& vector) -> utilities::StlStridedIterator<typename std::vector<ElementType>::iterator>;

        template <typename ElementType, VectorOrientation orientation>
        auto end(const Vector<ElementType, orientation>& vector) -> utilities::StlStridedIterator<typename std::vector<ElementType>::const_iterator>;

        class VectorArchiver
        {
            public: 
                template <typename ElementType, VectorOrientation orientation>
                static void Write(const Vector<ElementType, orientation>& vector, const std::string& name, utilities::Archiver& archiver);

                template <typename ElementType, VectorOrientation orientation>
                static void Read(Vector<ElementType, orientation>& vector, const std::string& name, utilities::Unarchiver& archiver);
        };

        template <typename ElementType>
        using ColumnVector = Vector<ElementType, VectorOrientation::column>;

        template <typename ElementType>
        using ColumnVectorReference = VectorReference<ElementType, VectorOrientation::column>;

        template <typename ElementType>
        using ConstColumnVectorReference = ConstVectorReference<ElementType, VectorOrientation::column>;

        template <typename ElementType>
        using RowVector = Vector<ElementType, VectorOrientation::row>;

        template <typename ElementType>
        using RowVectorReference = VectorReference<ElementType, VectorOrientation::row>;

        template <typename ElementType>
        using ConstRowVectorReference = ConstVectorReference<ElementType, VectorOrientation::row>;
    }
}

#pragma region implementation 

#include <utilities/include/Debug.h>
#include <utilities/include/Exception.h>

namespace ell 
{
    namespace math 
    {
        template <typename ElementType>
        UnorientedConstVectorBase<ElementType>::UnorientedConstVectorBase(const ElementType* pData, size_t size, size_t increment) : 
            _pData(pData),
            _size(size),
            _increment(increment)
        {}

        template <typename ElementType>
        const ElementType& UnorientedConstVectorBase<ElementType>::operator[](size_t index) const
        {
            DEBUG_THROW(index >= _size, utilities::InputException(utilities::InputExceptionErrors::indexOutOfRange, "index exceeds vector size"));
            return GetConstDataPointer()[index * _increment];
        }

        template <typename ElementType>
        void UnorientedConstVectorBase<ElementType>::Swap(UnorientedConstVectorBase<ElementType>& other)
        {
            std::swap(_pData, other._pData);
            std::swap(_size, other._size);
            std::swap(_increment, other._increment);
        }

        template <typename ElementType>
        ElementType UnorientedConstVectorBase<ElementType>::Norm0() const
        {
            return Aggregate([](ElementType x) {return x != 0 ? 1 : 0; });
        }

        template <typename ElementType>
        ElementType UnorientedConstVectorBase<ElementType>::Norm1() const
        {
            return Aggregate([](ElementType x) {return std::abs(x);});
        }

        template <typename ElementType>
        ElementType UnorientedConstVectorBase<ElementType>::Norm2() const 
        {
            return std::sqrt(Norm2Squared());
        }

        template <typename ElementType>
        ElementType UnorientedConstVectorBase<ElementType>::Norm2Squared() const
        {
            return Aggregate([](ElementType x) {return x * x;});
        }

        
    }   
}
