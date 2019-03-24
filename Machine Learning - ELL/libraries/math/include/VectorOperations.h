/**
 * Microsoft - Modern Information Technology
 * https://github.com/Microsoft/ELL/blob/master/libraries/math/include/VectorOperations.h
 *
 *  Created on: Mar 20, 2019
 *  Student (MIG Virtual Developer): Tung Dang
 */

#pragma once

#include "BlasWrapper.h"
#include "Common.h"
#include "Matrix.h"
#include "Transformations.h"
#include "Vector.h"
#include <utilities/include/TypeTraits.h>
#include <ostream>
#include <string>

namespace ell
{
    namespace math 
    {
        /* Prints vector in initializer list format */
        template <typename ElementType, VectorOrientation orientation> 
        void Print(ConstVectorReference<ElementType, orientation> vector, std::ostream& stream, 
                    size_t indent = 0, size_t maxElements = std::numeric_limits<size_t>::max());

        template <typename ElementType, VectorOrientation orientation>
        std::ostream& operator<<(std::ostream& stream, ConstVectorReference<ElementType, orientation> vector);

        template <typename ElementType, VectorOrientation orientation>
        auto Transpose(ConstVectorReference<ElementType, orientation> vector)
        {
            return vector.Transpose();
        }

        /* A class that represents a transformed constant vector */
        template <typename ElementType, VectorOrientation orientation, typename TransformationType>
        class TransformedConstVectorReference 
        {
            public: 
                TransformedConstVectorReference(ConstVectorReference<ElementType, orientation> vector,
                                                    TransformationType Transformation);
                const TransformationType GetTransformation() {return _transformation;}
                ConstVectorReference<ElementType, orientation> GetVector() const 
                {
                    return _vector;
                }

            private: 
                ConstVectorReference<ElementType, orientation> _vector;
                TransformationType _transformation;
        };

        template <typename ElementType, VectorOrientation orientation, typename TransformationType>
        TransformedConstVectorReference<ElementType, orientation, TransformationType> TransformVector(
            ConstVectorReference<ElementType, orientation> vector, TransformationType Transformation);
        
        template <typename ElementType, VectorOrientation orientation>
        auto Square(ConstVectorReference<ElementType, orientation> vector) 
            -> TransformedConstVectorReference<ElementType, orientation, Transformation<ElementType>>;
        
        template <typename ElementType, VectorOrientation orientation>
        auto Sqrt(ConstVectorReference<ElementType, orientation> vector) 
            -> TransformedConstVectorReference<ElementType, orientation, Transformation<ElementType>>;

        template <typename ElementType, VectorOrientation orientation>
        auto Abs(ConstVectorReference<ElementType, orientation> vector)
            -> TransformedConstVectorReference<ElementType, orientation, Transformation<ElementType>>;

        template <typename ElementType>
        struct ScaleFunction
        {
            ElementType _value;
            ElementType operator()(ElementType x);
        };

        template <typename ElementType, VectorOrientation orientation>
        auto operator*(double scalar, ConstVectorReference<ElementType, orientation> vector)
            -> TransformedConstVectorReference<ElementType, orientation, ScaleFunction<ElementType>>;

        template <typename ElementType, VectorOrientation orientation>
        auto Transpose(VectorReference<ElementType, orientation> vector)
        {
            return vector.Transpose();
        }

        template <typename VectorElementType, VectorOrientation orientation, typename ScalarType, 
                    utilities::IsFundamental<ScalarType> concept = true>
        void operator +=(VectorReference<VectorElementType, orientation> vector, ScalarType scalar);

        template <typename ElementType, VectorOrientation orientation>
        void operator +=(VectorReference<ElementType, orientation> vectorB, 
                         ConstVectorReference<ElementType, orientation> vectorA);

        template <typename ElementType, VectorOrientation orientation, typename TransformationType>
        void operator +=(VectorReference<ElementType, orientation> vector, 
            TransformedConstVectorReference<ElementType, orientation, TransformationType> transformedVector);

