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
#include <iostream>
#include <functional>
#include <algorithm>
#include <sstream>
#include <cassert>
#include <stdexcept>
#include <bh.h>
#include "InstructionBatch.hpp"
#include "GenerateSourceCode.hpp"

InstructionBatch::KernelMap InstructionBatch::kernelMap = InstructionBatch::KernelMap();

InstructionBatch::InstructionBatch(bh_instruction* inst, const std::vector<KernelParameter*>& operands)
    : arraynum(0)
    , scalarnum(0)
    , float16(false)
    , float64(false)
    , complex(false)
{
#ifdef STATS
    gettimeofday(&createTime,NULL);
#endif
    if (inst->operand[0].ndim > 3)
        throw std::runtime_error("More than 3 dimensions not supported.");        
    shape = std::vector<bh_index>(inst->operand[0].shape, inst->operand[0].shape + inst->operand[0].ndim);
    add(inst, operands);
}

bool InstructionBatch::shapeMatch(bh_intp ndim,const bh_index dims[])
{
    int size = shape.size();
    if (ndim == size)
    {
        for (int i = 0; i < ndim; ++i)
        {
            if (dims[i] != shape[i])
                return false;
        }
        return true;
    }
    return false;
}

bool InstructionBatch::sameView(const bh_view& a, const bh_view& b)
{
    //assumes the the views shape are the same and they have the same base
    if (a.start != b.start)
        return false;
    for (size_t i = 0; i < shape.size(); ++i)
    {
        if (a.stride[i] != b.stride[i])
            return false;
    }
    return true;
}

inline int gcd(int a, int b)
{
    int c = a % b;
    while(c != 0)
    {
        a = b;
        b = c;
        c = a % b;
    }
    return b;
}

bool InstructionBatch::disjointView(const bh_view& a, const bh_view& b)
{
    //assumes the the views shape are the same and they have the same base
    int astart = a.start;
    int bstart = b.start;
    int stride = 1;
    for (int i = 0; i < a.ndim; ++i)
    {
        stride = gcd(a.stride[i], b.stride[i]);
        int as = astart / stride;
        int bs = bstart / stride;
        int ae = as + a.shape[i] * (a.stride[i]/stride);
        int be = bs + b.shape[i] * (b.stride[i]/stride);
        if (ae <= bs || be <= as)
            return true;
        astart %= stride;
        bstart %= stride;
    }
    if (stride > 1 && a.start % stride != b.start % stride)
        return true;
    return false;
}

void InstructionBatch::add(bh_instruction* inst, const std::vector<KernelParameter*>& operands)
{
    assert(!isScalar(operands[0]));

    // Check that the shape matches
    if (!shapeMatch(inst->operand[0].ndim, inst->operand[0].shape))
        throw BatchException(0);

    std::vector<int> opids(operands.size(),-1);
    for (size_t op = 0; op < operands.size(); ++op)
    {
        BaseArray* ba = dynamic_cast<BaseArray*>(operands[op]);
        if (ba) // not a scalar
        {
            // If any operand's base is already used as output, it has to be alligned or disjoint
            ArrayRange orange = output.equal_range(ba);
            for (ArrayMap::iterator oit = orange.first ; oit != orange.second; ++oit)
            {
                if (sameView(views[oit->second], inst->operand[op]))
                {
                    // Same view so we use the same bh_array* for it
                    opids[op] = oit->second;
                } 
                else if (!disjointView(views[oit->second], inst->operand[op])) 
                { 
                    throw BatchException(0);
                }
            }
            // If the output operans is allready used as input it has to be alligned or disjoint
            ArrayRange irange = input.equal_range(ba);
            for (ArrayMap::iterator iit = irange.first ; iit != irange.second; ++iit)
            {
                if (sameView(views[iit->second], inst->operand[op]))
                {
                    // Same view so we use the same bh_array* for it
                    opids[op] =  iit->second;
                } 
                else if (op == 0 && !disjointView(views[iit->second], inst->operand[0]))
                {
                    throw BatchException(0);
                }
            }
        }
    }


    // OK so we can accept the instruction
    // Register unknow parameters
    for (size_t op = 0; op < operands.size(); ++op)
    {
        if (opids[op]<0)
        {
            KernelParameter* kp = operands[op];
            BaseArray* ba = dynamic_cast<BaseArray*>(kp);
            if (ba)
            {
                if (op == 2 && inst->operand[1].base == inst->operand[2].base && 
                    sameView(inst->operand[1], inst->operand[2]))
                {    //catch when same input is used twice and don't allready have en id
                    opids[2] = opids[1];
                    continue;
                } else {
                    opids[op] = views.size();
                    views.push_back(inst->operand[op]);
                }
                if (op == 0)
                {
                    output.insert(std::make_pair(ba, opids[op]));
                }
                else
                {
                    input.insert(std::make_pair(ba, opids[op]));
                }
                if (parameters.find(kp) == parameters.end())
                {
                    std::stringstream ss;
                    ss << "a" << arraynum++;
                    parameters[kp] = ss.str();
                }
            }
            else //scalar
            {
                std::stringstream ss;
                ss << "s" << scalarnum++;
                opids[op] = SCALAR_OFFSET+scalarnum;
                kernelVariables[opids[op]] = ss.str();
                parameters[kp] = ss.str();
            }
            switch (kp->type())
            {
            case OCL_FLOAT16:
                float16 = true;
                break;
            case OCL_FLOAT64:
                float64 = true;
                break;
            case OCL_COMPLEX64:
                complex = true;
                break;
            case OCL_COMPLEX128:
                float64 = true;
                complex = true;
                break;
            default:
                break;
            }
        }
    }
    instructions.push_back(make_pair(inst, opids));

}

