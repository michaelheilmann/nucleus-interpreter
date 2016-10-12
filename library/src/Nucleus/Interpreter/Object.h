// Copyright (c) Michael Heilmann 2018
#pragma once

#include "Nucleus/Interpreter/GC/Object.h"
#include "Nucleus/Interpreter/GC/Type.h"

typedef Nucleus_Interpreter_GC_Type Nucleus_Interpreter_Object_Type;

#define NUCLEUS_INTERPRETER_OBJECT(pointer) ((Nucleus_Interpreter_Object *)(pointer))
typedef Nucleus_Interpreter_GC_Object Nucleus_Interpreter_Object;

Nucleus_Interpreter_NoError() Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_Object_lock
    (
        Nucleus_Interpreter_Object *object
    );

Nucleus_Interpreter_NoError() Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_Object_unlock
    (
        Nucleus_Interpreter_Object *object
    );

Nucleus_Interpreter_NoError() Nucleus_Interpreter_NonNull() bool
Nucleus_Interpreter_Object_isLocked
    (
        Nucleus_Interpreter_Object *object
    );

/// @todo Rename to Nucleus_Interpreter_Type.
/// @todo Move into "Nucleus/Interpreter/Type.h".
typedef struct Nucleus_Interpreter_GC_Type Nucleus_Interpreter_Type;

#define NUCLEUS_INTERPRETER_OBJECT_FINALIZE(pointer) ((Nucleus_Interpreter_Object_Finalize *)(pointer))
/// @todo Rename to Nucleus_Interpreter_FinalizeForeignObject.
/// @todo Move into "Nucleus/Interpreter/Type.h".
#define Nucleus_Interpreter_Object_Finalize Nucleus_Interpreter_GC_FinalizeForeignObject

#define NUCLEUS_INTERPRETER_OBJECT_VISIT(pointer) ((Nucleus_Interpreter_Object_Visit *)(pointer))
/// @todo Rename to Nucleus_Interpreter_VisitForeignObject.
/// @todo Move into "Nucleus/Interpreter/Type.h".
#define Nucleus_Interpreter_Object_Visit Nucleus_Interpreter_GC_VisitForeignObject

#define NUCLEUS_INTERPRETER_FINALIZETYPE(pointer) ((Nucleus_Interpreter_FinalizeType *)(pointer))
/// @todo Rename to Nucleus_Interpreter_FinalizeType.
/// @todo Move into "Nucleus/Interpreter/Type.h".
#define Nucleus_Interpreter_FinalizeType Nucleus_Interpreter_GC_FinalizeType

/// @todo Rename to Nucleus_Interpreter_getOrCreateForeignType.
/// @todo Move into "Nucleus/Interpreter/Type.h".
Nucleus_Interpreter_NoError() Nucleus_Interpreter_NonNull(1) Nucleus_Interpreter_Type *
Nucleus_Interpreter_getOrCreateForeignType
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_Object_Finalize *finalize,
        Nucleus_Interpreter_Object_Visit *visit,
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
