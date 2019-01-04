/**
 * Microsoft - Modern Information Technology
 * https://github.com/Microsoft/ELL/blob/master/libraries/utilities/include/CompressedIntegerList.h
 *
 *  Created on: Jan 04, 2019
 *  Student (MIG Virtual Developer): Tung Dang
 */

#include <cstddef>
#include <cstdint>
#include <vector>

namespace ell 
{
    namespace utilities 
    {
        /**
         * A non-decreasing list of nonnegative integers, with a forward Iterator, 
         * stored in a compressed delta enconding
        */
        class CompressedIntegerList 
        {
            public:
            class Iterator 
            {
                public: 
                Iterator() = default;
                Iterator(const Iterator&) = default;
                Iterator(Iterator&&) = default;

                // Query if this object input stream valid
                bool IsValid() const {return _iter < _end;}
                void Next();
                size_t Get() const {return _value;}

                private: 
                Iterator(const uint8_t* iter, const uint8_t* end);
                friend class CompressedIntegerList;

                const uint8_t* _iter;
                const uint8_t* _end;
                size_t _value;
                size_t _iter_increment;
            };

            CompressedIntegerList();
            CompressedIntegerList(CompressedIntegerList&& other) = default;
            CompressedIntegerList(const CompressedIntegerList&) = default;
            ~CompressedIntegerList() = default;

            void operator=(const CompressedIntegerList&) = delete;

            size_t Size() const;
            void Reserve(size_t size);
            size_t Max() const;
            void Append(size_t value);
            void Reset();
            Iterator GetIterator() const {return Iterator(_data.data(), _data.data() + _data.size());}

            private:
            std::vector<uint8_t> _data;
            size_t _last;
            size_t _size;

        };
    }
}