Kernel InstructionBatch::generateKernel(ResourceManager* resourceManager)
{
#ifdef STATS
    timeval start, end;
    gettimeofday(&start,NULL);
#endif
    std::string code = generateCode();
#ifdef STATS
    gettimeofday(&end,NULL);
    resourceManager->batchSource += (end.tv_sec - start.tv_sec)*1000000.0 + (end.tv_usec - start.tv_usec);
#endif
    size_t codeHash = string_hasher(code);

    KernelMap::iterator kit = kernelMap.find(codeHash);
    if (kit == kernelMap.end())
    {
        std::stringstream source, kname;
        kname << "kernel" << std::hex << codeHash;
        if (float16)
        {
            source << "#pragma OPENCL EXTENSION cl_khr_fp16 : enable\n";
        }
        if (float64)
        {
            source << "#pragma OPENCL EXTENSION cl_khr_fp64 : enable\n";
        }
        if (complex)
        {
            source << "#include <complex.h>\n";
        }
        source << "__kernel void " << kname.str() << code;
        Kernel kernel(resourceManager, shape.size(), source.str(), kname.str());
        kernelMap.insert(std::make_pair(codeHash, kernel));
        return kernel;
    } else {
        return kit->second;
    }
}

void InstructionBatch::run(ResourceManager* resourceManager)
{
#ifdef STATS
    timeval now;
    gettimeofday(&now,NULL);
    resourceManager->batchBuild += (now.tv_sec - createTime.tv_sec)*1000000.0 + (now.tv_usec - createTime.tv_usec);
#endif

    if (output.begin() != output.end())
    {
        for (ParameterMap::iterator pit = parameters.begin(); pit != parameters.end(); ++pit)
            parameterList.insert(std::make_pair(pit->second, pit->first));
        for (ArrayMap::iterator iit = input.begin(); iit != input.end(); ++iit)
            inputList.insert(std::make_pair(iit->second, iit->first));
        for (ArrayMap::iterator oit = output.begin(); oit != output.end(); ++oit)
            outputList.insert(std::make_pair(oit->second, oit->first));
        Kernel kernel = generateKernel(resourceManager);
        Kernel::Parameters kernelParameters;
        for (ParameterList::iterator pit = parameterList.begin(); pit != parameterList.end(); ++pit)
        {
            if (output.find(static_cast<BaseArray*>(pit->second)) == output.end())
                kernelParameters.push_back(std::make_pair(pit->second, false));
            else
                kernelParameters.push_back(std::make_pair(pit->second, true));
        }
        std::vector<size_t> globalShape;
        for (int i = shape.size()-1; i>=0; --i)
            globalShape.push_back(shape[i]);
        kernel.call(kernelParameters, globalShape);
    }
}

std::string InstructionBatch::generateCode()
{
    std::stringstream source;
    source << "( ";
    // Add Array kernel parameters
    ParameterList::iterator pit = parameterList.begin();
    source << *(pit->second) << " " << pit->first;
    for (++pit; pit != parameterList.end(); ++pit)
    {
        source << "\n                     , " << *(pit->second) << " " << pit->first;
    }

    source << ")\n{\n";
    
    generateGIDSource(shape, source);
    
    // Load input parameters
    for (ArrayList::iterator iit = inputList.begin(); iit != inputList.end(); ++iit)
    {
        std::stringstream ss;
        ss << "v" << iit->first;
        kernelVariables[iit->first] = ss.str();
        source << "\t" << oclTypeStr(iit->second->type()) << " " << ss.str() << " = " <<
            parameters[iit->second] << "[";
        generateOffsetSource(views[iit->first], source);
        source << "];\n";
    }

    // Generate code for instructions
    for (InstructionList::iterator iit = instructions.begin(); iit != instructions.end(); ++iit)
    {
        std::vector<std::string> operands;
        // Has the output operand been assigned a variable name?
        VariableMap::iterator kvit = kernelVariables.find(iit->second[0]);
        if (kvit == kernelVariables.end())
        {
            std::stringstream ss;
            ss << "v" << iit->second[0];
            kernelVariables[(iit->second)[0]] = ss.str();
            operands.push_back(ss.str());
            source << "\t" << oclTypeStr(oclType(iit->first->operand[0].base->type)) << " " << ss.str() << ";\n";
        }
        else
        {
            operands.push_back(kvit->second);
        }
        // find variable names for input operands
        for (int op = 1; op < bh_operands(iit->first->opcode); ++op)
        {
            operands.push_back(kernelVariables[iit->second[op]]);  
        }
        // generate source code for the instruction
        generateInstructionSource(iit->first->opcode, 
                                  std::make_pair(oclType(iit->first->operand[0].base->type),
                                                 oclType(iit->first->operand[1].base ? 
                                                         iit->first->operand[1].base->type : 
                                                         iit->first->constant.type)), 
                                  operands, source);
    }

    // Save output parameters
    for (ArrayList::iterator oit = outputList.begin(); oit != outputList.end(); ++oit)
    {
        source << "\t" << parameters[oit->second] << "[";
        generateOffsetSource(views[oit->first], source);
        source << "] = " <<  kernelVariables[oit->first] << ";\n";
    }

    source << "}\n";
    return source.str();
}

bool InstructionBatch::read(BaseArray* array)
{
    if (input.find(array) == input.end())
        return false;
    return true;
}

bool InstructionBatch::write(BaseArray* array)
{
    if (output.find(array) == output.end())
        return false;
    return true;
}

bool InstructionBatch::access(BaseArray* array)
{
    return (read(array) || write(array));
}

bool InstructionBatch::discard(BaseArray* array)
{
    output.erase(array);
    bool r =  read(array);
    if (!r)
    {
        parameters.erase(static_cast<KernelParameter*>(array));
    }
    return !r;
}
