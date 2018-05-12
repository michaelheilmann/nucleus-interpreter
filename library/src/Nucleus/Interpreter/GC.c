// Copyright (c) 2018 Michael Heilmann
// https://github.com/nucleus-interpreter/blob/master/documentation/Nucleus_Interpreter_GC.md
#include "Nucleus/Interpreter/GC.h"

#include "Nucleus/Interpreter/TS.h"
#include "Nucleus/Interpreter/GC/Object.h"
#include "Nucleus/Memory.h"

Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Status
Nucleus_Interpreter_initializeGC
    (
        Nucleus_Interpreter_GC *gc
    )
{
    if (Nucleus_Unlikely(!gc)) return Nucleus_Interpreter_Status_InvalidArgument;
    // Initialize the gray list.
    gc->gray = NULL;
	// Initialize the heap list.
	return Nucleus_Collections_PointerArray_initialize(&gc->arenas, 8, NULL, NULL);
}

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_uninitializeGC
    (
        Nucleus_Interpreter_GC *gc
    )
{
	Nucleus_Collections_PointerArray_uninitialize(&gc->arenas);
}

Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Status
Nucleus_Interpreter_GC_allocate
    (
        Nucleus_Interpreter_GC *gc,
        void **memoryBlock,
        size_t size
    )
{
    if (Nucleus_Unlikely(!gc || !memoryBlock)) return Nucleus_Interpreter_Status_InvalidArgument;
    void *localMemoryBlock = NULL;
    Nucleus_Status status = Nucleus_allocateMemory(&localMemoryBlock, size);
    if (Nucleus_Unlikely(status))
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
    if (Nucleus_Unlikely(!gc || !memoryBlock)) return Nucleus_Interpreter_Status_InvalidArgument;
    void *localMemoryBlock = NULL;
    Nucleus_Status status = Nucleus_allocateArrayMemory(&localMemoryBlock, numberOfElements, elementSize);
    if (Nucleus_Unlikely(status))
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

Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Status
Nucleus_Interpreter_GC_registerArena
	(
		Nucleus_Interpreter_GC *gc,
		Nucleus_Interpreter_GC_Arena *arena
	)
{
	Nucleus_Status status = Nucleus_Collections_PointerArray_append(&gc->arenas, arena);
	if (Nucleus_Unlikely(status))
	{
		switch (status)
		{
			case Nucleus_Status_InvalidArgument:
				return Nucleus_Interpreter_Status_InvalidArgument;
			case Nucleus_Status_Overflow:
				return Nucleus_Interpreter_Status_Overflow;
			case Nucleus_Status_AllocationFailed:
				return Nucleus_Interpreter_Status_AllocationFailed;
			default:
				return Nucleus_Interpreter_Status_InternalError;
		};
	}
	return status;
}
