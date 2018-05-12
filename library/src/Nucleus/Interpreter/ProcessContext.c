// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/Interpreter/ProcessContext.h"

#include <assert.h>
#include "Nucleus/Memory.h"
#include "Nucleus/Interpreter/JumpTarget.h"

Nucleus_Interpreter_NoError() Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Status
Nucleus_Interpreter_ProcessContext_initialize
    (
        Nucleus_Interpreter_ProcessContext *context
    )
{
    if (!context) return Nucleus_Interpreter_Status_InvalidArgument;
    //
    context->status = Nucleus_Interpreter_Status_Success;
    //
    context->jumpTargets = NULL;
    //
    context->status = Nucleus_Interpreter_initializeTS(&context->ts);
    if (context->status) return context->status;
    //
    context->status = Nucleus_Interpreter_initializeGC(&context->gc);
    if (context->status)
    {
        Nucleus_Interpreter_uninitializeTS(&context->ts);
        return context->status;
    }
    //
    return context->status;
}

Nucleus_Interpreter_NoError() Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_ProcessContext_uninitialize
    (
        Nucleus_Interpreter_ProcessContext *context
    )
{
    Nucleus_Interpreter_uninitializeGC(&context->gc);
    Nucleus_Interpreter_uninitializeTS(&context->ts);
}

Nucleus_Interpreter_NoError() Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_ProcessContext_pushJumpTarget
    (
        Nucleus_Interpreter_ProcessContext *context,
        Nucleus_Interpreter_JumpTarget *jumpTarget
    )
{
    assert(NULL != context && NULL != jumpTarget);
    jumpTarget->previous = context->jumpTargets;
    context->jumpTargets = jumpTarget;
}

Nucleus_Interpreter_NoError() Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_ProcessContext_popJumpTarget
    (
        Nucleus_Interpreter_ProcessContext *context
    )
{
    assert(NULL != context && NULL != context->jumpTargets);
    context->jumpTargets = context->jumpTargets->previous;
}

Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Status
Nucleus_Interpreter_ProcessContext_getStatus
    (
        Nucleus_Interpreter_ProcessContext *context
    )
{ return context->status; }

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_ProcessContext_setStatus
    (
        Nucleus_Interpreter_ProcessContext *context,
        Nucleus_Interpreter_Status status
    )
{ context->status = status; }

Nucleus_Interpreter_ReturnNonNull() Nucleus_Interpreter_NonNull() void *
Nucleus_Interpreter_ProcessContext_allocateUnmanagedMemory
    (
        Nucleus_Interpreter_ProcessContext *context,
        Nucleus_Interpreter_Size size
    )
{
    void *memoryBlock;
    Nucleus_Interpreter_Status status = Nucleus_Interpreter_GC_allocate(&context->gc,
                                                                        &memoryBlock,
                                                                        size);
    if (status)
    {
        Nucleus_Interpreter_ProcessContext_setStatus(context, status);
        Nucleus_Interpreter_ProcessContext_jump(context);
    }
    return memoryBlock;
}

Nucleus_Interpreter_ReturnNonNull() Nucleus_Interpreter_NonNull() void *
Nucleus_Interpreter_ProcessContext_allocateUnmanagedArrayMemory
    (
        Nucleus_Interpreter_ProcessContext *context,
        Nucleus_Interpreter_Size numberOfElements,
        Nucleus_Interpreter_Size elementSize
    )
{
    void *memoryBlock;
    Nucleus_Interpreter_Status status = Nucleus_Interpreter_GC_allocateArray(&context->gc,
                                                                             &memoryBlock,
                                                                             numberOfElements,
                                                                             elementSize);
    if (status)
    {
        Nucleus_Interpreter_ProcessContext_setStatus(context, status);
        Nucleus_Interpreter_ProcessContext_jump(context);
    }
    return memoryBlock;
}

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_ProcessContext_deallocateUnmanagedMemory
    (
        Nucleus_Interpreter_ProcessContext *context,
        void *memoryBlock
    )
{ Nucleus_Interpreter_GC_deallocate(&context->gc, memoryBlock); }

Nucleus_Interpreter_NoReturn() Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_ProcessContext_jump
    (
        Nucleus_Interpreter_ProcessContext *context
    )
{
    assert(NULL != context && NULL != context->jumpTargets);
    longjmp(context->jumpTargets->environment, -1);
}
