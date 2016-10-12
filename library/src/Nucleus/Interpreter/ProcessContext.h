// Copyright (c) Michael Heilmann 2018
// Provides getting/setting a status, pushing/popping/jumping to jump targets, and memory allocations/deallocations.
#pragma once

#include "Nucleus/Interpreter/Annotations.h"
#include "Nucleus/Interpreter/Status.h"
#include "Nucleus/Interpreter/GC.h"
#include <stddef.h> /// @todo For size_t. Remove this.

// Forward declaration.
typedef struct Nucleus_Interpreter_JumpTarget Nucleus_Interpreter_JumpTarget;

/// @ingroup interpreter
/// @internal
/// @brief Unconditionally cast a @a (Nucleus_Interpreter_ProcessContext) or derived pointer into a @a (Nucleus_Interpreter_ProcessContext) pointer
/// @param pointer a @a (Nucleus_Interpreter_ProcessContext) or derived pointer
#define NUCLEUS_INTERPRETER_PROCESSCONTEXT(pointer) ((Nucleus_Interpreter_ProcessContext *)(pointer))

/// @ingroup interpreter
/// @internal
/// @brief Process context which provides
/// - setting/getting the context status,
/// - pushing/popping jump targets,
/// - jumping to jump targets, and
/// - raw memory allocations and deallocations.
/// This is the required functionality derived contexts to add heaps and stack.
typedef struct Nucleus_Interpreter_ProcessContext Nucleus_Interpreter_ProcessContext;

struct Nucleus_Interpreter_ProcessContext
{
    /// @brief A null pointer or a pointer to the last element of the singly-linked list stack of @a (Nucleus_Interpreter_JumpTarget) objects.
    Nucleus_Interpreter_JumpTarget *jumpTargets;
    /// @brief The status variable of this context.
    /// Default value is Nucleus_Language_FeatureLevelOne_Status_Success.
    Nucleus_Interpreter_Status status;
    /// @brief The garbage collector.
    Nucleus_Interpreter_GC gc;
}; // struct Nucleus_Interpreter_ProcessContext

/// @ingroup interpreter
/// @internal
/// @brief Initialize this @a (Nucleus_Interpreter_ProcessContext) object.
/// @param context a pointer to an uninitialized @a (Nucleus_Interpreter_ProcessContext) object
/// @return #Nucleus_Interpreter_Status_Success on success, a non-zero status code on success
Nucleus_Interpreter_NoError() Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Status
Nucleus_Interpreter_ProcessContext_initialize
    (
        Nucleus_Interpreter_ProcessContext *context
    );

/// @ingroup interpreter
/// @internal
/// @brief Uninitialize this @a (Nucleus_Interpreter_ProcessContext) object.
/// @param context a pointer to an initialized @a (Nucleus_Interpreter_ProcessContext) object
Nucleus_Interpreter_NoError() Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_ProcessContext_uninitialize
    (
        Nucleus_Interpreter_ProcessContext *context
    );

/// @ingroup language
/// @internal
/// @brief Push a jump target on the top of the stack of jump targets of a @a (Nucleus_Interpreter_ProcessContext).
/// @param context a pointer to the @a (Nucleus_Interpreter_ProcessContext) object
/// @param errorHandler a pointer to the @a (Nucleus_Interpreter_JumpTarget) object
Nucleus_Interpreter_NoError() Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_ProcessContext_pushJumpTarget
    (
        Nucleus_Interpreter_ProcessContext *context,
        Nucleus_Interpreter_JumpTarget *jumpTarget
    );

/// @ingroup interpreter
/// @internal
/// @brief Pop a jump target from the stack of jump targets of a @a (Nucleus_Interpreter_ProcessContext).
/// @param context a pointer to the @a (Nucleus_Interpreter_ProcessContext) object
/// @undefined the error handler stack of the @a (Nucleus_Interpreter_ProcessContext) object is empty
Nucleus_Interpreter_NoError() Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_ProcessContext_popJumpTarget
    (
        Nucleus_Interpreter_ProcessContext *context
    );

/// @ingroup interpreter
/// @internal
/// @brief Get the value of the status variable of a @a (Nucleus_Interpreter_ProcessContext).
/// @param context a pointer to the @ (Nucleus_Interpreter_ProcessContext) object
/// @return the value assigned to the status variable
Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Status
Nucleus_Interpreter_ProcessContext_getStatus
    (
        Nucleus_Interpreter_ProcessContext *context
    );

/// @ingroup interpreter
/// @internal
/// @brief Set the value of the status variable of a @a (Nucleus_Interpreter_ProcessContext).
/// @param context a pointer to the @ (Nucleus_Interpreter_ProcessContext) object
/// @param status the value of to be assigned to the status variable
Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_ProcessContext_setStatus
    (
        Nucleus_Interpreter_ProcessContext *context,
        Nucleus_Interpreter_Status status
    );

/// @ingroup interpreter
/// @internal
/// @brief Allocate an unmanaged memory block.
/// @param context a pointer to the @ (Nucleus_Interpreter_ProcessContext) object
/// @param size the size, in Bytes, of the memory block to allocate. @a 0 is a valid size.
/// @return a pointer to the beginning of the unmanaged memory block of the size @a numberOfBytes
Nucleus_Interpreter_ReturnNonNull() Nucleus_Interpreter_NonNull() void *
Nucleus_Interpreter_ProcessContext_allocate
    (
        Nucleus_Interpreter_ProcessContext *context,
        size_t size
    );

/// @ingroup interpreter
/// @internal
/// @brief Allocate an unmanaged memory block.
/// @param context a pointer to the @ (Nucleus_Interpreter_ProcessContext) object
/// @param numberOfElements, elementSize the size, in Bytes, of the memory block to allocate. @a 0 is a valid size.
/// @return a pointer to the beginning of the unmanaged memory block of the size @a numberOfBytes
Nucleus_Interpreter_ReturnNonNull() Nucleus_Interpreter_NonNull() void *
Nucleus_Interpreter_ProcessContext_allocateArray
    (
        Nucleus_Interpreter_ProcessContext *context,
        size_t numberOfElements,
        size_t elementSize
    );

/// @ingroup interpreter
/// @internal
/// @brief Deallocate unmanaged memory block.
/// @param context a pointer to the @ (Nucleus_Interpreter_ProcessContext) object
/// @param memoryBlock a pointer to an unmanaged memory block previously allocated by
/// @a (Nucleus_Interpreter_ProcessContext_allocate) or @a (Nucleus_Interpreter_ProcessContext_allocateArray)
Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_ProcessContext_deallocate
    (
        Nucleus_Interpreter_ProcessContext *context,
        void *memoryBlock
    );

Nucleus_Interpreter_NoReturn() Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_ProcessContext_jump
    (
        Nucleus_Interpreter_ProcessContext *context
    );
