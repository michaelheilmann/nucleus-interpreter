// Copyright (c) Michael Heilmann 2018
#pragma once

#include "Nucleus/Interpreter/GC/Heap.h"
#include <stddef.h> // For size_t.

// Forward declaration.
typedef struct Nucleus_Interpreter_String Nucleus_Interpreter_String;
typedef struct Nucleus_Interpreter_GC_Tag Nucleus_Interpreter_GC_Tag;

/// @ingroup interpreter
/// @internal
/// @brief A string heap.
/// @extends Nucleus_Interpreter_Heap
typedef struct Nucleus_Interpreter_StringHeap Nucleus_Interpreter_StringHeap;

struct Nucleus_Interpreter_StringHeap
{
    Nucleus_Interpreter_GC_Heap __parent;
    Nucleus_Interpreter_GC_Tag **buckets;
    size_t size;
    size_t capacity;
}; // struct Nucleus_Interpreter_StringHeap

/// @ingroup interpreter
/// @internal
/// @brief Initialize a @a Nucleus_Interpreter_StringHeap object.
/// @param context a pointer to a @a (Nucleus_Interpreter_Context) object
/// @param stringHeap a pointer to an uninitialized @a (Nucleus_Interpreter_StringHeap) object
/// @post The @a Nucleus_Interpreter_StringHeap object was initialized on success, otherwise not.
Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_StringHeap_initialize
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringHeap *stringHeap
    );

/// @ingroup interpreter
/// @internal
/// @brief Uninitialize a @a Nucleus_Interpreter_StringHeap object.
/// @param context a pointer to a @a (Nucleus_Interpreter_Context) object
/// @param stringHeap a pointer to an initialized @a Nucleus_Interpreter_StringHeap object
/// @post The @a Nucleus_Interpreter_StringHeap object was uninitialized.
Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_StringHeap_uninitialize
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringHeap *stringHeap
    );
