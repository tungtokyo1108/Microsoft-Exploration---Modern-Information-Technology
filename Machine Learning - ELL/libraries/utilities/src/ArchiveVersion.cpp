/**
 * Microsoft - Modern Information Technology
 * https://github.com/Microsoft/ELL/blob/master/libraries/utilities/src/ArchiveVersion.cpp
 *
 *  Created on: Jan 10, 2019
 *  Student (MIG Virtual Developer): Tung Dang
 */

#include "ArchiveVersion.h"

namespace ell
{
namespace utilities
{
    bool operator==(const ArchiveVersion& a, const ArchiveVersion& b)
    {
        return a.versionNumber == b.versionNumber;
    }

    bool operator!=(const ArchiveVersion& a, const ArchiveVersion& b)
    {
        return !(a == b);
    }

    bool operator>(const ArchiveVersion& a, const ArchiveVersion& b)
    {
        return a.versionNumber > b.versionNumber;
    }

    bool operator>=(const ArchiveVersion& a, const ArchiveVersion& b)
    {
        return a > b || a == b;
    }

    bool operator<(const ArchiveVersion& a, const ArchiveVersion& b)
    {
        return !(a >= b);
    }

    bool operator<=(const ArchiveVersion& a, const ArchiveVersion& b)
    {
        return !(a > b);
    }
} // namespace utilities
} // namespace ell