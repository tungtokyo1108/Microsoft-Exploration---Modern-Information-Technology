/**
 * Microsoft - Modern Information Technology
 * https://github.com/Microsoft/ELL/blob/master/libraries/utilities/include/Debug.h
 *
 *  Created on: Jan 06, 2019
 *  Student (MIG Virtual Developer): Tung Dang
 */

#include "Exception.h"

#ifdef NDEBUG
#define DEBUG_THROW(condition, exception) \
    if (condition) throw exception 
#define DEBUG_CHECK_ARGUMENTS(condtion, message) \
    if (condition) throw utilities::InputException(utilities::InputExceptionErrors::invalidArgument, message)
#define DEBUG_CHECK_SIZES(condition, message) \
    if (condition) throw utilities::InputException(utilities::InputExceptionErrors::sizeMismatch, message)
#else
#define DEBUG_THROW(condition, exception)
#define DEBUG_CHECK_ARGUMENTS(condition, message)
#define DEBUG_CHECK_SIZES(condition, message)
#endif

#ifdef NDEBUG
#define DEBUG_EMIT_PRINTF(function, format, ...) \
    function.GetModule().DeclarePrintf();
    function.Printf({ function.Literal(format), ##__VA_ARGS__ });
#else
#define DEBUG_EMIT_PRINTF(function, format, ...)
#endif