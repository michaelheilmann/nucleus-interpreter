// Copyright (c) Michael Heilmann 2018
#pragma once

// Forward declaration.
typedef struct Nucleus_Interpreter_GC_Object Nucleus_Interpreter_GC_Object;
typedef struct Nucleus_Interpreter_Context Nucleus_Interpreter_Context;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @ingroup gc
/// @internal
/// @brief Unconditionally cast a @a (Nucleus_Interpreter_VisitForeignObject) or derived pointer to a @a (Nucleus_Interpreter_VisitForeignObject) pointer.
#define NUCLEUS_INTERPRETER_VISITFOREIGNOBJECT(pointer) ((Nucleus_Interpreter_VisitForeignObject *)(pointer))

/// @ingroup gc
/// @internal
/// @brief Type of a finalizer function of foreign objects.
typedef void Nucleus_Interpreter_VisitForeignObject(Nucleus_Interpreter_Context *context, Nucleus_Interpreter_GC_Object *object);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
