/*
    Copyright 2016-2017 StapleButter

    This file is part of melonDS.

    melonDS is free software: you can redistribute it and/or modify it under
    the terms of the GNU General Public License as published by the Free
    Software Foundation, either version 3 of the License, or (at your option)
    any later version.

    melonDS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with melonDS. If not, see http://www.gnu.org/licenses/.
*/

#ifdef __WIN32__
    #include <windows.h>
#else
    // TODO!!
#endif

#include <stdio.h>
#include "NDS.h"
#include "CP15.h"
#include "ARMJIT.h"
#include "ARMJIT_ALU.h"
#include "ARMJIT_Branch.h"
#include "ARMJIT_LoadStore.h"


namespace ARMJIT
{


const int kBlockSize = 32*1024;
const int kNumBlocks = 256;
const int kMaxBlocksPerPage = 4;

u8* CodeCache;
u8** CodeCacheIndex;            // memory addr tag -> pointer to code block in cache
u32* CodeCacheReverseIndex;     // block number -> memory address


bool Init()
{
#ifdef __WIN32__
    CodeCache = (u8*)VirtualAlloc(NULL, kNumBlocks*kBlockSize, MEM_COMMIT|MEM_RESERVE, PAGE_EXECUTE_READWRITE);
#else
    // TODO!!
    CodeCache = NULL;
#endif

    if (!CodeCache)
    {
        printf("JIT: code cache allocation failed\n");
        return false;
    }

    // 0x0_XXXX00
    CodeCacheIndex = new u8*[65536*kMaxBlocksPerPage];
    CodeCacheReverseIndex = new u32[kNumBlocks];

    return true;
}

void DeInit()
{
    if (CodeCache)
    {
#ifdef __WIN32__
       VirtualFree(CodeCache, 0, MEM_RELEASE);
#else
        // TODO!!
        CodeCache = NULL;
#endif
    }

    delete[] CodeCacheIndex;
    delete[] CodeCacheReverseIndex;
}

void Reset()
{
    if (CodeCache)
        memset(CodeCache, 0xCC, kNumBlocks*kBlockSize);

    memset(CodeCacheIndex, 0, 65536*kMaxBlocksPerPage*sizeof(u8*));
    memset(CodeCacheReverseIndex, 0, kNumBlocks*sizeof(u32));
}


void A_UNK(ARM* cpu, u32 pc, u32 instr)
{
    printf("undefined ARM%d instruction %08X @ %08X\n", cpu->Num?7:9, instr, pc-8);
    //for (int i = 0; i < 16; i++) printf("R%d: %08X\n", i, cpu->R[i]);

}

void T_UNK(ARM* cpu, u32 pc, u32 instr)
{
    printf("undefined THUMB%d instruction %04X @ %08X\n", cpu->Num?7:9, instr, pc-4);

}



void A_MSR_IMM(ARM* cpu, u32 pc, u32 instr)
{

}

void A_MSR_REG(ARM* cpu, u32 pc, u32 instr)
{

}

void A_MRS(ARM* cpu, u32 pc, u32 instr)
{

}


void A_MCR(ARM* cpu, u32 pc, u32 instr)
{

}

void A_MRC(ARM* cpu, u32 pc, u32 instr)
{

}



void A_SVC(ARM* cpu, u32 pc, u32 instr)
{

}

void T_SVC(ARM* cpu, u32 pc, u32 instr)
{

}



#define INSTRFUNC_PROTO(x)  void (*x)(ARM* cpu, u32 pc, u32 instr)
#include "ARM_InstrTable.h"
#undef INSTRFUNC_PROTO

}