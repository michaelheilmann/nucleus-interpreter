// Copyright (c) Michael Heilmann 2018
// Interpreter context.
#pragma once

#include "Nucleus/Interpreter/ProcessContext.h"
#include "Nucleus/Interpreter/GeneralHeap.h"
#include "Nucleus/Interpreter/StringHeap.h"
#include "Nucleus/Interpreter/Object.h"

// Forward declaration.

/// @todo Should not be visible.
typedef struct Nucleus_Interpreter_ScratchSpace Nucleus_Interpreter_ScratchSpace;

/// @ingroup interpreter
/// @internal
/// @brief Unconditionally cast a @a (Nucleus_Interpreter_Context) or derived pointer into a @a (Nucleus_Interpreter_Context) pointer
/// @param pointer a @a (Nucleus_Interpreter_Context) or derived pointer
#define NUCLEUS_INTERPRETER_CONTEXT(pointer) ((Nucleus_Interpreter_Context *)(pointer))

/// @ingroup interpreter
/// @internal
/// @brief The base of a context.
/// @details This base is required for creating @a (Nucleus_Language_Heap) objects.
/// @todo Add support for garbage collection types (visit and finalize).
typedef struct Nucleus_Interpreter_Context Nucleus_Interpreter_Context;

struct Nucleus_Interpreter_Context
{
    Nucleus_Interpreter_ProcessContext __parent;
    /// @brief The general heap.
    Nucleus_Interpreter_GeneralHeap generalHeap;
    /// @brief The string heap.
    Nucleus_Interpreter_StringHeap stringHeap;
    /// @brief A null pointer or a pointer to the first element of the singly-linked list of @a (Nucleus_Interpreter_ScratchSpace) objects.
    Nucleus_Interpreter_ScratchSpace *scratchSpaces;
}; // struct Nucleus_Interpreter_Context

/// @ingroup interpreter
/// @internal
/// @brief Initialize this @a (Nucleus_Language_FeatureLevel_OneContext) object.
/// @param context a pointer to an uninitialized @a (Nucleus_Interpreter_Context) object
/// @return #Nucleus_Interpreter_Status_Success on success, a non-zero status code on success
Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Status
Nucleus_Interpreter_Context_initialize
    (
        Nucleus_Interpreter_Context *context
    );

/// @ingroup interpreter
/// @internal
/// @brief Uninitialize this @a (Nucleus_Interpreter_Context) object.
/// @param context a pointer to an initialized @a (Nucleus_Interpreter_Context) object
Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_Context_uninitialize
    (
        Nucleus_Interpreter_Context *context
    );

/// @ingroup interpreter
/// @brief Create a context.
/// @return #Nucleus_Interpreter_Status_Success on success, a non-zero status code on failure
/// @post @a *context was assigned a pointer to a @a Nucleus_Interpreter_Context object on success.
Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Status
Nucleus_Interpreter_Context_create
    (
        Nucleus_Interpreter_Context **context
    );

/// @ingroup interpreter
/// @brief Destroy a context.
/// @param context a pointer to a @a Nucleus_Interpreter_Context object
/// @post The @a Nucleus_Interpreter_Context and all its contained objects were destroyed
Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_Context_destroy
    (
        Nucleus_Interpreter_Context *context
    );

Nucleus_Interpreter_ReturnNonNull() Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Object *
Nucleus_Interpreter_Context_allocateObject
    (
        Nucleus_Interpreter_Context *context,
        size_t numberOfBytes
    );

/// @ingroup interpreter
/// @internal
/// @brief Raise an error.
/// @detail
/// - Assign the status variable of the context as if
/// @code
/// Nucleus_Interpreter_Context_setStatus(context, status)
/// @endcode
/// was called.
/// - Jump to the jump target on the top of the stack of jump targets.
/// In particular, the behavior of a call to this function is undefined if that stack is empty.
/// @param context a pointer to the @a (Nucleus_Interpreter_Context) object
Nucleus_Interpreter_NoReturn() Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_Context_raiseError
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_Status status
    );

Nucleus_Interpreter_ReturnNonNull() Nucleus_Interpreter_NonNull() char *
Nucleus_Interpreter_Context_acquireScratchSpace
    (
        Nucleus_Interpreter_Context *context,
        size_t numberOfBytes
    );

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_Context_relinquishScratchSpace
    (
        Nucleus_Interpreter_Context *context,
        char *bytes
    );

#define Nucleus_Interpreter_Context_assertNotNull(C, A) \
    if (!(A)) { \
        Nucleus_Interpreter_ProcessContext_setStatus(NUCLEUS_INTERPRETER_PROCESSCONTEXT(C), Nucleus_Interpreter_Status_InvalidArgument); \
        Nucleus_Interpreter_ProcessContext_jump(NUCLEUS_INTERPRETER_PROCESSCONTEXT(C)); \
    }

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_gc
    (
        Nucleus_Interpreter_Context *context
    );

Nucleus_Interpreter_NoError() Nucleus_Interpreter_NonNull(1) void
Nucleus_Interpreter_visit
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_GC_Object *object
    );