        template <typename VectorElementType, VectorOrientation orientation, typename ScalarType, 
                    utilities::IsFundamental<ScalarType> concept = true>
        void operator -=(VectorReference<VectorElementType, orientation> vector, ScalarType scalar);   

        template <typename ElementType, VectorOrientation orientation>
        void operator -=(VectorReference<ElementType, orientation> vectorB, 
                         ConstVectorReference<ElementType, orientation> vectorA);    

        template <typename VectorElementType, VectorOrientation orientation, typename ScalarType, 
                    utilities::IsFundamental<ScalarType> concept = true>
        void operator *=(VectorReference<VectorElementType, orientation> vector, ScalarType scalar); 

        template <typename VectorElementType, VectorOrientation orientation, typename ScalarType, 
                    utilities::IsFundamental<ScalarType> concept = true>
        void operator /=(VectorReference<VectorElementType, orientation> vector, ScalarType scalar);

        template <ImplementationType implementation = ImplementationType::openBlas, 
                  typename ElementType, VectorOrientation orientation>
        void AddUpdate(ElementType scalar, VectorReference<ElementType, orientation> vector);

        template <ImplementationType implementation = ImplementationType::openBlas, 
                  typename ElementType, VectorOrientation orientation>
        void AddUpdate(ConstVectorReference<ElementType, orientation> vectorA, 
                        VectorReference<ElementType, orientation> vectorB); 
                    
        template <ImplementationType implementation = ImplementationType::openBlas,
                  typename ElementType, VectorOrientation orientation>
        void AddSet(ElementType scalar, ConstVectorReference<ElementType, orientation> vector, 
                     VectorReference<ElementType, orientation> output);

        template <ImplementationType implementation = ImplementationType::openBlas, 
                  typename ElementType, VectorOrientation orientation>
        void AddSet(ConstVectorReference<ElementType, orientation> vectorA, 
                    ConstVectorReference<ElementType, orientation> vectorB, 
                    VectorReference<ElementType, orientation> output);
        
        template <ImplementationType implementation = ImplementationType::openBlas,
                  typename ElementType, VectorOrientation orientation>
        void ScaleUpdate(ElementType scalar, ConstVectorReference<ElementType, orientation> vector);

        template <ImplementationType implementation = ImplementationType::openBlas, 
                  typename ElementType, VectorOrientation orientation>
        void ScaleSet(ElementType scalar, ConstVectorReference<ElementType, orientation> vector, 
                        VectorReference<ElementType, orientation> output);

        struct OnesVector {};

        // vectorB += scalarA * vectorA
        template <ImplementationType implementation = ImplementationType::openBlas, 
                  typename ElementType, VectorOrientation orientation>
        void ScaleAddUpdate(ElementType scalarA, ConstVectorReference<ElementType, orientation> vectorA, 
                            One, VectorReference<ElementType, orientation> vectorB);

        // vectorB = scalarA * ones + scalarB * vectorB
        template <ImplementationType implementation = ImplementationType::openBlas, 
                  typename ElementType, VectorOrientation orientation>
        void ScaleAddUpdate(ElementType scalarA, OnesVector, 
                            ElementType scalarB, VectorReference<ElementType, orientation> vectorB);

        // vectorB = vectorA + scalarB * vectorB
        template <ImplementationType implementation = ImplementationType::openBlas, 
                  typename ElementType, VectorOrientation orientation>
        void ScaleAddUpdate(One, ConstVectorReference<ElementType, orientation> vectorA, 
                            ElementType scalarB, VectorReference<ElementType, orientation> vectorB);

        // vectorB = scalarA * vectorA + scalarB * vectorB
        template <ImplementationType implementation = ImplementationType::openBlas, 
                  typename ElementType, VectorOrientation orientation>
        void ScaleAddUpdate(ElementType scalarA, VectorReference<ElementType, orientation> vectorA, 
                            ElementType scalarB, VectorReference<ElementType, orientation> vectorB);


