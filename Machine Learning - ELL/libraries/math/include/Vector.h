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

        template <typename ElementType>
        ElementType UnorientedConstVectorBase<ElementType>::NormInfinity() const 
        {
            if (_size == 0)
            {
                return 0;
            }

            const ElementType* pData = GetConstDataPointer();
            const ElementType* pEnd = pData + _size * _increment;
            ElementType result = *pData;
            pData += _increment;

            while(pData < pEnd)
            {
                result = std::max(result, std::abs(*pData));
                pData += _increment;
            }
            return result;
        }

        template <typename ElementType>
        template <typename MapperType>
        ElementType UnorientedConstVectorBase<ElementType>::Aggregate(MapperType mapper) const 
        {
            ElementType result = 0;
            const ElementType* current = GetConstDataPointer();
            const ElementType* end = current + _size * _increment;
            while (current < end)
            {
                result += mapper(*current);
                current += _increment;
            }
            return result;
        }

        template <typename ElementType>
        std::vector<ElementType> UnorientedConstVectorBase<ElementType>::ToArray() const 
        {
            std::vector<ElementType> result(_size);

            const ElementType* _pData = GetConstDataPointer();
            for (size_t i=0; i < _size; ++i, _pData += _increment)
            {
                result[i] = *_pData;
            }
            return result;
        }

        /*************************************************************************************************************************************
         ************************************************** Const Vector Reference ***********************************************************
        **************************************************************************************************************************************/

        template <typename ElementType, VectorOrientation orientation>
        ConstVectorReference<ElementType, orientation>::ConstVectorReference(const ElementType* pData, size_t size, size_t increment) : 
            UnorientedConstVectorBase<ElementType>(pData, size, increment)
        {
        }

        template <typename ElementType, VectorOrientation orientation>
        void ConstVectorReference<ElementType, orientation>::Swap(ConstVectorReference<ElementType, orientation>& other)
        {
            UnorientedConstVectorBase<ElementType>::Swap(other);
        }

        template <typename ElementType, VectorOrientation orientation>
        bool ConstVectorReference<ElementType, orientation>::IsEqual(ConstVectorReference<ElementType, orientation> other, ElementType tolerance) const 
        {
            if (this->Size() != other.Size())
            {
                return false;
            }

            const ElementType* pThis = this->GetConstDataPointer();
            const ElementType* pThisEnd = pThis + this->Size() * this->GetIncrement();
            const ElementType* pOther = other.GetConstDataPointer();

            while(pThis < pThisEnd)
            {
                auto diff = (*pThis) - (*pOther);
                if (diff > tolerance || -diff > tolerance)
                {
                    return false;
                }
                pThis += this->GetIncrement();
                pOther += other.GetIncrement();
            }
            return true;
        }

        template <typename ElementType, VectorOrientation orientation>
        bool ConstVectorReference<ElementType, orientation>::operator==(const ConstVectorReference<ElementType, orientation>& other) const 
        {
            return IsEqual(other);
        }

        template <typename ElementType, VectorOrientation orientation>
        bool ConstVectorReference<ElementType, orientation>::operator!=(const ConstVectorReference<ElementType, orientation>& other) const 
        {
            return !(*this == other);
        }

        template <typename ElementType, VectorOrientation orientation>
        ConstVectorReference<ElementType, orientation> ConstVectorReference<ElementType, orientation>::GetSubVector(size_t offset, size_t size) const
        {
            DEBUG_THROW(offset + size > this->Size(), utilities::InputException(utilities::InputExceptionErrors::indexOutOfRange, "subvector offset + subvector size exceeds vector size."));
            return ConstVectorReference<ElementType, orientation>(this->GetConstDataPointer() + offset * this->GetIncrement(), size, this->GetIncrement());
        }

        /*************************************************************************************************************************************
         ******************************************************* Vector Reference ************************************************************
        **************************************************************************************************************************************/

        template <typename ElementType, VectorOrientation orientation>
        VectorReference<ElementType, orientation>::VectorReference(const ElementType* pData, size_t size, size_t increment) : 
            ConstVectorReference<ElementType, orientation>(pData, size, increment)
        {}

        template <typename ElementType, VectorOrientation orientation>
        ElementType& VectorReference<ElementType, orientation>::operator[](size_t index)
        {
            DEBUG_THROW(index >= this->Size(), utilities::InputException(utilities::InputExceptionErrors::indexOutOfRange, "index exceeds vector size."));
            return GetDataPointer()[index * this->GetIncrement()];
        }

        template <typename ElementType, VectorOrientation orientation>
        void VectorReference<ElementType, orientation>::Swap(VectorReference<ElementType, orientation>& other)
        {
            ConstVectorReference<ElementType, orientation>::Swap(other);
        }

        template <typename ElementType, VectorOrientation orientation>
        template <typename OtherElementType>
        void VectorReference<ElementType, orientation>::CopyFrom(ConstVectorReference<OtherElementType, orientation> other)
        {
            if (this->Size() != other.Size())
            {
                throw utilities::InputException(utilities::InputExceptionErrors::invalidArgument, "this vector and other vector are not the same size.");
            }

            ElementType* pData = GetDataPointer();
            const OtherElementType* pOtherData = other.GetConstDataPointer();
            const size_t otherIncrement = other.GetIncrement();
            const OtherElementType* pOtherEnd = pOtherData + otherIncrement * other.Size();

            if (this->GetIncrement() == 1 && otherIncrement == 1)
            {
                while (pOtherData < pOtherEnd)
                {
                    (*pData) = static_cast<ElementType>(*pOtherData);
                    ++pData;
                    ++pOtherData;
                }
            }
            else
            {
                while(pOtherData < pOtherEnd)
                {
                    (*pData) = static_cast<ElementType>(*pOtherData);
                    pData += this->GetIncrement();
                    pOtherData += otherIncrement;
                }
            }
        }

        template <typename ElementType, VectorOrientation orientation>
        void VectorReference<ElementType, orientation>::Reset() 
        {
            Fill(0);
        }

        template <typename ElementType, VectorOrientation orientation>
        void VectorReference<ElementType, orientation>::Fill(ElementType value)
        {
            ElementType* data = GetDataPointer();
            ElementType* end = data + this->Size() * this->GetIncrement();

            if (this->IsContiguous())
            {
                std::fill(data, end, value);
            }
            else
            {
                while (data < end)
                {
                   *data = value;
                   data += this->GetIncrement(); 
                }
            }
        }

        template <typename ElementType, VectorOrientation orientation>
        template <typename GeneratorType>
        void VectorReference<ElementType, orientation>::Generate(GeneratorType generator)
        {
            ElementType* data = GetDataPointer();
            ElementType* end = data + this->Size() * this->GetIncrement();

            while (data < end)
            {
                *data = static_cast<ElementType>(generator());
                data += this->GetIncrement();
            }
        }

        template <typename ElementType, VectorOrientation orientation>
        template <typename TransformationType>
        void VectorReference<ElementType, orientation>::Transform(TransformationType transformation)
        {
            ElementType* pData = this->GetDataPointer();
            const ElementType* pEnd = pData + this->Size() * this->GetIncrement();
            while (pData < pEnd)
            {
                *pData = transformation(*pData);
                pData += this->GetIncrement();
            }
        }

        template <typename ElementType, VectorOrientation orientation>
        VectorReference<ElementType, orientation> VectorReference<ElementType, orientation>::GetReference()
        {
            return VectorReference<ElementType, orientation>(GetDataPointer(), this->Size(), this->GetIncrement());
        }

        template <typename ElementType, VectorOrientation orientation>
        VectorReference<ElementType, orientation> VectorReference<ElementType, orientation>::GetSubVector(size_t offset, size_t size)
        {
            DEBUG_THROW(offset + size > this->Size(), utilities::InputException(utilities::InputExceptionErrors::indexOutOfRange, "subvector offset + subvector size exceeds vector size."));
            return VectorReference<ElementType, orientation>(GetDataPointer() + offset * this->GetIncrement(), size, this->GetIncrement());
        }

        /*************************************************************************************************************************************
         ********************************************************** Vector *******************************************************************
        **************************************************************************************************************************************/

        template <typename ElementType, VectorOrientation orientation>
        Vector<ElementType, orientation>::Vector(size_t size) : 
            VectorReference<ElementType, orientation>(nullptr, size, 1), 
            _data(size)
        {
            this->_pData = _data.data();
        }

        template <typename ElementType, VectorOrientation orientation>
        Vector<ElementType, orientation>::Vector(std::vector<ElementType> data) : 
            VectorReference<ElementType, orientation>(nullptr, data.size(), 1),
            _data(std::move(data))
        {
            this->_pData = _data.data();
        }

        template <typename ElementType, VectorOrientation orientation>
        Vector<ElementType, orientation>::Vector(std::initializer_list<ElementType> list) : 
            VectorReference<ElementType, orientation>(nullptr, list.size(), 1),
            _data(list.begin(), list.end())
        {
            this->_pData = _data.data();
        }

        template <typename ElementType, VectorOrientation orientation> 
        Vector<ElementType, orientation>::Vector(Vector<ElementType, orientation>&& other) : 
            VectorReference<ElementType, orientation>(nullptr, other.Size(), other.GetIncrement()), 
            _data(std::move(other._data))
        {
            this->_pData = _data.data();
        }

        template <typename ElementType, VectorOrientation orientation>
        Vector<ElementType, orientation>::Vector(const Vector<ElementType, orientation>& other) :
            VectorReference<ElementType, orientation>(nullptr, other.Size(), 1),
            _data(other.Size())
        {
            _pData = _data.data();
            this->CopyFrom(other);
        }

        template <typename ElementType, VectorOrientation orientation>
        Vector<ElementType, orientation>::Vector(ConstVectorReference<ElementType, orientation>& other) : 
            VectorReference<ElementType, orientation>(nullptr, other.Size(), 1),
            _data(other.Size())
        {
            _pData = _data.data();
            this->CopyFrom(other);
        }

        template <typename ElementType, VectorOrientation orientation> 
        Vector<ElementType, orientation>::Vector(ConstVectorReference<ElementType, TransposeVectorOrientation<orientation>::value>& other) : 
            VectorReference<ElementType, orientation>(nullptr, other.Size(), 1),
            _data(other.Size())
        {
            _pData = _data.data();
            this->CopyFrom(other);
        }

        template <typename ElementType, VectorOrientation orientation>
        void Vector<ElementType, orientation>::Resize(size_t size)
        {
            _data.resize(size);
            this->_pData = _data.data();
            this->_size = size;
        }

        template <typename ElementType, VectorOrientation orientation>
        Vector<ElementType, orientation>& Vector<ElementType, orientation>::operator=(Vector<ElementType, orientation> other)
        {
            Swap(other);
            return *this;
        }

        template <typename ElementType, VectorOrientation orientation>
        void Vector<ElementType, orientation>::Swap(Vector<ElementType, orientation>& other)
        {
            VectorReference<ElementType, orientation>::Swap(other);
            std::swap(_data, other._data);
        }

        template <typename ElementType, VectorOrientation orientation>
        utilities::StlStridedIterator<typename std::vector<ElementType>::iterator> begin(Vector<ElementType, orientation>& vector)
        {
            return 
            {
                vector._data.begin(),
                static_cast<ptrdiff_t>(vector.GetIncrement())
            };
        }

        template <typename ElementType, VectorOrientation orientation>
        utilities::StlStridedIterator<typename std::vector<ElementType>::const_iterator> begin(const Vector<ElementType, orientation>& vector)
        {
            return {
                vector._data.cbegin(),
                static_cast<ptrdiff_t>(vectro.GetIncrement())
            };
        } 

        template <typename ElementType, VectorOrientation orientation>
        utilities::StlStridedIterator<typename std::vector<ElementType>::iterator> end(Vector<ElementType, orientation>& vector) 
        {
            return {
                vector._data.end(),
                static_cast<ptrdiff_t>(vector.GetIncrement())
            };
        }

        template <typename ElementType, VectorOrientation orientation>
        utilities::StlStridedIterator<typename std::vector<ElementType>::const_iterator> end(const Vector<ElementType, orientation>& vector)
        {
            return {
                vector._data.cend(),
                static_cast<ptrdiff_t>(vector.GetIncrement())
            };
        }

        template <typename ElementType, VectorOrientation orientation>
        void VectorArchiver::Write(const Vector<ElementType, orientation>& vector, const std::string& name, utilities::Archiver& archiver)
        {
            archiver[name] << vector.ToArray();
        }

        template <typename ElementType, VectorOrientation orientation>
        void VectorArchiver::Read(Vector<ElementType, orientation>& vector, const std::string& name, utilities::Unarchiver& archiver)
        {
            std::vector<ElementType> values;
            archiver[name] >> values;
            Vector<ElementType, orientation> value(std::move(values));
            vector.Swap(value);
        }
    }   
}
