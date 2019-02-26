/**
 * Microsoft - Modern Information Technology
 * https://github.com/tungtokyo1108/ELL/blob/master/libraries/math/include/Matrix.h
 *
 *  Created on: Feb 07, 2019
 *  Student (MIG Virtual Developer): Tung Dang
 */

#pragma once

#include "Vector.h"
#include <utilities/include/IArchivable.h>
#include <cstddef>
#include <limits>

namespace ell
{
    namespace math
    {
        template <typename ElementType>
        class CommonMatrixBase
        {
            public: 
                size_t NumRows() const {return _numRows;}
                size_t NumColumns() const {return _numColumns;}
                size_t Size() const {return NumRows() * NumColumns();}
                size_t GetIncrement() const {return _increment;}

            protected: 
                CommonMatrixBase(const ElementType* pData, size_t numRows, size_t numColumns, size_t increment);
                void Swap(CommonMatrixBase<ElementType>& other);
                size_t _numRows;
                size_t _numColumns;
                size_t _increment;
        };

        enum class MatrixLayout
        {
            columnMajor,
            rowMajor
        };

        enum class MatrixTranspose
        {
            noTranspose,
            transpose
        };

        template <MatrixLayout>
        struct TransposeMatrixLayout;

        template <>
        struct TransposeMatrixLayout<MatrixLayout::columnMajor> 
        {
            static constexpr MatrixLayout value = MatrixLayout::rowMajor;
        };
        
        template <>
        struct TransposeMatrixLayout<MatrixLayout::rowMajor>
        {
            static constexpr MatrixLayout value = MatrixLayout::columnMajor;
        };

        template <typename ElementType, MatrixLayout layout>
        class MatrixBase;

        template <typename ElementType>
        class MatrixBase<ElementType, MatrixLayout::columnMajor> : public CommonMatrixBase<ElementType>
        {
            public: 
                size_t GetMinorSize() const 
                {
                    return this->NumColumns();
                }

                size_t GetMajorSize() const 
                {
                    return this->NumRows();
                }

                size_t GetRowIncrement() const 
                {
                    return 1;
                }

                size_t GetColumnIncrement() const 
                {
                    return this->GetIncrement();
                }

            protected:
                MatrixBase(const ElementType* pData, size_t numRows, size_t numColumns);
                MatrixBase(const ElementType* pData, size_t numRows, size_t numColumns, size_t increment);
                void Swap(MatrixBase<ElementType, MatrixLayout::columnMajor>& other);
                static constexpr VectorOrientation _intervalOrientation = VectorOrientation::column;
        };

        template <typename ElementType>
        class MatrixBase<ElementType, MatrixLayout::rowMajor> : public CommonMatrixBase<ElementType>
        {
            public: 
                size_t GetMinorSize() const 
                {
                    return this->NumRows();
                }

                size_t GetMajorSize() const
                {
                    return this->NumColumns();
                }

                size_t GetColumnIncrement() const 
                {
                    return 1;
                }

                size_t GetRowIncrement() const 
                {
                    return this->GetIncrement();
                }

            protected: 
                MatrixBase(const ElementType* pData, size_t numRows, size_t numColumns);
                MatrixBase(const ElementType* pData, size_t numRows, size_t numColumns, size_t increment);
                void Swap(MatrixBase<ElementType, MatrixLayout::rowMajor>& other);
                static constexpr 
        };

        template <typename ElementType, MatrixLayout layout>
        class ConstMatrixReference : public MatrixBase<ElementType, layout>
        {
            public:
                ConstMatrixReference(const ElementType* pData, size_t numRows, size_t numColumns);
                ConstMatrixReference(const ElementType* pData, size_t numRows, size_t numColumns, size_t increment);
                MatrixLayout GetLayout() const 
                {
                    return layout;
                }
                inline ElementType operator()(size_t rowIndex, size_t columnIndex) const;
                const ElementType* GetConstDataPointer() const {return this->_pData;}
                std::vector<ElementType> ToArray() const;
                void Swap(ConstMatrixReference<ElementType, layout>& other);
                bool IsContigous() const 
                {
                    return this->GetIncrement() == this->GetMajorSize();
                }
                bool IsEqual(ConstMatrixReference<ElementType, layout> other, ElementType tolerance = static_cast<ElementType>(1.0e-8)) const;
                bool IsEqual(ConstMatrixReference<ElementType, TransposeMatrixLayout<layout>::value> other, 
                             ElementType tolerance = static_cast<ElementType>(1.0e-8)) const;
                bool operator==(const ConstMatrixReference<ElementType, layout>& other) const;
                bool operator==(const ConstMatrixReference<ElementType, TransposeMatrixLayout<layout>::value>& other) const;

