/*
This file is part of Bohrium and copyright (c) 2012 the Bohrium
team <http://www.bh107.org>.

Bohrium is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as
published by the Free Software Foundation, either version 3
of the License, or (at your option) any later version.

Bohrium is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the
GNU Lesser General Public License along with Bohrium.

If not, see <http://www.gnu.org/licenses/>.
*/

#include <vector>

#ifndef __BH_UTIL_H
#define __BH_UTIL_H

namespace bohrium {

// Concatenate two vectors
template <typename T>
std::vector<T> vector_cat(const std::vector<T> &a, const std::vector<T> &b) {
    std::vector<T> ret(a);
    ret.insert(ret.end(), b.begin(), b.end());
    return ret;
}

} // bohrium



#endif
