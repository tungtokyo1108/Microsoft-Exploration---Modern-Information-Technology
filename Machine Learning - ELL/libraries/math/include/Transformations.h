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

        
    }
} 