                template <MatrixLayout otherLayout>
                bool operator!=(const ConstMatrixReference<ElementType, otherLayout>& other);

                ConstMatrixReference<ElementType, layout> GetConstReference() const {return *this;}
                ConstMatrixReference<ElementType, layout> GetSubMatrix(size_t firstRow, size_t firstColumn, 
                                                            size_t numRows, size_t numColumns) const;
                ConstColumnVectorReference<ElementType> GetColumn(size_t index) const;
                ConstRowVectorReference<ElementType> GetRow(size_t index) const;
                ConstColumnVectorReference<ElementType> GetDiagonal() const;
                
                auto GetMajorVector(size_t index) const
                {
                    return ConstVectorReference<ElementType, MatrixBase<ElementType, layout>::_intervalOrientation>(this->GetMajorVectorBegin(index), this->GetMajorSize(), 1);
                }
                auto Transpose() const -> ConstMatrixReference<ElementType, TransposeMatrixLayout<layout>::value>;
                ConstColumnVectorReference<ElementType> ReferenceAsVector() const;

            protected:
                friend class ConstMatrixReference<ElementType, TransposeMatrixLayout<layout>::value>;
                const ElementType* GetMajorVectorBegin(size_t index) const; 
        };

        template <typename ElementType, MatrixLayout layout>
        class MatrixReference : public ConstMatrixReference<ElementType, layout>
        {
            public:
                MatrixReference(ElementType* pData, size_t numRows, size_t numColumns, size_t increment);
                MatrixReference(ElementType* pData, size_t numRows, size_t numColumns);
                using ConstMatrixReference<ElementType, layout>::operator();
                inline ElementType& operator()(size_t rowIndex, size_t columnsIndex);
                ElementType* GetDataPointer() 
                {
                    return const_cast<ElementType*>(this->_pData);
                }
                using ConstMatrixReference<ElementType, layout>::IsContigous;
                void CopyFrom(ConstMatrixReference<ElementType, layout> other);
                void CopyFrom(ConstMatrixReference<ElementType, TransposeMatrixLayout<layout>::value> other);
                void Swap(MatrixReference<ElementType, layout>& other);
                void Reset() {Fill(0);}
                void Fill(ElementType value);
                
                template <typename GeneratorType>
                void Generate(GeneratorType generator);
                template <typename TransformationType>
                void Transform(TransformationType transformation);

                using ConstMatrixReference<ElementType, layout>::GetSubMatrix;
                using ConstMatrixReference<ElementType, layout>::GetColumns;
                using ConstMatrixReference<ElementType, layout>::GetRow;
                using ConstMatrixReference<ElementType, layout>::GetDiagonal;
                using ConstMatrixReference<ElementType, layout>::GetMajorVector;
                using ConstMatrixReference<ElementType, layout>::Transpose;
                using ConstMatrixReference<ElementType, layout>::ReferenceAsVector;

                MatrixReference<ElementType, layout> GetReference() 
                {
                    return *this;
                }

                auto Transpose() -> MatrixReference<ElementType, TransposeMatrixLayout<layout>::value>;
                MatrixReference<ElementType, layout> GetSubMatrix(size_t firstRow, size_t firstColumn, size_t numRows, size_t numColumns);
                ColumnVectorReference<ElementType> GetColumn(size_t index);
                RowVectorReference<ElementType> GetRow(size_t index);
                ColumnVectorReference<ElementType> GetDiagonal();
                ColumnVectorReference<ElementType> ReferenceAsVector();
                auto GetMajorVector(size_t index)
                {
                    return VectorReference<ElementType, MatrixBase<ElementType, layout>::_internalOrientation>(this->GetMajorVectorBegin(index), this->GetMajorSize(),1);
                }
            protected:
                friend MatrixReference<ElementType, TransposeMatrixLayout<layout>::value>;
        };

