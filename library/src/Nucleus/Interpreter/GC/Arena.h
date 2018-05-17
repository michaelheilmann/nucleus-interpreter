// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Interpreter/Annotations.h"

// Forward declaration.
typedef struct Nucleus_Interpreter_Context Nucleus_Interpreter_Context;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @ingroup gc
/// @internal
#define NUCLEUS_INTERPRETER_GC_ARENA(pointer) ((Nucleus_Interpreter_GC_Arena *)(pointer))

/// @ingroup gc
/// @internal
typedef struct Nucleus_Interpreter_GC_Arena Nucleus_Interpreter_GC_Arena;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @ingroup gc
/// @internal
#define NUCLEUS_INTERPRETER_GC_ARENA_PREMARK(pointer) ((Nucleus_Interpreter_GC_Arena_Premark *)(pointer))

/// @ingroup gc
/// @internal
typedef void (Nucleus_Interpreter_GC_Arena_Premark)(Nucleus_Interpreter_Context *, Nucleus_Interpreter_GC_Arena *);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @ingroup gc
/// @internal
#define NUCLEUS_INTERPRETER_GC_ARENA_SWEEP(pointer) ((Nucleus_Interpreter_GC_Arena_Sweep *)(pointer))

/// @ingroup gc
/// @internal
typedef void (Nucleus_Interpreter_GC_Arena_Sweep)(Nucleus_Interpreter_Context *, Nucleus_Interpreter_GC_Arena *);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @ingroup gc
/// @internal
#define NUCLEUS_INTERPRETER_GC_ARENA_UNINITIALIZE(pointer) ((Nucleus_Interpreter_GC_Arena_Uninitialize *)(pointer))

/// @ingroup gc
/// @internal
typedef void (Nucleus_Interpreter_GC_Arena_Uninitialize)(Nucleus_Interpreter_Context *, Nucleus_Interpreter_GC_Arena *);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

struct Nucleus_Interpreter_GC_Arena
{
    Nucleus_Interpreter_GC_Arena_Premark *premark;
    Nucleus_Interpreter_GC_Arena_Sweep *sweep;
    Nucleus_Interpreter_GC_Arena_Uninitialize *uninitialize;
};

/// @ingroup gc
/// @internal
/// @brief Initialize a @a (Nucleus_Interpreter_GC_Arena) object.
Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_GC_Arena_initialize
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_GC_Arena *arena
    );

/// @ingroup gc
/// @internal
/// @brief Uninitialize a @a (Nucleus_Interpreter_GC_Arena) object.
Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_GC_Arena_uninitialize
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_GC_Arena *arena
    );

/// @ingroup gc
/// @internal
/// @brief Premark a @a (Nucleus_Interpreter_GC_Arena) object i.e. identify roots.
/// @param context a pointer to a @a (Nucleus_Interpreter_Context) object
/// @param arena a pointer to the initialized @a (Nucleus_Interpreter_GC_Arena) object
Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_GC_Arena_premark
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_GC_Arena *arena
    );

/// @ingroup gc
/// @internal
/// @brief Sweep a @a (Nucleus_Interpreter_GC_Arena) object i.e. finalize and deallocate dead objects in the arena.
/// @param context a pointer to a @a (Nucleus_Interpreter_Context) object
/// @param arena a pointer to the initialized @a (Nucleus_Interpreter_GC_Arena) object
Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_GC_Arena_sweep
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_GC_Arena *arena
    );
