// Copyright (c) Michael Heilmann 2018
#pragma once

#include "Nucleus/Interpreter/GC/Heap.h"

// Forward declaration.
typedef struct Nucleus_Interpreter_GC_Tag Nucleus_Interpreter_GC_Tag;

/// @ingroup interpreter
/// @internal
/// @brief A general heap.
/// @extends Nucleus_Interpreter_Heap
typedef struct Nucleus_Interpreter_GeneralHeap Nucleus_Interpreter_GeneralHeap;

struct Nucleus_Interpreter_GeneralHeap
{
    Nucleus_Interpreter_GC_Heap __parent;
    /// @brief A null pointer or a pointer to the first element of the singly-linked list of @a Nucleus_Interpreter_Object) objects.
    Nucleus_Interpreter_GC_Tag *objects;
}; // struct Nucleus_Interpreter_GeneralHeap

/// @ingroup interpreter
/// @internal
/// @brief Initialize a @a (Nucleus_Interpreter_GeneralHeap) object.
/// @param context a pointer to a @a (Nucleus_Interpreter_Context) object
/// @param generalHeap a pointer to an uninitialized @a (Nucleus_Interpreter_GeneralHeap) object
/// @post The @a (Nucleus_Interpreter_GeneralHeap) object was initialized on success, otherwise not.
Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_GeneralHeap_initialize
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_GeneralHeap *generalHeap
    );

/// @ingroup language
/// @internal
/// @brief Uninitialize a @a (Nucleus_Interpreter_GeneralHeap) object.
/// @param context a pointer to a @a (Nucleus_Interpreter_Context) object
/// @param generalHeap a pointer to an initialized @a (Nucleus_Interpreter_GeneralHeap) object
/// @post The @a (Nucleus_Interpreter_GeneralHeap) object was uninitialized.
Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_GeneralHeap_uninitialize
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_GeneralHeap *generalHeap
    );