        template <typename ElementType, MatrixLayout layout>
        class Matrix : public MatrixReference<ElementType, layout>
        {
            public: 
                Matrix(size_t numRows, size_t numColumns);
                Matrix(std::initializer_list<std::initializer_list<ElementType>> list);
                Matrix(size_t numRows, size_t numColumns, const std::vector<ElementType>& data);
                Matrix(size_t numRows, size_t numColumns, std::vector<ElementType>&& data);
                Matrix(Matrix<ElementType, layout>&& other);
                Matrix(const Matrix<ElementType, layout>& other);
                Matrix(ConstMatrixReference<ElementType, layout>& other);
                Matrix(ConstMatrixReference<ElementType, TransposeMatrixLayout<layout>::value> other);
                Matrix<ElementType, layout>& operator=(Matrix<ElementType, layout> other);
                std::vector<ElementType> ToArray() const 
                {
                    return _data;
                }
                void Swap(Matrix<ElementType, layout>& other);
            
            private:
                std::vector<ElementType> _data;
        };

        class MatrixArchiver
        {
            public: 
                template<typename ElementType, MatrixLayout layout>
                static void Write(const Matrix<ElementType, layout>& matrix, const std::string& name, utilities::Archiver& archiver);

                template<typename ElementType, MatrixLayout layout>
                static void Read(Matrix<ElementType, layout>& matrix, const std::string& name, utilities::Unarchiver& archiver);

            private:
                static std::string GetRowsName(const std::string& name) {return name + "_rows";}
                static std::string GetColumnsName(const std::string& name) {return name + "_columns";}
                static std::string GetValuesName(const std::string& name) {return name + "_values";}
        };

        template <typename ElementType>
        using ColumnMatrix = Matrix<ElementType, MatrixLayout::columnMajor>;

        template <typename ElementType>
        using ColumnMatrixReference = MatrixReference<ElementType, MatrixLayout::columnMajor>;

        template <typename ElementType>
        using RowMatrix = Matrix<ElementType, MatrixLayout::rowMajor>;

        template <typename ElementType>
        using RowMatrixReference = MatrixReference<ElementType, MatrixLayout::rowMajor>;

        template <typename ElementType>
        using ConstRowMatrixReference = ConstMatrixReference<ElementType, MatrixLayout::rowMajor>;
    }
} 

#pragma region implementation 

#include <utilities/include/Debug.h>
#include <utilities/include/Exception.h>
#include <utilities/include/Unused.h>

#include <algorithm>

namespace ell 
{
    namespace math
    {
        template <typename ElementType>
        CommonMatrixBase<ElementType>::CommonMatrixBase(const ElementType* pData, size_t numRows, size_t numColumns, size_t increment) :
            _pData(pData),
            _numRows(numRows),
            _numColumns(numColumns),
            _increment(increment) 
        {}

        template <typename ElementType>
        void CommonMatrixBase<ElementType>::Swap(CommonMatrixBase<ElementType>& other) 
        {
            using std::swap;
            swap(_pData, other._pData);
            swap(_numRows, other._numRows);
            swap(_numColumns, other._numColumns);
            swap(_increment, other._increment);
        }

        template <typename ElementType>
        MatrixBase<ElementType, MatrixLayout::rowMajor>::MatrixBase(const ElementType* pData, 
                    size_t numRows, size_t numColumns) : 
            CommonMatrixBase<ElementType>(pData, numRows, numColumns)
        {}

        template <typename ElementType>
        MatrixBase<ElementType, MatrixLayout::rowMajor>::MatrixBase(const ElementType* pData,
                    size_t numRows, size_t numColumns, size_t increment) :
            CommonMatrixBase<ElementType>(pData, numRows, numColumns, increment)
        {}

        template <typename ElementType>
        void MatrixBase<ElementType, MatrixLayout::rowMajor>::Swap(
                    MatrixBase<ElementType, MatrixLayout::rowMajor>& other)
        {
            CommonMatrixBase<ElementType>::Swap(other);
        }

        template <typename ElementType>
        MatrixBase<ElementType, MatrixLayout::columnMajor>::MatrixBase(const ElementType* pData,
                    size_t numRows, size_t numColumns) : 
            CommonMatrixBase<ElementType>(pData, numRows, numColumns, numRows)
        {}

        template <typename ElementType>
        MatrixBase<ElementType, MatrixLayout::columnMajor>::MatrixBase(const ElementType* pData, 
                    size_t numRows, size_t numColumns, size_t increment) : 
            CommonMatrixBase<ElementType>(pData, numRows, numColumns, increment)
        {}

