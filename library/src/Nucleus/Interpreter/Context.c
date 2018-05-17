// Copyright (c) 2018 Michael Heilmann
// Interpreter context.
#include "Nucleus/Interpreter/Context.h"

#include "Nucleus/Interpreter/Context-private.c.in"

#include <assert.h>
#include "Nucleus/Memory.h" /// @todo Remove this.
#include "Nucleus/Interpreter/GC/Object.h"
#include "Nucleus/Interpreter/GC/OnVisit.h"
#include "Nucleus/Interpreter/TS.h"
#include "Nucleus/Interpreter/JumpTarget.h"

Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Status
Nucleus_Interpreter_Context_initialize
    (
        Nucleus_Interpreter_Context *context
    )
{
    // (1) Initialize core context.
    Nucleus_Interpreter_Status status = Nucleus_Interpreter_ProcessContext_initialize(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
    if (status) return status;
    // (2) Initialize scratch spaces.
    context->scratchSpaces = NULL;
    Nucleus_Interpreter_JumpTarget jt1;
    Nucleus_Interpreter_ProcessContext_pushJumpTarget(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context), &jt1);
    if (!setjmp(jt1.environment))
    {
        // (3.1) Initialize string heap.
        Nucleus_Interpreter_StringArena_initialize(context, &context->stringArena);
		// (3.2) Register the string heap.
		status = Nucleus_Interpreter_GC_registerArena(&NUCLEUS_INTERPRETER_PROCESSCONTEXT(context)->gc, NUCLEUS_INTERPRETER_GC_ARENA(&context->stringArena));
		if (status) { Nucleus_Interpreter_GC_Arena_uninitialize(context, NUCLEUS_INTERPRETER_GC_ARENA(&context->stringArena));
					  Nucleus_Interpreter_Context_raiseError(context, status); }
        Nucleus_Interpreter_JumpTarget jt2;
        Nucleus_Interpreter_ProcessContext_pushJumpTarget(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context), &jt2);
        if (!setjmp(jt2.environment))
        {
            // (4.1) Initialize general heap.
            Nucleus_Interpreter_GeneralArena_initialize(context, &context->generalArena);
			// (4.2) Register the general heap.
			status = Nucleus_Interpreter_GC_registerArena(&NUCLEUS_INTERPRETER_PROCESSCONTEXT(context)->gc, NUCLEUS_INTERPRETER_GC_ARENA(&context->generalArena));
			if (status) { Nucleus_Interpreter_GC_Arena_uninitialize(context, NUCLEUS_INTERPRETER_GC_ARENA(&context->generalArena));
			              Nucleus_Interpreter_Context_raiseError(context, status); }
            Nucleus_Interpreter_ProcessContext_popJumpTarget(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
        }
        else
        {
            Nucleus_Interpreter_ProcessContext_popJumpTarget(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
            Nucleus_Interpreter_GC_Arena_uninitialize(context, NUCLEUS_INTERPRETER_GC_ARENA(&context->stringArena));
            Nucleus_Interpreter_Context_raiseError(context, Nucleus_Interpreter_ProcessContext_getStatus(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context)));
        }
    }
    else
    {
        Nucleus_Interpreter_ProcessContext_popJumpTarget(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
        Nucleus_Interpreter_Status status = Nucleus_Interpreter_ProcessContext_getStatus(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
        Nucleus_Interpreter_ProcessContext_uninitialize(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
        return status;
    }
    return Nucleus_Interpreter_Status_Success;
}

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_Context_uninitialize
    (
        Nucleus_Interpreter_Context *context
    )
{
    Nucleus_Interpreter_GC_Arena_uninitialize(context, NUCLEUS_INTERPRETER_GC_ARENA(&context->generalArena));
    Nucleus_Interpreter_GC_Arena_uninitialize(context, NUCLEUS_INTERPRETER_GC_ARENA(&context->stringArena));
    while (context->scratchSpaces)
    {
        Nucleus_Interpreter_ScratchSpace *scratchSpace = context->scratchSpaces; context->scratchSpaces = scratchSpace->next;
        Nucleus_Interpreter_ScratchSpace_destroy(context, scratchSpace);
    }
    Nucleus_Interpreter_ProcessContext_uninitialize(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
}

Nucleus_Interpreter_NonNull(1) Nucleus_Interpreter_Status
Nucleus_Interpreter_Context_create
    (
       Nucleus_Interpreter_Context **context
    )
{
    if (!context) return Nucleus_Interpreter_Status_InvalidArgument;
    Nucleus_Interpreter_Context *temporary;
    Nucleus_Status status = Nucleus_allocateMemory((void **)&temporary, sizeof(Nucleus_Interpreter_Context));
    if (status)
    {
        switch (status)
        {
           case Nucleus_Status_AllocationFailed: return Nucleus_Interpreter_Status_AllocationFailed;
           case Nucleus_Status_InvalidArgument: return Nucleus_Interpreter_Status_InvalidArgument;
           default: return Nucleus_Interpreter_Status_InternalError;
       };
    }
    Nucleus_Interpreter_Status languageStatus = Nucleus_Interpreter_Context_initialize(temporary);
    if (languageStatus)
    {
        Nucleus_deallocateMemory(context);
        return languageStatus;
    }
    *context = temporary;
    return Nucleus_Interpreter_Status_Success;
}

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_Context_destroy
    (
        Nucleus_Interpreter_Context *context
    )
{
    Nucleus_Interpreter_Context_uninitialize(context);
    Nucleus_deallocateMemory(context);
}

Nucleus_Interpreter_NoReturn() Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_Context_raiseError
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_Status status
    )
{
    Nucleus_Interpreter_ProcessContext_setStatus(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context), status);
    Nucleus_Interpreter_ProcessContext_jump(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
}

Nucleus_Interpreter_ReturnNonNull() Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Object *
Nucleus_Interpreter_Context_allocateManagedArray
	(
        Nucleus_Interpreter_Context *context,
		Nucleus_Interpreter_Type *arrayType,
        Nucleus_Interpreter_Size numberOfElements	
	)
{
    Nucleus_Status status;
    Nucleus_Interpreter_GC_Tag *tag;
    status = Nucleus_Interpreter_GC_allocateManagedArrayNoError(&NUCLEUS_INTERPRETER_PROCESSCONTEXT(context)->gc,
                                                                &tag,
                                                                numberOfElements,
																arrayType,
                                                                &context->generalArena.objects);
    if (status)
    {
        Nucleus_Interpreter_ProcessContext_setStatus(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context), status);
        Nucleus_Interpreter_ProcessContext_jump(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
    }
    return tag2Address(tag);
}

Nucleus_Interpreter_ReturnNonNull() Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Object *
Nucleus_Interpreter_Context_allocateManaged
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_Size numberOfBytes
    )
{
    Nucleus_Status status;
    Nucleus_Interpreter_GC_Tag *tag;
    status = Nucleus_Interpreter_GC_allocateManagedNoError(&NUCLEUS_INTERPRETER_PROCESSCONTEXT(context)->gc,
                                                           &tag,
                                                           numberOfBytes,
                                                           &context->generalArena.objects);
    if (status)
    {
        Nucleus_Interpreter_ProcessContext_setStatus(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context), status);
        Nucleus_Interpreter_ProcessContext_jump(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
    }
    return tag2Address(tag);
}

Nucleus_Interpreter_ReturnNonNull() Nucleus_Interpreter_NonNull() char *
Nucleus_Interpreter_Context_acquireScratchSpace
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_Size numberOfBytes
    )
{
    Nucleus_Interpreter_ScratchSpace *scratchSpace = context->scratchSpaces;
    if (!scratchSpace)
    {
        scratchSpace = Nucleus_Interpreter_ScratchSpace_create(context, numberOfBytes);
    }
    if (scratchSpace->numberOfBytes < numberOfBytes)
    {
        Nucleus_Status statusNucleus = Nucleus_reallocateMemory((void **)&scratchSpace,
                                                                sizeof(Nucleus_Interpreter_ScratchSpace) +
                                                                sizeof(char) * numberOfBytes);
        if (statusNucleus)
        {
            Nucleus_Interpreter_Status status;
            switch (statusNucleus)
            {
               case Nucleus_Status_AllocationFailed: { status = Nucleus_Interpreter_Status_AllocationFailed; } break;
               case Nucleus_Status_InvalidArgument:  { status = Nucleus_Interpreter_Status_InvalidArgument; } break;
               default:                              { status = Nucleus_Interpreter_Status_InternalError; } break;
            };
            scratchSpace->next = context->scratchSpaces; context->scratchSpaces = scratchSpace;
            Nucleus_Interpreter_ProcessContext_setStatus(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context), status);
            Nucleus_Interpreter_ProcessContext_jump(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
        }
        scratchSpace->numberOfBytes = numberOfBytes;
    }
    return ((char *)scratchSpace) + sizeof(Nucleus_Interpreter_ScratchSpace);
}

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_Context_relinquishScratchSpace
    (
        Nucleus_Interpreter_Context *context,
        char *bytes
    )
{
    Nucleus_Interpreter_ScratchSpace *scratchSpace = (Nucleus_Interpreter_ScratchSpace *)(bytes - sizeof(Nucleus_Interpreter_ScratchSpace));
    scratchSpace->next = context->scratchSpaces; context->scratchSpaces = scratchSpace;
}

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_gc
    (
        Nucleus_Interpreter_Context *context
    )
{ Nucleus_Interpreter_GC_onRun(context); }

Nucleus_Interpreter_NoError() Nucleus_Interpreter_NonNull(1) void
Nucleus_Interpreter_visit
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_GC_Object *object
    )
{
    if (object)
    {
        Nucleus_Interpreter_GC_Tag *tag = address2Tag(object);
		// If the object is white (i.e. is neither gray nor black), put it into gray list.
        if (Nucleus_Interpreter_GC_Tag_isWhite(tag))
        {
            NUCLEUS_INTERPRETER_PROCESSCONTEXT(context)->gc.gray = tag;
            tag->next = NUCLEUS_INTERPRETER_PROCESSCONTEXT(context)->gc.gray;
            Nucleus_Interpreter_GC_Tag_setGray(tag);
        }
    }
}
