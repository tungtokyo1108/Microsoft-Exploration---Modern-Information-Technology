/**
 * Microsoft - Modern Information Technology
 * https://github.com/Microsoft/ELL/blob/master/libraries/utilities/src/Logger.cpp
 *
 *  Created on: Dec 26, 2018
 *  Student (MIG Virtual Developer): Tung Dang
 */

#include "Logger.h"

#include <fstream>
#include <iostream>

namespace ell 
{
    namespace utilities
    {
        namespace logging
        {
            bool& ShouldFlush()
            {
                static bool shouldFlush = false;
                return shouldFlush;
            }

            bool& ShouldLog()
            {
                static bool shouldLog = false;
                return shouldLog;
            }

            std::ostream& EOL(std::ostream& stream)
            {
                stream << "\n";
                if (ShouldFlush())
                {
                    stream << std::flush;
                }
                return stream;
            }

            OutputStreamImpostor& Log()
            {
                static OutputStreamImpostor nullHandle;
                static OutputStreamImpostor logHandle{std::cout};

                if (ShouldLog())
                {
                    return logHandle;
                }
                else
                {
                    return nullHandle;
                }
            }
        }
    }
}