        template <typename ElementType>
        void MatrixBase<ElementType, MatrixLayout::columnMajor>::Swap(
                    MatrixBase<ElementType,MatrixLayout::columnMajor>& other) 
        {
            CommonMatrixBase<ElementType>::Swap(other);
        }
        
        template <typename ElementType, MatrixLayout layout>
        ConstMatrixReference<ElementType, layout>::ConstMatrixReference(const ElementType* pData,
                    size_t numRows, size_t numColumns, size_t increment) :
            MatrixBase<ElementType, layout>(pData, numRows, numColumns, increment)
        {}

        template <typename ElementType, MatrixLayout layout>
        ConstMatrixReference<ElementType, layout>::ConstMatrixReference(const ElementType* pData, 
                    size_t numRows, size_t numColumns) : 
            MatrixBase<ElementType, layout>(pData, numRows, numColumns)
        {}

        template <typename ElementType, MatrixLayout layout>
        ElementType ConstMatrixReference<ElementType, layout>::operator()(size_t rowIndex, size_t columnIndex) const 
        {
            using namespace std::string_literals;
            using std::to_string;
            DEBUG_THROW(rowIndex >= this->NumRows() || columnIndex >= this->NumColumns(), 
                utilities::InputException(utilities::InputExceptionErrors::indexOutOfRange, 
                "("s + to_string(rowIndex) + "," + to_string(columnIndex) + ") exceeds matrix dimensions (" + 
                to_string(this->NumRows()) + "x" + to_string(this->NumColumns()) + ")."));
            
            return GetConstDataPointer()[rowIndex * this->GetRowIncrement() + columnIndex * this->GetColumnsIncrement()];
        }

        template <typename ElementType, MatrixLayout layout>
        std::vector<ElementType> ConstMatrixReference<ElementType, layout>::ToArray() const
        {
            std::vector<ElementType> v(this->Size());
            auto vIterator = v.begin();
            for (size_t i=0; i < this->GetMinorSize(); ++i)
            {
                auto pIntervalData = GetMajorVectorBegin(i);
                std::copy(pIntervalData, pIntervalData + this->GetMajorSize(), vIterator);
                vIterator += this->GetMajorSize();
            }
            return v;
        }

        template <typename ElementType, MatrixLayout layout>
        void ConstMatrixReference<ElementType, layout>::Swap(ConstMatrixReference<ElementType, layout>& other)
        {
            MatrixBase<ElementType, layout>::Swap(other);
        }

        template <typename ElementType, MatrixLayout layout>
        bool ConstMatrixReference<ElementType, layout>::IsEqual(ConstMatrixReference<ElementType, layout> other, 
                    ElementType tolerance) const
        {
            if (this->NumRows() != other.NumRows() || this->NumColumns() != other.NumColumns())
            {
                return false;
            }

            for (size_t i=0; i < this->GetMinorSize(); ++i)
            {
                if (!GetMajorVector(i).IsEqual(other.GetMajorVector(i), tolerance))
                {
                    return false;
                }
            }
            return true;
        }

        template <typename ElementType, MatrixLayout layout>
        bool ConstMatrixReference<ElementType, layout>::IsEqual(ConstMatrixReference<ElementType, 
            TransposeMatrixLayout<layout>::value> other, ElementType tolerance) const 
        {
            if (this->NumRows() != other.NumRows() || this->NumColumns() != other.NumColumns())
            {
                return false;
            }
            for (size_t i=0; i < this->NumRows(); ++i)
            {
                if (!GetRow(i).IsEqual(other.GetRow(i), tolerance))
                {
                    return false;
                }
            }
            return true;
        }

        template <typename ElementType, MatrixLayout layout>
        bool ConstMatrixReference<ElementType, layout>::operator==(const ConstMatrixReference<ElementType, layout>& other) const 
        {
            return IsEqual(other);
        }

        template <typename ElementType, MatrixLayout layout>
        bool ConstMatrixReference<ElementType, layout>::operator==(
            const ConstMatrixReference<ElementType, TransposeMatrixLayout<layout>::value>& other) const 
        {
            return IsEqual(other);
        }    

        template <typename ElementType, MatrixLayout layout>
        template <MatrixLayout otherLayout>
        bool ConstMatrixReference<ElementType, layout>::operator!=(const ConstMatrixReference<ElementType, otherLayout>& other)
        {
            return !(*this == other);
        }

