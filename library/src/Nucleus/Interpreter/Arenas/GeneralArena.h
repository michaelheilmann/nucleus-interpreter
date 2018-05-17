// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Interpreter/GC/Arena.h"

// Forward declaration.
typedef struct Nucleus_Interpreter_GC_Tag Nucleus_Interpreter_GC_Tag;

/// @ingroup interpreter
/// @internal
/// @brief A general heap.
/// @extends Nucleus_Interpreter_Arena
typedef struct Nucleus_Interpreter_GeneralArena Nucleus_Interpreter_GeneralArena;

struct Nucleus_Interpreter_GeneralArena
{
    Nucleus_Interpreter_GC_Arena __parent;
    /// @brief A null pointer or a pointer to the first element of the singly-linked list of @a Nucleus_Interpreter_Object) objects.
    Nucleus_Interpreter_GC_Tag *objects;
}; // struct Nucleus_Interpreter_GeneralArena

/// @ingroup interpreter
/// @internal
/// @brief Initialize a @a (Nucleus_Interpreter_GeneralArena) object.
/// @param context a pointer to a @a (Nucleus_Interpreter_Context) object
/// @param generalArena a pointer to an uninitialized @a (Nucleus_Interpreter_GeneralArena) object
/// @post The @a (Nucleus_Interpreter_GeneralArena) object was initialized on success, otherwise not.
Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_GeneralArena_initialize
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_GeneralArena *generalArena
    );
