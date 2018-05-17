// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Interpreter/GC/Object.h"
#include "Nucleus/Interpreter/TS.h"

#define NUCLEUS_INTERPRETER_OBJECT(pointer) ((Nucleus_Interpreter_Object *)(pointer))
typedef Nucleus_Interpreter_GC_Object Nucleus_Interpreter_Object;

Nucleus_Interpreter_NoError() Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_Object_lock
    (
		Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_Object *object
    );

Nucleus_Interpreter_NoError() Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_Object_unlock
    (
		Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_Object *object
    );

Nucleus_Interpreter_NoError() Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Boolean
Nucleus_Interpreter_Object_isLocked
    (
		Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_Object *object
    );

/// @todo Rename to Nucleus_Interpreter_getOrCreateForeignType.
/// @todo Move into "Nucleus/Interpreter/Type.h".
Nucleus_Interpreter_NoError() Nucleus_Interpreter_NonNull(1) Nucleus_Interpreter_Type *
Nucleus_Interpreter_getOrCreateForeignType
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_FinalizeForeignObject *finalizeForeignObject,
        Nucleus_Interpreter_VisitForeignObject *visitForeignObject,
        Nucleus_Interpreter_FinalizeType *finalizeType
    );

/// @todo Rename to Nucleus_Interpreter_getOrCreateArrayType
/// @todo Move into "Nucleus/Interpreter/Type.h".
Nucleus_Interpreter_NoError() Nucleus_Interpreter_NonNull(1, 2) Nucleus_Interpreter_Type *
Nucleus_Interpreter_getOrCreateArrayType
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_Type *elementType,
        Nucleus_Interpreter_FinalizeType *finalizeType
    );

Nucleus_Interpreter_NoError() Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Type *
Nucleus_Interpreter_Object_getType
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_Object *object
    );

Nucleus_Interpreter_NoError() Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_Object_setType
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_Object *object,
        Nucleus_Interpreter_Type *type
    );