        template <typename ElementType, MatrixLayout layout>
        ConstMatrixReference<ElementType, layout> ConstMatrixReference<ElementType, layout>::GetSubMatrix(
            size_t firstRow, size_t firstColumn, size_t numRows, size_t numColumns) const 
        {
            DEBUG_THROW(firstRow + numRows > this->NumRows() || firstColumn + numColumns > this->NumColumns(),
                utilities::InputException(utilities::InputExceptionErrors::indexOutOfRange, "block exceeds matrix dimensions."));
            return ConstMatrixReference<ElementType, layout>(GetConstDataPointer() + firstRow * this->GetRowIncrement()
                + firstColumn * this->GetColumnIncrement(), numRows, numColumns, this->GetIncrement());    
        }

        template <typename ElementType, MatrixLayout layout>
        ConstColumnVectorReference<ElementType> ConstMatrixReference<ElementType, layout>::GetColumn(size_t index) const 
        {
            DEBUG_THROW(index >= this->NumColumns(),
                utilities::InputException(utilities::InputExceptionErrors::indexOutOfRange, "column index exeeds matrix dimensions"));
            return ConstColumnVectorReference<ElementType>(GetConstDataPointer() + index * this->GetColumnIncrement(),
                this->NumRows(), this->GetRowIncrement());
        }
        template <typename ElementType, MatrixLayout layout>
        ConstRowVectorReference<ElementType> ConstMatrixReference<ElementType, layout>::GetRow(size_t index) const
        {
            DEBUG_THROW(index >= this->NumRows(),
                utilities::InputException(utilities::InputExceptionErrors::indexOutOfRange, "row index exeeds matrix dimensions"));
            return ConstRowVectorReference<ElementType>(GetConstDataPointer() + index * this->GetRowIncrement(),
                this->NumColumns(), this->GetColumnIncrement());
        }

        template <typename ElementType, MatrixLayout layout>
        ConstColumnVectorReference<ElementType> ConstMatrixReference<ElementType, layout>::GetDiagonal() const
        {
            auto size = std::min(this->NumColumns(), this->NumRows());
            return ConstColumnVectorReference<ElementType>(GetConstDataPointer(), size, this->GetIncrement() + 1);
        }

        template <typename ElementType, MatrixLayout layout>
        ConstColumnVectorReference<ElementType> ConstMatrixReference<ElementType, layout>::ReferenceAsVector() const 
        {
            DEBUG_THROW(!IsContigous(), utilities::InputException(utilities::InputExceptionErrors::indexOutOfRange, "Can not flatten a matrix when its memory is contigous"));
            return ConstColumnVectorReference<ElementType>(GetConstDataPointer(), this->NumRows() * this->NumColumns(), 1);
        }

        template <typename ElementType, MatrixLayout layout>
        auto ConstMatrixReference<ElementType, layout>::Transpose() const -> ConstMatrixReference<ElementType, TransposeMatrixLayout<layout>::value>
        {
            return ConstMatrixReference<ElementType, TransposeMatrixLayout<layout>::value>(
                GetConstDataPointer(), this->NumColumns(), this->NumRows(), this->GetIncrement());
        }

        template <typename ElementType, MatrixLayout layout>
        const ElementType* ConstMatrixReference<ElementType, layout>::GetMajorVectorBegin(size_t index) const 
        {
            return GetConstDataPointer() + index * this->GetIncrement();
        }

        template <typename ElementType, MatrixLayout layout>
        MatrixReference<ElementType, layout>::MatrixReference(ElementType *pData, size_t numRows, 
                        size_t numColums, size_t increment) : 
            ConstMatrixReference<ElementType, layout>(pData, numRows, numColums, increment)
        {}

        template <typename ElementType, MatrixLayout layout>
        MatrixReference<ElementType, layout>::MatrixReference(ElementType *pData, size_t numRows, size_t numColumns) :
            ConstMatrixReference<ElementType, layout>(pData, numRows, numColumns)
        {}

        template <typename ElementType, MatrixLayout layout>
        ElementType& MatrixReference<ElementType, layout>::operator()(size_t rowIndex, size_t columnIndex)
        {
            using namespace std::string_literals;
            using std::to_string;
            DEBUG_THROW(rowIndex >= this->NumRows() || columnIndex >= this->NumColumns(), 
                utilities::InputException(utilities::InputExceptionErrors::indexOutOfRange, 
                "("s + to_string(rowIndex) + "," + to_string(columnIndex) + ") exceeds matrix dimensions (" +
                to_string(this->NumRows()) + "x" + to_string(this->NumColumns()) + ")."));
            return GetDataPointer()[rowIndex * this->GetRowIncrement() + columnIndex * this->GetColumnIncrement()];
        } 