        // output = scalarA * vectorA + vectorB
        template <ImplementationType implementation = ImplementationType::openBlas, 
                  typename ElementType, VectorOrientation orientation>
        void ScaleAddSet(ElementType scalarA, ConstVectorReference<ElementType, orientation> vectorA, 
                         One, ConstVectorReference<ElementType, orientation> vectorB, 
                         VectorReference<ElementType, orientation> output);
        // output = scalarA * ones + scalarB * vectorB
        template <ImplementationType implementation = ImplementationType::openBlas, 
                  typename ElementType, VectorOrientation orientation>
        void ScaleAddSet(ElementType scalarA, OnesVector, 
                         ElementType scalarB, ConstVectorReference<ElementType, orientation> vectorB,
                         VectorReference<ElementType, orientation> output);

        // output = vectorA + scalarB * vectorB
        template <ImplementationType implementation = ImplementationType::openBlas, 
                  typename ElementType, VectorOrientation orientation>
        void ScaleAddSet(One, ConstVectorReference<ElementType, orientation> vectorA, 
                         ElementType scalarB, ConstVectorReference<ElementType, orientation> vectorB, 
                         VectorReference<ElementType, orientation> output);

        // output = scalarA * vectorA + scalarB * vectorB
        template <ImplementationType implementation = ImplementationType::openBlas, 
                  typename ElementType, VectorOrientation orientation>
        void ScaleAddSet(ElementType scalarA, ConstVectorReference<ElementType, orientation> vectorA, 
                         ElementType scalarB, ConstVectorReference<ElementType, orientation> vectorB,
                         VectorReference<ElementType, orientation> output);

        template <typename ElementType, VectorOrientation orientation>
        void ElementwiseMultiplySet(ConstVectorReference<ElementType, orientation> vectorA,
                                    ConstVectorReference<ElementType, orientation> vectorB, 
                                    VectorReference<ElementType, orientation> output);

        template <ImplementationType implementation = ImplementationType::openBlas, typename ElementType>
        void InnerProduct (ConstRowVectorReference<ElementType> vectorA, 
                           ConstRowVectorReference<ElementType> vectorB, 
                           ElementType& result);

        template <typename ElementType>
        ElementType Dot(UnorientedConstVectorBase<ElementType> vectorA, 
                        UnorientedConstVectorBase<ElementType> vectorB);

        template <ImplementationType implementation = ImplementationType::openBlas, 
                  typename ElementType, MatrixLayout layout>
        void OuterProduct(ConstColumnVectorReference<ElementType> vectorA, 
                          ConstColumnVectorReference<ElementType> vectorB, 
                          MatrixReference<ElementType, layout> matrix);

        template <typename ElementType, VectorOrientation orientation>
        void CumulativeSumUpdate(VectorReference<ElementType, orientation> vector);

        template <typename ElementType, VectorOrientation orientation>
        void ConsecutiveDifferenceUpdate(VectorReference<ElementType, orientation> vector);

        template <typename ElementType, VectorOrientation orientation, typename TransformationType>
        void TransformUpdate(TransformationType transformation, VectorReference<ElementType, orientation> vector);

        template <typename ElementType, VectorOrientation orientation, typename TransformationType>
        void TransformSet(TransformationType transformation, ConstVectorReference<ElementType, orientation> vector,
                            VectorReference<ElementType, orientation> output);

        template <typename ElementType, VectorOrientation orientation, typename TransformationType>
        void TransformAddUpdate(TransformationType transformation, 
                                ConstVectorReference<ElementType, orientation> vectorA, 
                                VectorReference<ElementType, orientation> vectorB);

        namespace Internal 
        {
            template <ImplementationType implementation>
            struct VectorOperations
            {};   

            template <>
            struct VectorOperations<ImplementationType::native>
            {
                static std::string GetImplementationName() {return "Native";}

                template <typename ElementType>
                static void InnerProduct(ConstRowVectorReference<ElementType> vectorA, ConstColumnVectorReference<ElementType> vectorB, ElementType& result);

