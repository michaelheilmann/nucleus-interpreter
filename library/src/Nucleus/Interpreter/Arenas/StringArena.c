// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/Interpreter/Arenas/StringArena-private.c.in"

#include "Nucleus/Interpreter/String-internal.h"
#include "Nucleus/Interpreter/JumpTarget.h"

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_StringArena_initialize
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringArena *stringArena
    )
{
    Nucleus_Interpreter_GC_Arena_initialize(context, NUCLEUS_INTERPRETER_GC_ARENA(stringArena));
    stringArena->size = 0;
    stringArena->capacity = 16;
    Nucleus_Interpreter_JumpTarget jt;
    Nucleus_Interpreter_ProcessContext_pushJumpTarget(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context), &jt);
    if (!setjmp(jt.environment))
    {
        stringArena->buckets = Nucleus_Interpreter_ProcessContext_allocateUnmanagedArrayMemory(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context),
                                                                                               16, sizeof(Nucleus_Interpreter_GC_Tag *));
        Nucleus_Interpreter_ProcessContext_popJumpTarget(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
    }
    else
    {
        Nucleus_Interpreter_ProcessContext_popJumpTarget(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
        Nucleus_Interpreter_Context_raiseError(context, Nucleus_Interpreter_ProcessContext_getStatus(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context)));
    }
    for (size_t i = 0, n = 16; i < n; ++i)
    { stringArena->buckets[i] = NULL; }
    NUCLEUS_INTERPRETER_GC_ARENA(stringArena)->premark = NUCLEUS_INTERPRETER_GC_ARENA_PREMARK(&premark);
    NUCLEUS_INTERPRETER_GC_ARENA(stringArena)->sweep = NUCLEUS_INTERPRETER_GC_ARENA_SWEEP(&sweep);
    NUCLEUS_INTERPRETER_GC_ARENA(stringArena)->uninitialize = NUCLEUS_INTERPRETER_GC_ARENA_UNINITIALIZE(&uninitialize);
}