        template <typename ElementType, MatrixLayout layout>
        void MatrixReference<ElementType, layout>::CopyFrom(ConstMatrixReference<ElementType, layout> other)
        {
            if (this->NumRows() != other.NumRows() || this->NumColumns() != other.NumColumns())
            {
                throw utilities::InputException(utilities::InputExceptionErrors::invalidArgument, "Matrix diemensions are not the same");
            }

            for (size_t i=0; i < other.GetMinorSize(); ++i)
            {
                GetMajorVector(i).CopyFrom(other.GetMajorVector(i));
            }
        }

        template <typename ElementType, MatrixLayout layout>
        void MatrixReference<ElementType, layout>::CopyFrom(ConstMatrixReference<ElementType, TransposeMatrixLayout<layout>::value> other)
        {
            if (this->NumRows() != other.NumRows() || this->NumColumns() != other.NumColumns())
            {
                throw utilities::InputException(utilities::InputExceptionErrors::invalidArgument, "Matrix diemensions are not the same");
            }

            for (size_t i=0; i < other.NumRows(); ++i)
            {
                GetRow(i).CopyFrom(other.GetRow(i));
            }
        }

        template <typename ElementType, MatrixLayout layout>
        void MatrixReference<ElementType, layout>::Swap(MatrixReference<ElementType, layout>& other)
        {
            ConstMatrixReference<ElementType, layout>::Swap(other);
        }

        template <typename ElementType, MatrixLayout layout>
        void MatrixReference<ElementType, layout>::Fill(ElementType value)
        {
            for (size_t i=0; i < this->GetMinorSize(); ++i)
            {
                auto vector = GetMajorVector(i);
                vector.Fill(value);
            }
        }

        template <typename ElementType, MatrixLayout layout>
        template <typename GeneratorType>
        void MatrixReference<ElementType, layout>::Generate(GeneratorType generator)
        {
            for (size_t i=0; i < this->GetMinorSize(); ++i)
            {
                GetMajorVector(i).Generate(generator);
            }
        }

        template <typename ElementType, MatrixLayout layout>
        template <typename TransformationType>
        void MatrixReference<ElementType, layout>::Transform(TransformationType transformation)
        {
            for (size_t i=0; i < this->GetMinorSize(); ++i)
            {
                TransformUpdate(transformation, GetMajorVector());
            }
        }

        template <typename ElementType, MatrixLayout layout>
        auto MatrixReference<ElementType, layout>::Transpose() -> MatrixReference<ElementType, TransposeMatrixLayout<layout>::value>
        {
            return MatrixReference<ElementType, TransposeMatrixLayout<layout>::value>(GetDataPointer(), 
                            this->NumColumns(), this->NumRows(), this->GetIncrement());
        }

        template <typename ElementType, MatrixLayout layout>
        MatrixReference<ElementType, layout> MatrixReference<ElementType, layout>::GetSubMatrix(
            size_t firstRow, size_t firstColumn, size_t numRows, size_t numColumns)
        {
            DEBUG_THROW(firstRow + numRows > this->NumRows() || firstColumn + numColumns > this->NumColumns(),
                utilities::InputException(utilities::InputExceptionErrors::indexOutOfRange, "block exceeds matrix dimensions"));
            return MatrixReference<ElementType, layout>(GetDataPointer() + firstRow * this->GetRowIncrement() 
                + firstColumn * this->GetColumnIncrement(), numRows, numColumns, this->GetIncrement());
        }

        template <typename ElementType, MatrixLayout layout>
        ColumnVectorReference<ElementType> MatrixReference<ElementType, layout>::GetColumn(size_t index)
        {
            DEBUG_THROW(index >= this->NumColumns(),
                utilities::InputException(utilities::InputExceptionErrors::indexOutOfRange, "column exceeds matrix dimensions"));
            return ColumnVectorReference<ElementType>(GetDataPointer() + index * this->GetColumnIncrement(),
                                this->NumRows(), this->GetRowIncrement());
        }

