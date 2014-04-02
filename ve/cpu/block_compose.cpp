#include "block.hpp"
//
//  NOTE: This file is autogenerated based on the tac-definition.
//        You should therefore not edit it manually.
//
using namespace std;
namespace bohrium{
namespace engine{
namespace cpu{

/**
 *  Compose a block based on the instruction-nodes within a dag.
 */
bool Block::compose()
{
    if (this->dag.nnode<1) {
        fprintf(stderr, "Got an empty dag. This cannot be right...\n");
        return false;
    }
    bool compose_res = compose(0, this->dag.nnode-1);

    return compose_res;
}

/**
 *  Compose a block based on the instruction-nodes within a dag.
 *  Starting from and including node_start to and including node_end.
 */
bool Block::compose(bh_intp node_start, bh_intp node_end)
{
    DEBUG(TAG, "compose("<< node_start <<", "<< node_end << ") : node_span(" << ((node_end-node_start)+1) << ")");
    if (this->dag.nnode<1) {
        fprintf(stderr, "Got an empty dag. This cannot be right...\n");
        return false;
    }
    
    // Reset metadata
    length      = 0; // The length of the block
    noperands   = 0; // The number of operands
    omask       = 0; // And the operation mask
    symbol      = "";
    symbol_text = "";

    size_t pc = 0;
    for (int node_idx=node_start; node_idx<=node_end; ++node_idx, ++pc, ++length) {
        
        if (dag.node_map[node_idx] <0) {
            fprintf(stderr, "Code-generation for subgraphs is not supported yet.\n");
            return false;
        }

        this->instr[pc] = &this->ir.instr_list[dag.node_map[node_idx]];
        bh_instruction& instr = *this->instr[pc];

        uint32_t out=0, in1=0, in2=0;

        //
        // Program packing: output argument
        // NOTE: All but BH_NONE has an output which is an array
        if (instr.opcode != BH_NONE) {
            out = this->add_operand(instr, 0);
        }

        //
        // Program packing; operator, operand and input argument(s).
        switch (instr.opcode) {    // [OPCODE_SWITCH]

            case BH_ABSOLUTE:
                in1 = this->add_operand(instr, 1);

                this->program[pc].op    = MAP;  // TAC
                this->program[pc].oper  = ABSOLUTE;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= MAP;    // Operationmask
                break;
            case BH_ARCCOS:
                in1 = this->add_operand(instr, 1);

                this->program[pc].op    = MAP;  // TAC
                this->program[pc].oper  = ARCCOS;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= MAP;    // Operationmask
                break;
            case BH_ARCCOSH:
                in1 = this->add_operand(instr, 1);

                this->program[pc].op    = MAP;  // TAC
                this->program[pc].oper  = ARCCOSH;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= MAP;    // Operationmask
                break;
            case BH_ARCSIN:
                in1 = this->add_operand(instr, 1);

                this->program[pc].op    = MAP;  // TAC
                this->program[pc].oper  = ARCSIN;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= MAP;    // Operationmask
                break;
            case BH_ARCSINH:
                in1 = this->add_operand(instr, 1);

                this->program[pc].op    = MAP;  // TAC
                this->program[pc].oper  = ARCSINH;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= MAP;    // Operationmask
                break;
            case BH_ARCTAN:
                in1 = this->add_operand(instr, 1);

                this->program[pc].op    = MAP;  // TAC
                this->program[pc].oper  = ARCTAN;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= MAP;    // Operationmask
                break;
            case BH_ARCTANH:
                in1 = this->add_operand(instr, 1);

                this->program[pc].op    = MAP;  // TAC
                this->program[pc].oper  = ARCTANH;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= MAP;    // Operationmask
                break;
            case BH_CEIL:
                in1 = this->add_operand(instr, 1);

                this->program[pc].op    = MAP;  // TAC
                this->program[pc].oper  = CEIL;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= MAP;    // Operationmask
                break;
            case BH_COS:
                in1 = this->add_operand(instr, 1);

                this->program[pc].op    = MAP;  // TAC
                this->program[pc].oper  = COS;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= MAP;    // Operationmask
                break;
            case BH_COSH:
                in1 = this->add_operand(instr, 1);

                this->program[pc].op    = MAP;  // TAC
                this->program[pc].oper  = COSH;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= MAP;    // Operationmask
                break;
            case BH_EXP:
                in1 = this->add_operand(instr, 1);

                this->program[pc].op    = MAP;  // TAC
                this->program[pc].oper  = EXP;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= MAP;    // Operationmask
                break;
            case BH_EXP2:
                in1 = this->add_operand(instr, 1);

                this->program[pc].op    = MAP;  // TAC
                this->program[pc].oper  = EXP2;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= MAP;    // Operationmask
                break;
            case BH_EXPM1:
                in1 = this->add_operand(instr, 1);

                this->program[pc].op    = MAP;  // TAC
                this->program[pc].oper  = EXPM1;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= MAP;    // Operationmask
                break;
            case BH_FLOOR:
                in1 = this->add_operand(instr, 1);

                this->program[pc].op    = MAP;  // TAC
                this->program[pc].oper  = FLOOR;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= MAP;    // Operationmask
                break;
            case BH_IDENTITY:
                in1 = this->add_operand(instr, 1);

                this->program[pc].op    = MAP;  // TAC
                this->program[pc].oper  = IDENTITY;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= MAP;    // Operationmask
                break;
            case BH_IMAG:
                in1 = this->add_operand(instr, 1);

                this->program[pc].op    = MAP;  // TAC
                this->program[pc].oper  = IMAG;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= MAP;    // Operationmask
                break;
            case BH_INVERT:
                in1 = this->add_operand(instr, 1);

                this->program[pc].op    = MAP;  // TAC
                this->program[pc].oper  = INVERT;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= MAP;    // Operationmask
                break;
            case BH_ISINF:
                in1 = this->add_operand(instr, 1);

                this->program[pc].op    = MAP;  // TAC
                this->program[pc].oper  = ISINF;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= MAP;    // Operationmask
                break;
            case BH_ISNAN:
                in1 = this->add_operand(instr, 1);

                this->program[pc].op    = MAP;  // TAC
                this->program[pc].oper  = ISNAN;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= MAP;    // Operationmask
                break;
            case BH_LOG:
                in1 = this->add_operand(instr, 1);

                this->program[pc].op    = MAP;  // TAC
                this->program[pc].oper  = LOG;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= MAP;    // Operationmask
                break;
            case BH_LOG10:
                in1 = this->add_operand(instr, 1);

                this->program[pc].op    = MAP;  // TAC
                this->program[pc].oper  = LOG10;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= MAP;    // Operationmask
                break;
            case BH_LOG1P:
                in1 = this->add_operand(instr, 1);

                this->program[pc].op    = MAP;  // TAC
                this->program[pc].oper  = LOG1P;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= MAP;    // Operationmask
                break;
            case BH_LOG2:
                in1 = this->add_operand(instr, 1);

                this->program[pc].op    = MAP;  // TAC
                this->program[pc].oper  = LOG2;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= MAP;    // Operationmask
                break;
            case BH_LOGICAL_NOT:
                in1 = this->add_operand(instr, 1);

                this->program[pc].op    = MAP;  // TAC
                this->program[pc].oper  = LOGICAL_NOT;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= MAP;    // Operationmask
                break;
            case BH_REAL:
                in1 = this->add_operand(instr, 1);

                this->program[pc].op    = MAP;  // TAC
                this->program[pc].oper  = REAL;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= MAP;    // Operationmask
                break;
            case BH_RINT:
                in1 = this->add_operand(instr, 1);

                this->program[pc].op    = MAP;  // TAC
                this->program[pc].oper  = RINT;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= MAP;    // Operationmask
                break;
            case BH_SIN:
                in1 = this->add_operand(instr, 1);

                this->program[pc].op    = MAP;  // TAC
                this->program[pc].oper  = SIN;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= MAP;    // Operationmask
                break;
            case BH_SINH:
                in1 = this->add_operand(instr, 1);

                this->program[pc].op    = MAP;  // TAC
                this->program[pc].oper  = SINH;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= MAP;    // Operationmask
                break;
            case BH_SQRT:
                in1 = this->add_operand(instr, 1);

                this->program[pc].op    = MAP;  // TAC
                this->program[pc].oper  = SQRT;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= MAP;    // Operationmask
                break;
            case BH_TAN:
                in1 = this->add_operand(instr, 1);

                this->program[pc].op    = MAP;  // TAC
                this->program[pc].oper  = TAN;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= MAP;    // Operationmask
                break;
            case BH_TANH:
                in1 = this->add_operand(instr, 1);

                this->program[pc].op    = MAP;  // TAC
                this->program[pc].oper  = TANH;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= MAP;    // Operationmask
                break;
            case BH_TRUNC:
                in1 = this->add_operand(instr, 1);

                this->program[pc].op    = MAP;  // TAC
                this->program[pc].oper  = TRUNC;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= MAP;    // Operationmask
                break;
            case BH_ADD:
                in1 = this->add_operand(instr, 1);
                in2 = this->add_operand(instr, 2);

                this->program[pc].op    = ZIP;  // TAC
                this->program[pc].oper  = ADD;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= ZIP;    // Operationmask
                break;
            case BH_ARCTAN2:
                in1 = this->add_operand(instr, 1);
                in2 = this->add_operand(instr, 2);

                this->program[pc].op    = ZIP;  // TAC
                this->program[pc].oper  = ARCTAN2;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= ZIP;    // Operationmask
                break;
            case BH_BITWISE_AND:
                in1 = this->add_operand(instr, 1);
                in2 = this->add_operand(instr, 2);

                this->program[pc].op    = ZIP;  // TAC
                this->program[pc].oper  = BITWISE_AND;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= ZIP;    // Operationmask
                break;
            case BH_BITWISE_OR:
                in1 = this->add_operand(instr, 1);
                in2 = this->add_operand(instr, 2);

                this->program[pc].op    = ZIP;  // TAC
                this->program[pc].oper  = BITWISE_OR;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= ZIP;    // Operationmask
                break;
            case BH_BITWISE_XOR:
                in1 = this->add_operand(instr, 1);
                in2 = this->add_operand(instr, 2);

                this->program[pc].op    = ZIP;  // TAC
                this->program[pc].oper  = BITWISE_XOR;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= ZIP;    // Operationmask
                break;
            case BH_DIVIDE:
                in1 = this->add_operand(instr, 1);
                in2 = this->add_operand(instr, 2);

                this->program[pc].op    = ZIP;  // TAC
                this->program[pc].oper  = DIVIDE;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= ZIP;    // Operationmask
                break;
            case BH_EQUAL:
                in1 = this->add_operand(instr, 1);
                in2 = this->add_operand(instr, 2);

                this->program[pc].op    = ZIP;  // TAC
                this->program[pc].oper  = EQUAL;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= ZIP;    // Operationmask
                break;
            case BH_GREATER:
                in1 = this->add_operand(instr, 1);
                in2 = this->add_operand(instr, 2);

                this->program[pc].op    = ZIP;  // TAC
                this->program[pc].oper  = GREATER;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= ZIP;    // Operationmask
                break;
            case BH_GREATER_EQUAL:
                in1 = this->add_operand(instr, 1);
                in2 = this->add_operand(instr, 2);

                this->program[pc].op    = ZIP;  // TAC
                this->program[pc].oper  = GREATER_EQUAL;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= ZIP;    // Operationmask
                break;
            case BH_LEFT_SHIFT:
                in1 = this->add_operand(instr, 1);
                in2 = this->add_operand(instr, 2);

                this->program[pc].op    = ZIP;  // TAC
                this->program[pc].oper  = LEFT_SHIFT;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= ZIP;    // Operationmask
                break;
            case BH_LESS:
                in1 = this->add_operand(instr, 1);
                in2 = this->add_operand(instr, 2);

                this->program[pc].op    = ZIP;  // TAC
                this->program[pc].oper  = LESS;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= ZIP;    // Operationmask
                break;
            case BH_LESS_EQUAL:
                in1 = this->add_operand(instr, 1);
                in2 = this->add_operand(instr, 2);

                this->program[pc].op    = ZIP;  // TAC
                this->program[pc].oper  = LESS_EQUAL;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= ZIP;    // Operationmask
                break;
            case BH_LOGICAL_AND:
                in1 = this->add_operand(instr, 1);
                in2 = this->add_operand(instr, 2);

                this->program[pc].op    = ZIP;  // TAC
                this->program[pc].oper  = LOGICAL_AND;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= ZIP;    // Operationmask
                break;
            case BH_LOGICAL_OR:
                in1 = this->add_operand(instr, 1);
                in2 = this->add_operand(instr, 2);

                this->program[pc].op    = ZIP;  // TAC
                this->program[pc].oper  = LOGICAL_OR;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= ZIP;    // Operationmask
                break;
            case BH_LOGICAL_XOR:
                in1 = this->add_operand(instr, 1);
                in2 = this->add_operand(instr, 2);

                this->program[pc].op    = ZIP;  // TAC
                this->program[pc].oper  = LOGICAL_XOR;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= ZIP;    // Operationmask
                break;
            case BH_MAXIMUM:
                in1 = this->add_operand(instr, 1);
                in2 = this->add_operand(instr, 2);

                this->program[pc].op    = ZIP;  // TAC
                this->program[pc].oper  = MAXIMUM;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= ZIP;    // Operationmask
                break;
            case BH_MINIMUM:
                in1 = this->add_operand(instr, 1);
                in2 = this->add_operand(instr, 2);

                this->program[pc].op    = ZIP;  // TAC
                this->program[pc].oper  = MINIMUM;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= ZIP;    // Operationmask
                break;
            case BH_MOD:
                in1 = this->add_operand(instr, 1);
                in2 = this->add_operand(instr, 2);

                this->program[pc].op    = ZIP;  // TAC
                this->program[pc].oper  = MOD;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= ZIP;    // Operationmask
                break;
            case BH_MULTIPLY:
                in1 = this->add_operand(instr, 1);
                in2 = this->add_operand(instr, 2);

                this->program[pc].op    = ZIP;  // TAC
                this->program[pc].oper  = MULTIPLY;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= ZIP;    // Operationmask
                break;
            case BH_NOT_EQUAL:
                in1 = this->add_operand(instr, 1);
                in2 = this->add_operand(instr, 2);

                this->program[pc].op    = ZIP;  // TAC
                this->program[pc].oper  = NOT_EQUAL;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= ZIP;    // Operationmask
                break;
            case BH_POWER:
                in1 = this->add_operand(instr, 1);
                in2 = this->add_operand(instr, 2);

                this->program[pc].op    = ZIP;  // TAC
                this->program[pc].oper  = POWER;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= ZIP;    // Operationmask
                break;
            case BH_RIGHT_SHIFT:
                in1 = this->add_operand(instr, 1);
                in2 = this->add_operand(instr, 2);

                this->program[pc].op    = ZIP;  // TAC
                this->program[pc].oper  = RIGHT_SHIFT;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= ZIP;    // Operationmask
                break;
            case BH_SUBTRACT:
                in1 = this->add_operand(instr, 1);
                in2 = this->add_operand(instr, 2);

                this->program[pc].op    = ZIP;  // TAC
                this->program[pc].oper  = SUBTRACT;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= ZIP;    // Operationmask
                break;
            case BH_ADD_REDUCE:
                in1 = this->add_operand(instr, 1);
                in2 = this->add_operand(instr, 2);

                this->program[pc].op    = REDUCE;  // TAC
                this->program[pc].oper  = ADD;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= REDUCE;    // Operationmask
                break;
            case BH_BITWISE_AND_REDUCE:
                in1 = this->add_operand(instr, 1);
                in2 = this->add_operand(instr, 2);

                this->program[pc].op    = REDUCE;  // TAC
                this->program[pc].oper  = BITWISE_AND;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= REDUCE;    // Operationmask
                break;
            case BH_BITWISE_OR_REDUCE:
                in1 = this->add_operand(instr, 1);
                in2 = this->add_operand(instr, 2);

                this->program[pc].op    = REDUCE;  // TAC
                this->program[pc].oper  = BITWISE_OR;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= REDUCE;    // Operationmask
                break;
            case BH_BITWISE_XOR_REDUCE:
                in1 = this->add_operand(instr, 1);
                in2 = this->add_operand(instr, 2);

                this->program[pc].op    = REDUCE;  // TAC
                this->program[pc].oper  = BITWISE_XOR;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= REDUCE;    // Operationmask
                break;
            case BH_LOGICAL_AND_REDUCE:
                in1 = this->add_operand(instr, 1);
                in2 = this->add_operand(instr, 2);

                this->program[pc].op    = REDUCE;  // TAC
                this->program[pc].oper  = LOGICAL_AND;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= REDUCE;    // Operationmask
                break;
            case BH_LOGICAL_OR_REDUCE:
                in1 = this->add_operand(instr, 1);
                in2 = this->add_operand(instr, 2);

                this->program[pc].op    = REDUCE;  // TAC
                this->program[pc].oper  = LOGICAL_OR;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= REDUCE;    // Operationmask
                break;
            case BH_LOGICAL_XOR_REDUCE:
                in1 = this->add_operand(instr, 1);
                in2 = this->add_operand(instr, 2);

                this->program[pc].op    = REDUCE;  // TAC
                this->program[pc].oper  = LOGICAL_XOR;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= REDUCE;    // Operationmask
                break;
            case BH_MAXIMUM_REDUCE:
                in1 = this->add_operand(instr, 1);
                in2 = this->add_operand(instr, 2);

                this->program[pc].op    = REDUCE;  // TAC
                this->program[pc].oper  = MAXIMUM;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= REDUCE;    // Operationmask
                break;
            case BH_MINIMUM_REDUCE:
                in1 = this->add_operand(instr, 1);
                in2 = this->add_operand(instr, 2);

                this->program[pc].op    = REDUCE;  // TAC
                this->program[pc].oper  = MINIMUM;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= REDUCE;    // Operationmask
                break;
            case BH_MULTIPLY_REDUCE:
                in1 = this->add_operand(instr, 1);
                in2 = this->add_operand(instr, 2);

                this->program[pc].op    = REDUCE;  // TAC
                this->program[pc].oper  = MULTIPLY;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= REDUCE;    // Operationmask
                break;
            case BH_ADD_ACCUMULATE:
                in1 = this->add_operand(instr, 1);
                in2 = this->add_operand(instr, 2);

                this->program[pc].op    = SCAN;  // TAC
                this->program[pc].oper  = ADD;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= SCAN;    // Operationmask
                break;
            case BH_MULTIPLY_ACCUMULATE:
                in1 = this->add_operand(instr, 1);
                in2 = this->add_operand(instr, 2);

                this->program[pc].op    = SCAN;  // TAC
                this->program[pc].oper  = MULTIPLY;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= SCAN;    // Operationmask
                break;
            case BH_RANDOM:
                in1 = this->add_operand(instr, 1);

                this->program[pc].op    = GENERATE;  // TAC
                this->program[pc].oper  = RANDOM;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= GENERATE;    // Operationmask
                break;
            case BH_RANGE:

                this->program[pc].op    = GENERATE;  // TAC
                this->program[pc].oper  = RANGE;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= GENERATE;    // Operationmask
                break;
            case BH_DISCARD:

                this->program[pc].op    = SYSTEM;  // TAC
                this->program[pc].oper  = DISCARD;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= SYSTEM;    // Operationmask
                break;
            case BH_FREE:

                this->program[pc].op    = SYSTEM;  // TAC
                this->program[pc].oper  = FREE;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= SYSTEM;    // Operationmask
                break;
            case BH_NONE:

                this->program[pc].op    = SYSTEM;  // TAC
                this->program[pc].oper  = NONE;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= SYSTEM;    // Operationmask
                break;
            case BH_SYNC:

                this->program[pc].op    = SYSTEM;  // TAC
                this->program[pc].oper  = SYNC;
                this->program[pc].out   = out;
                this->program[pc].in1   = in1;
                this->program[pc].in2   = in2;
            
                this->omask |= SYSTEM;    // Operationmask
                break;

            default:
                if (instr.opcode>=BH_MAX_OPCODE_ID) {   // Handle extensions here

                    in1 = this->add_operand(instr, 1);
                    in2 = this->add_operand(instr, 2);

                    this->program[pc].op   = EXTENSION;
                    this->program[pc].oper = EXTENSION_OPERATOR;
                    this->program[pc].out  = out;
                    this->program[pc].in1  = in1;
                    this->program[pc].in2  = in2;

                    this->omask |= EXTENSION;
                    break;

                } else {
                    fprintf(stderr, "Block::compose: Err=[Unsupported instruction] {\n");
                    bh_pprint_instr(&instr);
                    fprintf(stderr, "}\n");
                    return false;
                }
        }
    }
    DEBUG(TAG, "compose(SUCCESS)");
    return true;
}

}}}
