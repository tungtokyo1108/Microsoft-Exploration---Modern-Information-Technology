/**
 * Microsoft - Modern Information Technology
 * https://github.com/Microsoft/ELL/blob/master/libraries/testing/include/testing.h
 *
 *  Created on: Dec 26, 2018
 *  Student (MIG Virtual Developer): Tung Dang
 */

#include <stdexcept>
#include <string>
#include <vector>

namespace ell 
{
    namespace testing 
    {
        class TestFailureException : public std::runtime_error 
        {
            public: 
            /* A description of the test failure that caused the exception */
            TestFailureException(const std::string& testDescription);
        };

        class TestNotImplementedException : public std::runtime_error
        {
            public: 
            TestNotImplementedException(const std::string& testDescription);
        };

        inline bool IsTrue(bool a)
        {
            return a;
        }

        inline bool IsFalse(bool a)
        {
            return !a;
        }

        template <typename T1, typename T2>
        inline std::enable_if_t<!std::is_floating_point<T1>::value && !std::is_floating_point<T2>::value, bool>
        IsEqual(T1 t1, T2 t2) 
        {
            return t1 == t2;
        }

        template <
            typename T1,
            typename T2,
            typename T3 = std::conditional_t<sizeof(T1) >= sizeof(T2), T1, T2>>
        inline std::enable_if_t<std::is_floating_point<T1>::value && std::is_floating_point<T2>::value, bool>
        // IsEqual(T1 a, T2 b, T3 tolerance = std::is_same_v<float, T3> ? 1.0e-6f : 1.0e-8)
        IsEqual(T1 a, T2 b, T3 tolerance = std::is_same<float, T3>::value)
        {
            return (a - b < tolerance && b - a < tolerance);
        }

        bool IsEqual(const std::vector<bool>& a, const std::vector<bool>& b);
        bool IsEqual(const std::vector<int>& a, const std::vector<int>& b);
        bool IsEqual(const std::vector<int64_t>& a, const std::vector<int64_t>& b);

        bool IsEqual(const std::vector<float>& a, const std::vector<float>& b, float tolerance = 1.0e-8);
        bool IsEqual(const std::vector<double>& a, const std::vector<double>& b, float tolerance = 1.0e-8);
        template <typename ValueType1, typename ValueType2>
        bool IsEqual(const std::vector<std::vector<ValueType1>>& a, const std::vector<std::vector<ValueType2>>& b, double tolerance = 1.0e-8);
        bool IsEqual(const std::vector<bool>& a, const std::vector<bool>& b);
        bool IsEqual(const std::vector<std::string>& a, const std::vector<std::string>& b);

        bool ProcessTest(const std::string& testDescription, bool success);
        bool ProcessQuietTest(const std::string& testDescription, bool success);
        void ProcessCriticalTest(const std::string& testDescription, bool success);

        void TestFailed(const std::string& message);
        void TestSucceeded(const std::string& message);
        bool DidTestFail();
        int GetExitCode();

        template <typename FunctionType, typename... Args>
        bool FailOnException(FunctionType& function, Args&&... args)
        {
            using namespace std::literals::string_literals;
            try 
            {
                function(std::forward<Args>(args)...);
                return true;
            }
            catch (const std::exception& exception)
            {
                TestFailed("Got exception in test:"s + exception.what());
            }
            catch (...)
            {
                TestFailed("Got unknown exception type in test");
            }
            return false;
        }

        struct EnableLoggingHelper
        {
            EnableLoggingHelper();
            ~EnableLoggingHelper();

            EnableLoggingHelper(const EnableLoggingHelper&) = delete;
            EnableLoggingHelper(EnableLoggingHelper&&) = delete;
            EnableLoggingHelper& operator=(const EnableLoggingHelper&) = delete;
            EnableLoggingHelper& operator=(EnableLoggingHelper&&) = delete;
        };
    }
}

#if defined(_WIN32)
#if defined(_WIN64)
#define TESTING_FORCE_DEFINE_SYMBOL(x, returnType, ...) __pragma(comment(linker, "/export:" #x))
#else
#define TESTING_FORCE_DEFINE_SYMBOL(x, returnType, ...) __pragma(comment(linker, "/export:_" #x))
#endif
#else
#define TESTING_FORCE_DEFINE_SYMBOL(x, returnType, ...) returnType (*__##x##_fp)(__VA_ARGS__) = &x;
#endif
