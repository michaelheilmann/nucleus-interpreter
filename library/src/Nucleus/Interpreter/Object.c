// Copyright (c) Michael Heilmann 2018
#include "Nucleus/Interpreter/Object.h"

#include "Nucleus/Interpreter/GC/Type.h"
#include "Nucleus/Interpreter/ProcessContext.h"
#include "Nucleus/Interpreter/Context.h"

Nucleus_Interpreter_NoError() Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_Object_lock
    (
        Nucleus_Interpreter_Object *object
    )
{ Nucleus_Interpreter_GC_Tag_lock(address2Tag(object)); }

Nucleus_Interpreter_NoError() Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_Object_unlock
    (
        Nucleus_Interpreter_Object *object
    )
{ Nucleus_Interpreter_GC_Tag_unlock(address2Tag(object)); }

Nucleus_Interpreter_NoError() Nucleus_Interpreter_NonNull() bool
Nucleus_Interpreter_Object_isLocked
    (
        Nucleus_Interpreter_Object *object
    )
{ return Nucleus_Interpreter_GC_Tag_isLocked(address2Tag(object)); }

Nucleus_Interpreter_NoError() Nucleus_Interpreter_NonNull(1) Nucleus_Interpreter_Type *
Nucleus_Interpreter_getOrCreateForeignType
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_Object_Finalize *finalize,
        Nucleus_Interpreter_Object_Visit *visit,
        Nucleus_Interpreter_FinalizeType *finalizeType
    )
{
    Nucleus_Interpreter_Status status;
    Nucleus_Interpreter_GC_Type *type;
    status = Nucleus_Interpreter_GC_getOrCreateForeignType(&NUCLEUS_INTERPRETER_PROCESSCONTEXT(context)->gc,
                                                           &type, NULL, finalize, visit, finalizeType);
    if (status)
    {
        Nucleus_Interpreter_ProcessContext_setStatus(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context), status);
        Nucleus_Interpreter_ProcessContext_jump(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
    }
    return type;
}

Nucleus_Interpreter_NoError() Nucleus_Interpreter_NonNull(1, 2) Nucleus_Interpreter_Type *
Nucleus_Interpreter_getOrCreateArrayType
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_Type *elementType,
        Nucleus_Interpreter_FinalizeType *finalizeType
    )
{
    Nucleus_Interpreter_Status status;
    Nucleus_Interpreter_GC_Type *type;
    status = Nucleus_Interpreter_GC_getOrCreateArrayType(&NUCLEUS_INTERPRETER_PROCESSCONTEXT(context)->gc,
                                                         &type, elementType, finalizeType);
    if (status)
    {
        Nucleus_Interpreter_ProcessContext_setStatus(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context), status);
        Nucleus_Interpreter_ProcessContext_jump(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
    }
    return type;
}

Nucleus_Interpreter_NoError() Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Object_Type *
Nucleus_Interpreter_Object_getType
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_Object *object
    )
{ return Nucleus_Interpreter_GC_Tag_getType(context, address2Tag(object)); }

Nucleus_Interpreter_NoError() Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_Object_setType
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_Object *object,
        Nucleus_Interpreter_Object_Type *type
    )
{ Nucleus_Interpreter_GC_Tag_setType(context, address2Tag(object), type); }
