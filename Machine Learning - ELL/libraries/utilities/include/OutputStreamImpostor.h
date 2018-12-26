/**
 * Microsoft - Modern Information Technology
 * https://github.com/Microsoft/ELL/blob/master/libraries/utilities/include/OutputStreamImpostor.h
 *
 *  Created on: Dec 26, 2018
 *  Student (MIG Virtual Developer): Tung Dang
 */

#include <functional>
#include <memory>
#include <ostream>

namespace ell 
{
    namespace utilities
    {
        class OutputStreamImpostor 
        {
            public: 
            enum class StreamType 
            {
                cout, 
                cerr,
                null 
            };

            OutputStreamImpostor();
            ~OutputStreamImpostor() = default;

            OutputStreamImpostor(const OutputStreamImpostor&) noexcept = default;
            OutputStreamImpostor& operator=(const OutputStreamImpostor&) noexcept = default;

            OutputStreamImpostor(OutputStreamImpostor&&) noexcept = default;
            OutputStreamImpostor& operator=(OutputStreamImpostor&&) noexcept = default;

            /**
             * Constructor that creates an object that directs output to  
             * - a specified stream
             * - a file 
             * - an existing stream 
            */
            OutputStreamImpostor(StreamType streamtype);
            OutputStreamImpostor(const std::string& filename); 
            OutputStreamImpostor(std::ostream& stream);

            /**
             * Casting operator that returns a reference to an ostream. This allows us to use an OutputStreamImposter 
             * in most places where: 
             * - an ostream would be accepted.
             * - a const ostream reference would be accepted. 
            */
            operator std::ostream&() & noexcept {return _outputStream; }
            operator std::ostream const&() const& noexcept {return _outputStream;}

            /* Output operator that sends the given value to the output stream */
            template <typename T>
            std::ostream& operator<<(T&& value);

            /* Return/Sets the current floating-point precision setting for the stream */
            std::streamsize precision() const;
            std::streamsize precision(std::streamsize prec);

            /**
             * Sets the specified format flags for the stream to on
             * Sets or clears the specified flags for the stream, depending on a mask 
            */
            std::ios_base::fmtflags setf(std::ios_base::fmtflags fmtfl);
            std::ios_base::fmtflags setf(std::ios_base::fmtflags fmtfl1, std::ios_base::fmtflags mask);

            private: 
            std::shared_ptr<std::ofstream> _fileStream;
            std::reference_wrapper<std::ostream> _outputStream;

        };
    }
}

#pragma region implementation 
namespace ell 
{
    namespace utilities
    {
        template <typename T>
        std::ostream& OutputStreamImpostor::operator<<(T&& value) 
        {
            _outputStream.get() << value;
            return _outputStream;
        }
    }
}
#pragma endregion implementation