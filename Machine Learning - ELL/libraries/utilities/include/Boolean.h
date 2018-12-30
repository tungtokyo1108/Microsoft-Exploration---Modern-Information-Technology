/**
 * Microsoft - Modern Information Technology
 * https://github.com/Microsoft/ELL/blob/master/libraries/utilities/include/Boolean.h
 *
 *  Created on: Dec 30, 2018
 *  Student (MIG Virtual Developer): Tung Dang
 */

#include <type_traits>

namespace ell
{
    
    namespace utilities
    {
        /* A simple wrapper around bool to work around the std::vector<bool> specialization */
        struct Boolean
        {
            Boolean();
            Boolean(bool value);
            operator bool() const {return value;}

            private:
            bool value = false;
        };

        /*static_assert(std::is_default_constructible<Boolean> &&
                      std::is_nothrow_move_assignable_v<Boolean> &&
                      std::is_nothrow_move_constructible_v<Boolean> &&
                      std::is_swappable_v<Boolean>);*/

        bool operator==(Boolean b1, Boolean b2);
        bool operator!=(Boolean b1, Boolean b2);
    } // utilities
    
}