        template <typename ElementType, MatrixLayout layout>
        RowVectorReference<ElementType> MatrixReference<ElementType, layout>::GetRow(size_t index)
        {
            DEBUG_THROW(index >= this->NumRows(),
                utilities::InputException(utilities::InputExceptionErrors::indexOutOfRange, "row exceeds matrix dimensions"));
            return RowVectorReference<ElementType>(GetDataPointer() + index * this->GetRowIncrement(),
                                this->NumColumns(), this->GetColumnIncrement());
        }

        template <typename ElementType, MatrixLayout layout>
        ColumnVectorReference<ElementType> MatrixReference<ElementType, layout>::GetDiagonal()
        {
            auto size = std::min(this->NumColumns(), this->NumRows());
            return ColumnVectorReference<ElementType>(GetDataPointer(), size, this->GetIncrement() + 1);
        }

        template <typename ElementType, MatrixLayout layout>
        ColumnVectorReference<ElementType> MatrixReference<ElementType, layout>::ReferenceAsVector()
        {
            DEBUG_THROW(!IsContiguous(), utilities::InputException(utilities::InputExceptionErrors::indexOutOfRange, "Can only flatten a matrix when its memory is contiguous"));
            return ColumnVectorReference<ElementType>(GetDataPointer(), this->NumRows() * this->NumColumns(), 1);
        }

        template <typename ElementType, MatrixLayout layout>
        Matrix<ElementType, layout>::Matrix(size_t numRows, size_t numColumns) : 
            MatrixReference<ElementType, layout>(nullptr, numRows, numColumns),
            _data(numRows * numColumns)
        {
            this->_pData = _data.data();
        }

        template <typename ElementType, MatrixLayout layout>
        Matrix<ElementType, layout>::Matrix(std::initializer_list<std::initializer_list<ElementType>> list) : 
            MatrixReference<ElementType, layout>(nullptr, list.size(), list.begin()->size()),
            _data(list.size() * list.begin()->size())
        {
            this->_pData = _data.data();
            auto numColumns = list.begin()->size();
            DEBUG_USED(numColumns);
            size_t i = 0;
            for (auto rowIter = list.begin(); rowIter < list.end(); ++rowIter)
            {
                DEBUG_THROW(rowIter->size() != numColumns, utilities::InputException(utilities::InputExceptionErrors::sizeMismatch, "incorrect number of elements in initializer list"));
                size_t j = 0;
                for (auto elementIter = rowIter->begin(); elementIter < rowIter->end(); ++elementIter)
                {
                    (*this)(i, j) = *elementIter;
                    ++j;
                }
                ++i;
            }
        }

        template <typename ElementType, MatrixLayout layout>
        Matrix<ElementType, layout>::Matrix(size_t numRows, size_t numColumns, const std::vector<ElementType>& data) : 
            MatrixReference<ElementType, layout>(nullptr, numRows, numColumns), 
            _data(data)
        {
            this->_pData = _data.data();
        }

        template <typename ElementType, MatrixLayout layout>
        Matrix<ElementType, layout>::Matrix(size_t numRows, size_t numColumns, std::vector<ElementType>&& data) : 
            MatrixReference<ElementType, layout>(nullptr, numRows, numColumns),
            _data(std::move(data))
        {
            this->_pData = _data.data();
        }

        template <typename ElementType, MatrixLayout layout>
        Matrix<ElementType, layout>::Matrix(Matrix<ElementType, layout>&& other) : 
            MatrixReference<ElementType, layout>(nullptr, other.NumRows(), other.NumColumns()),
            _data(std::move(other._data))
        {
            this->_pData = _data.data();
        }

        template <typename ElementType, MatrixLayout layout>
        Matrix<ElementType, layout>::Matrix(const Matrix<ElementType, layout>& other) : 
            MatrixReference<ElementType, layout>(nullptr, other.NumRows(), other.NumColumns()),
            _data(other._data)
        {
            this->_pData = _data.data();
        }

        template <typename ElementType, MatrixLayout layout>
        Matrix<ElementType, layout>::Matrix(ConstMatrixReference<ElementType, layout>& other) : 
            MatrixReference<ElementType, layout>(nullptr, other.NumRows(), other.NumColumns()), 
            _data(other.NumRows() * other.NumColumns())
        {
            this->_pData = _data.data();
            for (size_t i=0; i < this->NumRows(); ++i)
            {
                for (size_t j=0; j < this->NumColumns(); ++j)
                {
                    (*this)(i,j) = other(i,j);
                }
            }
        }

        
    }
}
