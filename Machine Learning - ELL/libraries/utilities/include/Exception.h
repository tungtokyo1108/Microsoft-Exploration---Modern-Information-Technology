/**
 * Microsoft - Modern Information Technology
 * https://github.com/Microsoft/ELL/blob/master/libraries/utilities/include/Exception.h
 *
 *  Created on: Dec 25, 2018
 *  Student (MIG Virtual Developer): Tung Dang
 */
#pragma once

#include <exception>
#include <string>

namespace ell 
{
    namespace utilities
    {
        class Exception : public std::exception
        {
            public:
            Exception(const std::string& message) : 
                _message(message) {}

            ~Exception() override = default;

            virtual const std::string& GetMessage() const {return _message;}
            const char* what() const noexcept override {return GetMessage().c_str();}

            private:
            std::string _message;
        };

        template <typename ErrorCodeType>
        class ErrorCodeException : public Exception
        {
            public:
            ErrorCodeException(ErrorCodeType errorCode, const std::string& message = "");

            ErrorCodeType GetErrorCode() const noexcept {return _errorCode;};

            private: 
            ErrorCodeType _errorCode;
        };

        enum class LogicExceptionErrors
        {
            illegalState,
            notImplemented,
            notInitialized
        };

        enum class SystemExceptionErrors
        {
            fileNotFound,
            fileNotWritable,
            serialPortUnavailable
        };

        enum class NumericExceptionErrors
        {
            divideByZero,
            overflow,
            didNotConverge
        };

        enum class InputExceptionErrors
        {
            badStringFormat,
            badData,
            indexOutOfRange,
            invalidArgument,
            invalidSize,
            nullReference,
            sizeMismatch,
            typeMismatch,
            versionMismatch
        };

        enum class DataFormatErrors
        {
            badFormat,
            illegalValue,
            abruptEnd
        };

        using LogicException = ErrorCodeException<LogicExceptionErrors>;
        using SystemException = ErrorCodeException<SystemExceptionErrors>;
        using NumericException = ErrorCodeException<NumericExceptionErrors>;
        using InputException = ErrorCodeException<InputExceptionErrors>;
        using DataFormatException = ErrorCodeException<DataFormatErrors>;
    }
}

#pragma region implementation 

namespace ell 
{
    namespace utilities
    {
        template <typename ErrorCodeType>
        ErrorCodeException<ErrorCodeType>::ErrorCodeException(ErrorCodeType errorCode, const std::string& message) : 
            Exception(message),
            _errorCode(errorCode)
        {}
    }
}

#pragma endregion implementation