                template <typename ElementType, MatrixLayout layout>
                static void OuterProduct(ConstColumnVectorReference<ElementType> vectorA, ConstRowVectorReference<ElementType> vectorB, MatrixReference<ElementType, layout> matrix);

                // vector += scalar
                template <typename ElementType, VectorOrientation orientation>
                static void AddUpdate(ElementType scalar, VectorReference<ElementType, orientation> vector);

                // vectorB += vectorA
                template <typename ElementType, VectorOrientation orientation>
                static void AddUpdate(ConstVectorReference<ElementType, orientation> vectorA, VectorReference<ElementType, orientation> vectorB);

                // output = scalar + vector
                template <typename ElementType, VectorOrientation orientation>
                static void AddSet(ElementType scalar, ConstVectorReference<ElementType, orientation> vector, VectorReference<ElementType, orientation> output);

                // output = vectorA + vectorB
                template <typename ElementType, VectorOrientation orientation>
                static void AddSet(ConstVectorReference<ElementType, orientation> vectorA, ConstVectorReference<ElementType, orientation> vectorB, VectorReference<ElementType, orientation> output);

                // vector *= scalar
                template <typename ElementType, VectorOrientation orientation>
                static void ScaleUpdate(ElementType scalar, VectorReference<ElementType, orientation> vector);

                // output = scalar * vector
                template <typename ElementType, VectorOrientation orientation>
                static void ScaleSet(ElementType scalar, ConstVectorReference<ElementType, orientation> vector, VectorReference<ElementType, orientation> output);

                // vectorB = scalarA * vectorA
                template <typename ElementType, VectorOrientation orientation>
                static void ScaleAddUpdate(ElementType scalarA, ConstVectorReference<ElementType, orientation> vectorA, One, VectorReference<ElementType, orientation> vectorB);

                // vectorB = scalarA * ones + scalarB * vectorB
                template <typename ElementType, VectorOrientation orientation>
                static void ScaleAddUpdate(ElementType scalarA, OnesVector, ElementType scalarB, VectorReference<ElementType, orientation> vectorB);

                // vectorB = vectorA + scalarB * vectorB
                template <typename ElementType, VectorOrientation orientation>
                static void ScaleAddUpdate(One, ConstVectorReference<ElementType, orientation> vectorA, ElementType scalarB, VectorReference<ElementType, orientation> vectorB);

                // vectorB = scalarA * vectorA + scalarB * vectorB
                template <typename ElementType, VectorOrientation orientation>
                static void ScaleAddUpdate(ElementType scalarA, ConstVectorReference<ElementType, orientation> vectorA, ElementType scalarB, VectorReference<ElementType, orientation> vectorB);

                // output = scalarA * vectorA + vectorB
                template <typename ElementType, VectorOrientation orientation>
                static void ScaleAddSet(ElementType scalarA, ConstVectorReference<ElementType, orientation> vectorA, One, ConstVectorReference<ElementType, orientation> vectorB, VectorReference<ElementType, orientation> output);

                // vectorC = scalarA * ones + scalarB * vectorB
                template <typename ElementType, VectorOrientation orientation>
                static void ScaleAddSet(ElementType scalarA, OnesVector, ElementType scalarB, ConstVectorReference<ElementType, orientation> vectorB, VectorReference<ElementType, orientation> output);

                // vectorB = vectorA + scalarB * vectorB
                template <typename ElementType, VectorOrientation orientation>
                static void ScaleAddSet(One, ConstVectorReference<ElementType, orientation> vectorA, ElementType scalarB, ConstVectorReference<ElementType, orientation> vectorB, VectorReference<ElementType, orientation> output);

                // vectorC = scalarA * vectorA + scalarB * vectorB
                template <typename ElementType, VectorOrientation orientation>
                static void ScaleAddSet(ElementType scalarA, ConstVectorReference<ElementType, orientation> vectorA, ElementType scalarB, ConstVectorReference<ElementType, orientation> vectorB, VectorReference<ElementType, orientation> output);
            
            };

