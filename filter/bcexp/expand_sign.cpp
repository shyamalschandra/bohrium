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
#include "expander.hpp"

using namespace std;

namespace bohrium {
namespace filter {
namespace composite {

int Expander::expand_sign(bh_ir& bhir, int pc)
{
    int start_pc = pc;
    bh_instruction& composite = bhir.instr_list[pc];
    composite.opcode = BH_NONE; // Lazy choice... no re-use just NOP it.

    bh_view out     = composite.operand[0];         // Grab operands
    bh_view input   = composite.operand[1];

    bh_type input_type = input.base->type;          // Grab the input-type

    bh_view meta = composite.operand[0];            // Inherit ndim and shape
    meta.start = 0;
    bh_intp nelements = 1;                          // Count number of elements
    for(bh_intp dim=meta.ndim-1; dim >= 0; --dim) { // Contiguous stride
        meta.stride[dim] = nelements;
        nelements *= meta.shape[dim];
    }
    if (!((input_type == BH_COMPLEX64) || \
          (input_type == BH_COMPLEX128))) { // For non-complex: sign(x) = (x>0)-(x<0)
                                                            
        bh_view lss     = make_temp(meta, input_type, nelements);// Temps
        bh_view gtr     = make_temp(meta, input_type, nelements);
        bh_view t_bool  = make_temp(meta, BH_BOOL, nelements);  

        inject(bhir, ++pc, BH_GREATER, t_bool, input, 0.0);    // Sequence
        inject(bhir, ++pc, BH_IDENTITY, lss, t_bool);
        inject(bhir, ++pc, BH_FREE, t_bool);
        inject(bhir, ++pc, BH_DISCARD, t_bool);
        
        inject(bhir, ++pc, BH_LESS, t_bool, input, 0.0);       
        inject(bhir, ++pc, BH_IDENTITY, gtr, t_bool);
        inject(bhir, ++pc, BH_FREE, t_bool);
        inject(bhir, ++pc, BH_DISCARD, t_bool);

        inject(bhir, ++pc, BH_SUBTRACT, out, lss, gtr);
        inject(bhir, ++pc, BH_FREE, lss);
        inject(bhir, ++pc, BH_DISCARD, lss);
        inject(bhir, ++pc, BH_FREE, gtr);
        inject(bhir, ++pc, BH_DISCARD, gtr);
    } else {                                // For complex: sign(0) = 0, sign(z) = z/|z|
                                            // General form: sign(z) = z/(|z|+(z==0))
        bh_view z_abs = make_temp(meta, input_type, nelements); // Temps
        bh_view z_zero_bool = make_temp(meta, BH_BOOL, nelements);
        bh_view z_zero = make_temp(meta, input_type, nelements);
        bh_view divisor = make_temp(meta, input_type, nelements);
        
        inject(bhir, ++pc, BH_ABSOLUTE, z_abs, input);          // Sequence
        inject(bhir, ++pc, BH_EQUAL, z_zero_bool, input, 0.0, input_type);
        inject(bhir, ++pc, BH_IDENTITY, z_zero, z_zero_bool);
        inject(bhir, ++pc, BH_FREE, z_zero_bool);
        inject(bhir, ++pc, BH_DISCARD, z_zero_bool);

        inject(bhir, ++pc, BH_ADD, divisor, z_abs, z_zero);
        inject(bhir, ++pc, BH_FREE, z_zero);
        inject(bhir, ++pc, BH_DISCARD, z_zero);
        inject(bhir, ++pc, BH_FREE, z_abs);
        inject(bhir, ++pc, BH_DISCARD, z_abs);

        inject(bhir, ++pc, BH_DIVIDE, out, input, divisor);
        inject(bhir, ++pc, BH_FREE, divisor);
        inject(bhir, ++pc, BH_DISCARD, divisor);
    }

    return pc-start_pc;
}

}}}
