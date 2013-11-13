/*
This file is part of Bohrium and Copyright (c) 2012 the Bohrium team:
http://bohrium.bitbucket.org

Bohrium is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as 
published by the Free Software Foundation, either version 3 
of the License, or (at your option) any later version.

Bohrium is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the 
GNU Lesser General Public License along with bohrium. 

If not, see <http://www.gnu.org/licenses/>.
*/
#include <iostream>
#include "bh/bh.hpp"

using namespace std;
using namespace bh;

void compute()
{
    cout << "Hello World." << endl;

    multi_array<double> x, y;

    x = random<double>(3,3);
    cout << "RANDOM: " << x << endl;

    x = random_n<double>(3,3);
    cout << "RANDOM: " << x << endl;

    //x = range<double>(1,10,2);
    x = range<double>(1,10,2);
    cout << "RANGE: " << x << endl;

    x = range<double>(10,1,(int64_t)(1-3));
    cout << "RANGE: " << x << endl;
}

int main()
{
    compute();
    return 0;
}

