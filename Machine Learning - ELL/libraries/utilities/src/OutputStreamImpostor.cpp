/**
 * Microsoft - Modern Information Technology
 * https://github.com/Microsoft/ELL/blob/master/libraries/utilities/src/OutputStreamImpostor.cpp
 *
 *  Created on: Dec 26, 2018
 *  Student (MIG Virtual Developer): Tung Dang
 */

#include "OutputStreamImpostor.h"
#include "Files.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>

namespace ell 
{
    namespace utilities 
    {
        static std::ofstream nullStreamBuf;

        OutputStreamImpostor::OutputStreamImpostor() : 
            _outputStream(nullStreamBuf) 
        {}

        OutputStreamImpostor::OutputStreamImpostor(StreamType streamType) : 
            OutputStreamImpostor()
        {
            switch(streamType)
            {
                case StreamType::cout: 
                    _outputStream = std::cout;
                    break;
                case StreamType::cerr:
                    _outputStream = std::cerr;
                    break;
                default: 
                    break;
            }
        }

        OutputStreamImpostor::OutputStreamImpostor(std::ostream& stream) : 
            _outputStream(stream) 
        {}

        OutputStreamImpostor::OutputStreamImpostor(const std::string& filename) :
            _fileStream(std::make_shared<std::ofstream>(OpenOfstream(filename))), 
            _outputStream(*_fileStream)
        {}

        std::streamsize OutputStreamImpostor::precision(std::streamsize prec)
        {
            return _outputStream.get().precision(prec);
        }

        std::streamsize OutputStreamImpostor::precision() const 
        {
            return _outputStream.get().precision();
        }

        std::ios_base::fmtflags OutputStreamImpostor::setf(std::ios_base::fmtflags fmtfl)
        {
            return _outputStream.get().setf(fmtfl);
        }


    }
}