/**
 * Microsoft - Modern Information Technology
 * https://github.com/Microsoft/ELL/blob/master/libraries/math/include/Transformations.h
 *
 *  Created on: Feb 10, 2019
 *  Student (MIG Virtual Developer): Tung Dang
 */

#pragma once 

#include <iostream>
#include <cmath>
#include <utilities/include/TypeTraits.h>

namespace ell 
{
    namespace math
    {
        template <typename ElementType>
        using Transformation = ElementType (*)(ElementType);

        template <typename ElementType>
        constexpr auto SquareRootTransformation = static_cast<Transformation<ElementType>>(std::sqrt);

        template <typename ElementType>
        constexpr auto CubicRootTransformation = static_cast<Transformation<ElementType>>(std::cbrt);

        template <typename ElementType>
        constexpr auto AbsoluteValueTransformation = static_cast<Transformation<ElementType>>(std::abs);

        template <typename ElementType>
        constexpr auto FloorTransformation = static_cast<Transformation<ElementType>>(std::floor);

        template <typename ElementType>
        constexpr auto CeilingTransformation = static_cast<Transformation<ElementType>>(std::ceil);

        template <typename ElementType>
        constexpr auto RoundTransformation = static_cast<Transformation<ElementType>>(std::round);

        template <typename ElementType>
        constexpr auto ExponentTransformation = static_cast<Transformation<ElementType>>(std::exp);

        template <typename ElementType>
        constexpr auto Base2ExponentTransformatin = static_cast<Transformation<ElementType>>(std::exp2);

        template <typename ElementType>
        constexpr auto NaturalLogTransformation = static_cast<Transformation<ElementType>>(std::log);

        template <typename ElementType>
        constexpr auto Base2LogTransformation = static_cast<Transformation<ElementType>>(std::log2);

        template <typename ElementType>
        constexpr auto Base10LogTransformation = static_cast<Transformation<ElementType>>(std::log10);

        template <typename ElementType>
        constexpr auto SineTransformation = static_cast<Transformation<ElementType>>(std::sin);

        template <typename ElementType>
        constexpr auto CosineTransformation = static_cast<Transformation<ElementType>>(std::cos);

        template <typename ElementType>
        constexpr auto TangentTransformation = static_cast<Transformation<ElementType>>(std::tan);

        template <typename ElementType>
        constexpr auto ArcSineTransformation = static_cast<Transformation<ElementType>>(std::asin);

        template <typename ElementType>
        constexpr auto ArcCosineTransformation = static_cast<Transformation<ElementType>>(std::acos);

        template <typename ElementType>
        constexpr auto ArcTangentTransformation = static_cast<Transformation<ElementType>>(std::atan);

        template <typename ElementType>
        constexpr auto HyperbolicSineTransformation = static_cast<Transformation<ElementType>>(std::sinh);

        template <typename ElementType>
        constexpr auto HyperbolicCosineTransformation = static_cast<Transformation<ElementType>>(std::cosh);

        template <typename ElementType>
        constexpr auto HyperbolicTangentTransformation = static_cast<Transformation<ElementType>>(std::tanh);

        template <typename ElementType>
        constexpr auto InverseHyperbolicSineTransformation = static_cast<Transformation<ElementType>>(std::asinh);

        template <typename ElementType>
        constexpr auto InverseHyperbolicCosineTransformation = static_cast<Transformation<ElementType>>(std::acosh);

        template <typename ElementType>
        constexpr auto InverseHyperbolicTangentTranformation = static_cast<Transformation<ElementType>>(std::atanh);

        template <typename ElementType>
        constexpr auto ErrorFunctionTransformation = static_cast<Transformation<ElementType>>(std::erf);

        template <typename ElementType, utilities::IsFundamental<ElementType> concept = true> 
        ElementType SquareTransformationImplementation(ElementType x)
        {
            return x * x;
        }

        template <typename ElementType>
        constexpr auto SquareTransformation = static_cast<Transformation<ElementType>>(SquareTransformationImplementation);
    }
} 
