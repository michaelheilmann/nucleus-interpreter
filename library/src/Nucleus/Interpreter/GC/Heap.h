// Copyright (c) Michael Heilmann 2018
#pragma once

#include "Nucleus/Interpreter/Annotations.h"

// Forward declaration.
typedef struct Nucleus_Interpreter_Context Nucleus_Interpreter_Context;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @ingroup gc
/// @internal
#define NUCLEUS_INTERPRETER_GC_HEAP(pointer) ((Nucleus_Interpreter_GC_Heap *)(pointer))

/// @ingroup gc
/// @internal
typedef struct Nucleus_Interpreter_GC_Heap Nucleus_Interpreter_GC_Heap;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @ingroup gc
/// @internal
#define NUCLEUS_INTERPRETER_GC_HEAP_PREMARK(pointer) ((Nucleus_Interpreter_GC_Heap_Premark *)(pointer))

/// @ingroup gc
/// @internal
typedef void (Nucleus_Interpreter_GC_Heap_Premark)(Nucleus_Interpreter_Context *, Nucleus_Interpreter_GC_Heap *);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @ingroup gc
/// @internal
#define NUCLEUS_INTERPRETER_GC_HEAP_SWEEP(pointer) ((Nucleus_Interpreter_GC_Heap_Sweep *)(pointer))

/// @ingroup gc
/// @internal
typedef void (Nucleus_Interpreter_GC_Heap_Sweep)(Nucleus_Interpreter_Context *, Nucleus_Interpreter_GC_Heap *);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @ingroup gc
/// @internal
#define NUCLEUS_INTERPRETER_GC_HEAP_UNINITIALIZE(pointer) ((Nucleus_Interpreter_GC_Heap_Uninitialize *)(pointer))

/// @ingroup gc
/// @internal
typedef void (Nucleus_Interpreter_GC_Heap_Uninitialize)(Nucleus_Interpreter_Context *, Nucleus_Interpreter_GC_Heap *);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

struct Nucleus_Interpreter_GC_Heap
{
    Nucleus_Interpreter_GC_Heap_Premark *premark;
    Nucleus_Interpreter_GC_Heap_Sweep *sweep;
    Nucleus_Interpreter_GC_Heap_Uninitialize *uninitialize;
};

/// @ingroup gc
/// @internal
/// @brief Initialize a @a (Nucleus_Interpreter_GC_Heap) object.
Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_GC_Heap_initialize
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_GC_Heap *heap
    );

/// @ingroup gc
/// @internal
/// @brief Uninitialize a @a (Nucleus_Interpreter_GC_Heap) object.
Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_GC_Heap_uninitialize
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_GC_Heap *heap
    );

/// @ingroup gc
/// @internal
/// @brief Premark a @a (Nucleus_Interpreter_GC_Heap) object i.e. identify roots.
/// @param context a pointer to a @a (Nucleus_Interpreter_Context) object
/// @param heap a pointer to the initialized @a (Nucleus_Interpreter_GC_Heap) object
Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_GC_Heap_premark
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_GC_Heap *heap
    );

/// @ingroup gc
/// @internal
/// @brief Sweep a @a (Nucleus_Interpreter_GC_Heap) object i.e. finalize and deallocate dead objects on the heap.
/// @param context a pointer to a @a (Nucleus_Interpreter_Context) object
/// @param heap a pointer to the initialized @a (Nucleus_Interpreter_GC_Heap) object
Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_GC_Heap_sweep
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_GC_Heap *heap
    );
