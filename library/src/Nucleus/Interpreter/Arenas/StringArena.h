// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Interpreter/GC/Arena.h"
#include "Nucleus/Types/Size.h"

// Forward declaration.
typedef struct Nucleus_Interpreter_String Nucleus_Interpreter_String;
typedef struct Nucleus_Interpreter_GC_Tag Nucleus_Interpreter_GC_Tag;

/// @ingroup interpreter
/// @internal
/// @brief A string arena.
/// @extends Nucleus_Interpreter_Arena
typedef struct Nucleus_Interpreter_StringArena Nucleus_Interpreter_StringArena;

struct Nucleus_Interpreter_StringArena
{
    Nucleus_Interpreter_GC_Arena __parent;
    Nucleus_Interpreter_GC_Tag **buckets;
    Nucleus_Size size;
    Nucleus_Size capacity;
}; // struct Nucleus_Interpreter_StringArena

/// @ingroup interpreter
/// @internal
/// @brief Initialize a @a Nucleus_Interpreter_StringArena object.
/// @param context a pointer to a @a (Nucleus_Interpreter_Context) object
/// @param stringArena a pointer to an uninitialized @a (Nucleus_Interpreter_StringArena) object
/// @post The @a (Nucleus_Interpreter_StringArena) object was initialized on success, otherwise not.
Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_StringArena_initialize
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringArena *stringArena
    );
