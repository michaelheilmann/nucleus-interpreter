// Copyright (c) Michael Heilmann 2018
// https://github.com/nucleus-interpreter/blob/master/documentation/Nucleus_Interpreter_GC.md
#include "Nucleus/Interpreter/GC.h"

#include "Nucleus/Interpreter/GC/Type.h"
#include "Nucleus/Interpreter/GC/Object.h"
#include "Nucleus/Memory.h"

Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Status
Nucleus_Interpreter_GC_initialize
    (
        Nucleus_Interpreter_GC *gc
    )
{
    if (!gc) return Nucleus_Interpreter_Status_InvalidArgument;
    // (1) Initialize the type hash map.
    Nucleus_Status status = Nucleus_Interpreter_GC_initializeTypes(gc);
    if (status) return status;
    // (2) Initialize the gray list.
    gc->gray = NULL;
    return Nucleus_Interpreter_Status_Success;
}

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_GC_uninitialize
    (
        Nucleus_Interpreter_GC *gc
    )
{
    Nucleus_Interpreter_GC_uninitializeTypes(gc);
}

Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Status
Nucleus_Interpreter_GC_allocate
    (
        Nucleus_Interpreter_GC *gc,
        void **memoryBlock,
        size_t size
    )
{
    if (!gc || !memoryBlock) return Nucleus_Interpreter_Status_InvalidArgument;
    void *localMemoryBlock = NULL;
    Nucleus_Status status = Nucleus_allocateMemory(&localMemoryBlock, size);
    if (status)
    {
        switch (status)
        {
        case Nucleus_Status_InvalidArgument:
            return Nucleus_Interpreter_Status_InvalidArgument;
        case Nucleus_Status_AllocationFailed:
            return Nucleus_Interpreter_Status_AllocationFailed;
        default:
            return Nucleus_Interpreter_Status_UnreachableCodeReached;
        };
    }
    Nucleus_fillMemory(localMemoryBlock, 0, size);
    *memoryBlock = localMemoryBlock;
    return Nucleus_Status_Success;
}

Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Status
Nucleus_Interpreter_GC_allocateArray
    (
        Nucleus_Interpreter_GC *gc,
        void **memoryBlock,
        size_t numberOfElements,
        size_t elementSize
    )
{
    if (!gc || !memoryBlock) return Nucleus_Interpreter_Status_InvalidArgument;
    void *localMemoryBlock = NULL;
    Nucleus_Status status = Nucleus_allocateArrayMemory(&localMemoryBlock, numberOfElements, elementSize);
    if (status)
    {
        switch (status)
        {
        case Nucleus_Status_InvalidArgument:
            return Nucleus_Interpreter_Status_InvalidArgument;
        case Nucleus_Status_AllocationFailed:
            return Nucleus_Interpreter_Status_AllocationFailed;
        case Nucleus_Status_Overflow:
            return Nucleus_Interpreter_Status_Overflow;
        default:
            return Nucleus_Interpreter_Status_UnreachableCodeReached;
        };
    }
    Nucleus_fillArrayMemory(localMemoryBlock, 0, numberOfElements, elementSize);
    *memoryBlock = localMemoryBlock;
    return Nucleus_Interpreter_Status_Success;
}

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_GC_deallocate
    (
        Nucleus_Interpreter_GC *gc,
        void *memoryBlock
    )
{ Nucleus_deallocateMemory(memoryBlock); }
