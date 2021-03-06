// Copyright (c) 2018 Michael Heilmann
// https://github.com/nucleus-interpreter/blob/master/documentation/Nucleus_Interpreter_GC.md
#pragma once

#include "Nucleus/Interpreter/Annotations.h"
#include "Nucleus/Interpreter/Status.h"
#include "Nucleus/Types/Size.h"
#include "Nucleus/Collections/PointerArray.h"

// Forward declarations.
typedef struct Nucleus_Interpreter_GC_Tag Nucleus_Interpreter_GC_Tag;
typedef struct Nucleus_Interpreter_GC_Arena Nucleus_Interpreter_GC_Arena;
typedef struct Nucleus_Interpreter_Type Nucleus_Interpreter_Type;

typedef enum Nucleus_Interpreter_GC_State Nucleus_Interpreter_GC_State;
enum Nucleus_Interpreter_GC_State
{
    Nucleus_Interpreter_GC_State_Idle,
    Nucleus_Interpreter_GC_State_Premark,
    Nucleus_Interpreter_GC_State_Mark,
    Nucleus_Interpreter_GC_State_Sweep,
}; // enum Nucleus_Interpreter_GC_State

typedef struct Nucleus_Interpreter_GC Nucleus_Interpreter_GC;
struct Nucleus_Interpreter_GC
{
    Nucleus_Interpreter_GC_State state;
    Nucleus_Interpreter_GC_Tag *gray; // List of gray objects.
	Nucleus_Collections_PointerArray arenas; // Array of arenas.
}; // struct Nucleus_Interpreter_GC

Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Status
Nucleus_Interpreter_initializeGC
    (
        Nucleus_Interpreter_GC *gc
    );

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_uninitializeGC
    (
        Nucleus_Interpreter_GC *gc
    );

/// @ingroup gc
/// @internal
/// @brief Allocate an unmanaged memory block.
/// @param gc a pointer to the @ (Nucleus_Interpreter_GC) object
/// @param memoryBlock a pointer to a @a (void *) variable
/// @param size the size, in Bytes, of the memory block to allocate. @a 0 is a valid size.
/// @post @a (*memoryBlock) was assigned a pointer to the beginning of a unmanaged memory of size @a size Bytes
/// and Nucleus_Interpreter_Success was returned. Otherwise @a memoryBlock was not dereferenced and a non-zero
/// status code was returned.
Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Status
Nucleus_Interpreter_GC_allocate
    (
        Nucleus_Interpreter_GC *gc,
        void **memoryBlock,
        size_t size
    );

/// @ingroup gc
/// @internal
/// @brief Allocate an unmanaged memory block.
/// @param gc a pointer to the @ (Nucleus_Interpreter_GC) object
/// @param memoryBlock a pointer to a @a (void *) variable
/// @param numberOfElements, elementSize the size, in Bytes, of the memory block to allocate. @a 0 is a valid size.
/// @post @a (*memoryBlock) was assigned a pointer to the beginning of a unmanaged memory of size @a (numberOfElements *
/// elementSize) Bytes and @a Nucleus_Interpreter_Success was returned. Otherwise @a memoryBlock was not dereferenced
/// and non-zero status code was returned.
Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Status
Nucleus_Interpreter_GC_allocateArray
    (
        Nucleus_Interpreter_GC *gc,
        void **memoryBlock,
        size_t numberOfElements,
        size_t elementSize
    );

/// @ingroup gc
/// @internal
/// @brief Deallocate unmanaged memory block.
/// @param gc a pointer to the @ (Nucleus_Interpreter_GC) object
/// @param memoryBlock a pointer to an unmanaged memory block previously allocated by
/// @a (Nucleus_Interpreter_GC_allocate) or @a (Nucleus_Interpreter_GC_allocateArray)
Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_GC_deallocate
    (
        Nucleus_Interpreter_GC *gc,
        void *memoryBlock
    );

Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Status
Nucleus_Interpreter_GC_registerArena
	(
		Nucleus_Interpreter_GC *gc,
		Nucleus_Interpreter_GC_Arena *arena
	);