            template <>
            struct VectorOperations<ImplementationType::openBlas> : public VectorOperations<ImplementationType::native>
            {};
        }        
    }
}

#pragma region implementation 

#include <utilities/include/Debug.h>
#include <utilities/include/Exception.h>

namespace ell 
{
    namespace math 
    {
        template <typename ElementType, VectorOrientation orientation>
        void Print(ConstVectorReference<ElementType, orientation> vector, std::ostream& stream, size_t indent, size_t maxElements)
        {
            DEBUG_CHECK_SIZES(maxElements < 3, "cannot specify maxElements below 3.");
            stream << std::string(indent, ' ');
            if (vector.Size() == 0)
            {
                stream << "{ }";
            }
            else if (vector.Size() <= maxElements)
            {
                stream << " { " << vector[0];
                for (size_t i=1; i < vector.Size(); ++i)
                {
                    stream << ", " << vector[i];
                }
                stream << " } ";
            }
            else 
            {
                stream << " { " << vector[0];
                for (size_t i = 0; i < maxElements; ++i)
                {
                    stream << ", " << vector[i];
                }
                stream << ", ..., " << vector[vector.Size() - 1] << " } ";
            }
        }

        template <typename ElementType, VectorOrientation orientation>
        std::ostream& operator<<(std::ostream& stream, ConstVectorReference<ElementType, orientation> vector)
        {
            Print(vector, stream);
            return stream;
        }

        template <typename ElementType, VectorOrientation orientation, typename TransformationType>
        TransformedConstVectorReference<ElementType, orientation, TransformationType>::TransformedConstVectorReference(
            ConstVectorReference<ElementType, orientation> vector, TransformationType transformation) : 
            _vector(vector),
            _transformation(std::move(transformation))
        {}

        template <typename ElementType, VectorOrientation orientation, typename TransformationType>
        TransformedConstVectorReference<ElementType, orientation, TransformationType> TransformVector(
            ConstVectorReference<ElementType, orientation> vector, TransformationType transformation)
        {
            return TransformedConstVectorReference<ElementType, orientation, TransformationType>(vector, transformation);
        }

        template <typename ElementType, VectorOrientation orientation>
        auto Square(ConstVectorReference<ElementType, orientation> vector) -> TransformedConstVectorReference<
                    ElementType, orientation, Transformation<ElementType>>
        {
            return TransformVector(vector, SquareTransformation<ElementType>);
        }

        template <typename ElementType, VectorOrientation orientation>
        auto Sqrt(ConstVectorReference<ElementType, orientation> vector) -> TransformedConstVectorReference<
                    ElementType, orientation, Transformation<ElementType>>
        {
            return TransformVector(vector, SquareRootTransformation<ElementType>);
        }

        template <typename ElementType, VectorOrientation orientation>
        auto Abs(ConstVectorReference<ElementType, orientation> vector) -> TransformedConstVectorReference<
                    ElementType, orientation, Transformation<ElementType>>
        {
            return TransformVector(vector, AbsoluteValueTransformation<ElementType>);
        }

        template <typename ElementType>
        ElementType ScaleFunction<ElementType>::operator()(ElementType x) 
        {
            return x * _value;
        }

        template <typename ElementType, VectorOrientation orientation>
        auto operator*(double scalar, ConstVectorReference<ElementType, orientation> vector) -> TransformedConstVectorReference<
                        ElementType, orientation, ScaleFunction<ElementType>>
        {
            ScaleFunction<ElementType> Transformation {static_cast<ElementType>(scalar)};
            return TransformVector(vector, transformation);
        }

        template <typename VectorElementType, VectorOrientation orientation, 
                  typename ScalarElementType, utilities::IsFundamental<ScalarElementType> concept>
        void operator+=(VectorReference<VectorElementType, orientation> vector, ScalarElementType scalar)
        {
            AddUpdate(static_cast<VectorElementType>(scalar), vector);
        }

        template <typename ElementType, VectorOrientation orientation>
        void operator+=(VectorReference<ElementType, orientation> vectorB, 
                        ConstVectorReference<ElementType, orientation> vectorA)
        {
            AddUpdate(vectorA, vectorB);
        }

