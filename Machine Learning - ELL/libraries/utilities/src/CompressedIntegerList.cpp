/**
 * Microsoft - Modern Information Technology
 * https://github.com/Microsoft/ELL/blob/master/libraries/utilities/src/CompressedIntegerList.cpp
 *
 *  Created on: Jan 04, 2019
 *  Student (MIG Virtual Developer): Tung Dang
 */

#include "CompressedIntegerList.h"
#include "Exception.h"

#include <cassert>
#include <cstring>
#include <limits>

namespace ell
{
    namespace utilities
    {
        void CompressedIntegerList::Iterator::Next()
        {
            size_t delta;
            _iter += _iter_increment;
            uint8_t first_val = *_iter;

            /**
             * chop off top 2 bits --- they encode the # bytes need for this delta 
             * 00 = 1 byte, 01 = 2 bytes, 10 = 4 bytes, 11 = 8 bytes
            */
            int total_bytes = 1 << ((first_val >> 6) & 0x03);
            assert(total_bytes);
            if (total_bytes == 1)
            {
                delta = first_val;
            }
            else
            {
                /**
                 * Read in the Next bytes
                 * Shift them over to fit the 6 bits of first_val we are using  
                */
                delta = 0;
                std::memcpy(&delta, _iter + 1, total_bytes - 1);
                delta = (delta << 6) | (first_val & 0x3f);
            }
            _iter_increment = total_bytes;
            _value += delta;
        }

        CompressedIntegerList::Iterator::Iterator(const uint8_t* iter, const uint8_t* end) : 
            _iter(iter),
            _end(end),
            _value(0),
            _iter_increment(0) 
        {
            if (IsValid())
            {
                Next();
            }
        }

        CompressedIntegerList::CompressedIntegerList() : 
            _last(std::numeric_limits<size_t>::max()),
            _size(0)
        {}

        size_t CompressedIntegerList::Size() const
        {
            return _size;
        }

        void CompressedIntegerList::Reserve(size_t size)
        {
            _data.reserve(size * 2);
        }

        size_t CompressedIntegerList::Max() const
        {
            if (_size == 0)
            {
                throw utilities::LogicException(utilities::LogicExceptionErrors::illegalState, "Can't get max of empty list");
            }

            return _last;
        }

        void CompressedIntegerList::Append(size_t value) 
        {
            assert(value != std::numeric_limits<size_t>::max());
            /*Calculate the delta from the previous number pushed*/
            size_t delta = 0;
            if (_last < std::numeric_limits<size_t>::max())
            {
                assert(value > _last);
            }
            else
            {
                _last = 0;
            }

            delta = value - _last;
            _last = value;

            /*figure out how many bits we need to represent this value*/
            int log2bytes = 0;
            if ((delta & 0xffffffffffffffc0) == 0)
            {
                log2bytes = 0;
            }
            else if ((delta & 0xffffffffffffc000) == 0)
            {
                log2bytes = 1;
            }
            else if ((delta & 0xffffffffc0000000) == 0)
            {
                log2bytes = 2;
            }
            else
            {
                log2bytes = 3;
            }

            int total_bytes = 1 << log2bytes;
            _data.resize(_data.size() + total_bytes);
            /*Get pointer to correct place in array*/
            uint8_t* buf = _data.data() + _data.size() - total_bytes;
            unsigned int mask = log2bytes << 6;
            size_t write_val = ((delta << 2) & 0xffffffffffffff00) | mask | (delta & 0x3f);
            std::memcpy(buf, &write_val, total_bytes);
            ++_size;
        }

        void CompressedIntegerList::Reset()
        {
            _data.resize(0);
            _last = std::numeric_limits<size_t>::max();
            _size = 0;
        }
    }
}