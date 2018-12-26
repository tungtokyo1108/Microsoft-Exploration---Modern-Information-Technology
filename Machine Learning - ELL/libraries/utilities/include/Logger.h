/**
 * Microsoft - Modern Information Technology
 * https://github.com/Microsoft/ELL/blob/master/libraries/utilities/include/Logger.h
 *
 *  Created on: Dec 26, 2018
 *  Student (MIG Virtual Developer): Tung Dang
 */

#include "OutputStreamImpostor.h"

namespace ell 
{
    namespace utilities
    {
        namespace logging
        {
            /**
             * Inserts a newline character into the output sequence os and 
             * flushes it as if by calling os.put followed by os.flush(), if 
             * ShouldFlush() return true
            */
            std::ostream& EOL(std::ostream& stream);

            bool& ShouldFlush();

            bool& ShouldLog();

            OutputStreamImpostor& Log();
        }
    }
    namespace logging = utilities::logging;
}