        template <typename ElementType, VectorOrientation orientation, typename TransformationType>
        void operator+=(VectorReference<ElementType, orientation> vector, 
                        TransformedConstVectorReference<ElementType, orientation, TransformationType> transformedVector)
        {
            TransformAddUpdate(transformedVector.GetTransformation(), transformedVector.GetVector(), vector);
        }

        template <typename VectorElementType, VectorOrientation orientation, 
                  typename ScalarElementType, utilities::IsFundamental<ScalarElementType> concept>
        void operator-=(VectorReference<VectorElementType, orientation> vector, ScalarElementType scalar)
        {
            AddUpdate(static_cast<VectorElementType>(-scalar), vector);
        }

        template <typename ElementType, VectorOrientation orientation>
        void operator-=(VectorReference<ElementType, orientation> vectorB,  
                        ConstVectorReference<ElementType, orientation> vectorA)
        {
            ScaleAddUpdate(static_cast<ElementType>(-1), vectorA, One(), vectorB);
        }

        template <typename VectorElementType, VectorOrientation orientation, 
                  typename ScalarElementType, utilities::IsFundamental<ScalarElementType> concept>
        void operator*=(VectorReference<VectorElementType, orientation> vector, ScalarElementType scalar)
        {
            ScaleUpdate(static_cast<VectorElementType>(scalar), vector);
        }

        template <typename VectorElementType, VectorOrientation orientation, 
                  typename ScalarElementType, utilities::IsFundamental<ScalarElementType> concept>
        void operator/=(VectorReference<VectorElementType, orientation> vector, ScalarElementType scalar)
        {
            DEBUG_THROW(scalar == 0, utilities::NumericException(utilities::NumericExceptionErrors::divideByZero, "Divide by zero."));
            ScaleUpdate(1 / static_cast<VectorElementType>(scalar), vector);
        }

        template <ImplementationType implementation, typename ElementType, VectorOrientation orientation>
        void AddUpdate(ElementType scalar, VectorReference<ElementType, orientation> vector)
        {
            if (scalar == 0)
            {
                return;
            }
            else 
            {
                Internal::VectorOperations<implementation>::AddUpdate(scalar, vector);
            }
        }

        template <ImplementationType implementation, typename ElementType, VectorOrientation orientation>
        void AddUpdate(ConstVectorReference<ElementType, orientation> vectorA, 
                        VectorReference<ElementType, orientation> vectorB)
        {
            DEBUG_CHECK_SIZES(vectorB.Size() != vectorA.Size(), "Incompatible vector sizes.");
            Internal::VectorOperations<implementation>::AddUpdate(vectorA, vectorB);
        }

        template <ImplementationType implementation, typename ElementType, VectorOrientation orientation>
        void AddSet(ElementType scalar, ConstVectorReference<ElementType, orientation> vector, 
                    VectorReference<ElementType, orientation> output)
        {
            if (scalar == 0)
            {
                output.CopyFrom(vector);
            }
            else 
            {
                Internal::VectorOperations<implementation>::AddSet(scalar, vector, output);
            }
        }

        template <ImplementationType implementation, typename ElementType, VectorOrientation orientation>
        void AddSet(ElementType scalar, ConstVectorReference<ElementType, orientation> vector, 
                    VectorReference<ElementType, orientation> output)
        {
            DEBUG_CHECK_SIZES(vectorA.Size() != vectorB.Size(), "Incompatible vector sizes.");
            Internal::VectorOperations<implementation>::AddSet(vectorA, vectorB, output);
        }

        template <ImplementationType implementation, typename ElementType, VectorOrientation orientation>
        void ScaleUpdate(ElementType scalar, VectorReference<ElementType, orientation> vector)
        {
            if (scalar == 1)
            {
                return;
            }
            else if (scalar == 0)
            {
                vector.Reset();
            }
            else 
            {
                Internal::VectorOperations<implementation>::ScaleUpdate(scalar, vector);
            }
        }

