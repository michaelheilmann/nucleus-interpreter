// Copyright (c) Michael Heilmann 2018
#include "Nucleus/Interpreter/StringHeap.h"

#include "Nucleus/Interpreter/String-internal.h"
#include "Nucleus/Interpreter/Context.h"
#include "Nucleus/Interpreter/JumpTarget.h"

Nucleus_Interpreter_NonNull() static void
premark
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringHeap *stringHeap
    );

Nucleus_Interpreter_NonNull() static void
sweep
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringHeap *stringHeap
    );

Nucleus_Interpreter_NonNull() static void
uninitialize
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringHeap *stringHeap
    );

Nucleus_Interpreter_NonNull() static void
premark
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringHeap *stringHeap
    )
{
    for (size_t i = 0, n = stringHeap->capacity; i < n; ++i)
    {
        Nucleus_Interpreter_GC_Tag *tag = stringHeap->buckets[i];
        while (tag)
        {
            if (Nucleus_Interpreter_GC_Tag_isLocked(tag))
            {
                Nucleus_Interpreter_GC_Tag_setBlack(tag);
            }
        }
    }
}

Nucleus_Interpreter_NonNull() static void
sweep
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringHeap *stringHeap
    )
{
    for (size_t i = 0, n = stringHeap->capacity; i < n; ++i)
    {
        Nucleus_Interpreter_GC_Tag **bucket = &(stringHeap->buckets[i]);
        while (*bucket)
        {
            Nucleus_Interpreter_GC_Tag *entry = *bucket; *bucket = entry->next;
            Nucleus_Interpreter_ProcessContext_deallocate(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context), entry);
            --stringHeap->size;
        }
    }
}

Nucleus_Interpreter_NonNull() static void
uninitialize
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringHeap *stringHeap
    )
{
    Nucleus_Interpreter_GC_Heap_sweep(context, NUCLEUS_INTERPRETER_GC_HEAP(stringHeap));
    Nucleus_Interpreter_ProcessContext_deallocate(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context), stringHeap->buckets);
    stringHeap->buckets = NULL;
    stringHeap->capacity = 0;
}


Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_StringHeap_initialize
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringHeap *stringHeap
    )
{
    Nucleus_Interpreter_GC_Heap_initialize(context, NUCLEUS_INTERPRETER_GC_HEAP(stringHeap));
    stringHeap->size = 0;
    stringHeap->capacity = 16;
    Nucleus_Interpreter_JumpTarget jt;
    Nucleus_Interpreter_ProcessContext_pushJumpTarget(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context), &jt);
    if (!setjmp(jt.environment))
    {
        stringHeap->buckets = Nucleus_Interpreter_ProcessContext_allocateArray(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context),
                                                                            16, sizeof(Nucleus_Interpreter_GC_Tag *));
        Nucleus_Interpreter_ProcessContext_popJumpTarget(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
    }
    else
    {
        Nucleus_Interpreter_ProcessContext_popJumpTarget(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
        Nucleus_Interpreter_Context_raiseError(context, Nucleus_Interpreter_ProcessContext_getStatus(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context)));
    }
    for (size_t i = 0, n = 16; i < n; ++i)
    { stringHeap->buckets[i] = NULL; }
    NUCLEUS_INTERPRETER_GC_HEAP(stringHeap)->premark = NUCLEUS_INTERPRETER_GC_HEAP_PREMARK(&premark);
    NUCLEUS_INTERPRETER_GC_HEAP(stringHeap)->sweep = NUCLEUS_INTERPRETER_GC_HEAP_SWEEP(&sweep);
    NUCLEUS_INTERPRETER_GC_HEAP(stringHeap)->uninitialize = NUCLEUS_INTERPRETER_GC_HEAP_UNINITIALIZE(&uninitialize);
}