        template <ImplementationType implementation, typename ElementType, VectorOrientation orientation>
        void ScaleSet(ElementType scalar, ConstVectorReference<ElementType, orientation> vector, VectorReference<ElementType, orientation> output)
        {
            DEBUG_CHECK_SIZES(vector.Size() != output.Size(), "Incompatible vector sizes.");

            if (scalar == 1)
            {
                output.CopyFrom(vector);
            }
            else if (scalar == 0)
            {
                output.Reset();
            }
            else
            {
                Internal::VectorOperations<implementation>::ScaleSet(scalar, vector, output);
            }
        }

        template <ImplementationType implementation, typename ElementType, VectorOrientation orientation>
        void ScaleAddUpdate(ElementType scalarA, ConstVectorReference<ElementType, orientation> vectorA, One, VectorReference<ElementType, orientation> vectorB)
        {
            DEBUG_CHECK_SIZES(vectorB.Size() != vectorA.Size(), "Incompatible vector sizes.");

            if (scalarA == 0)
            {
                return;
            }
            else if (scalarA == 1)
            {
                AddUpdate<implementation>(vectorA, vectorB);
            }
            else
            {
                Internal::VectorOperations<implementation>::ScaleAddUpdate(scalarA, vectorA, One(), vectorB);
            }
        }

        template <ImplementationType implementation, typename ElementType, VectorOrientation orientation>
        void ScaleAddUpdate(ElementType scalarA, OnesVector, ElementType scalarB, VectorReference<ElementType, orientation> vectorB)
        {
            if (scalarA == 0)
            {
                ScaleUpdate<implementation>(scalarB, vectorB);
            }
            else if (scalarB == 0)
            {
                vectorB.Fill(scalarA);
            }
            else if (scalarB == 1)
            {
                Internal::VectorOperations<implementation>::AddUpdate(scalarA, vectorB);
            }
            else 
            {
                Internal::VectorOperations<implementation>::ScaleAddUpdate(scalarA, OnesVector(), scalarB, vectorB);
            }
        }

        template <ImplementationType implementation, typename ElementType, VectorOrientation orientation>
        void ScaleAddUpdate(One, ConstVectorReference<ElementType, orientation> vectorA, ElementType scalarB, 
                            VectorReference<ElementType, orientation> vectorB)
        {
            DEBUG_CHECK_SIZES(vectorB.Size() != vectorA.Size(), "Incompatible vector sizes.");

            if (scalarB == 0)
            {   
                vectorB.CopyFrom(vectorA);
            }
            else if (scalarB == 1)
            {
                Internal::VectorOperations<implementation>::AddUpdate(vectorA, vectorB);
            }
            else
            {
                Internal::VectorOperations<implementation>::ScaleAddUpdate(One(), vectorA, scalarB, vectorB);
            }
        }

        template <ImplementationType implementation, typename ElementType, VectorOrientation orientation>
        void ScaleAddUpdate(ElementType scalarA, ConstVectorReference<ElementType, orientation> vectorA, ElementType scalarB, VectorReference<ElementType, orientation> vectorB)
        {
            DEBUG_CHECK_SIZES(vectorB.Size() != vectorA.Size(), "Incompatible vector sizes.");

            if (scalarA == 0)
            {
                ScaleUpdate<implementation>(scalarB, vectorB);
            }
            else if (scalarA == 1)
            {
                ScaleAddUpdate<implementation>(One(), vectorA, scalarB, vectorB);
            }
            else if (scalarB == 0)
            {
                Internal::VectorOperations<implementation>::ScaleSet(scalarA, vectorA, vectorB);
            }
            else if (scalarB == 1)
            {
                Internal::VectorOperations<implementation>::ScaleAddUpdate(scalarA, vectorA, One(), vectorB);
            }
            else
            {
                Internal::VectorOperations<implementation>::ScaleAddUpdate(scalarA, vectorA, scalarB, vectorB);
            }
        }
        
            
    } 
}
