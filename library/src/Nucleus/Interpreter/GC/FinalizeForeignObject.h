// Copyright (c) 2018 Michael Heilmann
#pragma once

// Forward declaration.
typedef struct Nucleus_Interpreter_GC_Object Nucleus_Interpreter_GC_Object;
typedef struct Nucleus_Interpreter_Context Nucleus_Interpreter_Context;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @ingroup gc
/// @internal
/// @brief Unconditionally cast a @a (Nucleus_Interpreter_FinalizeForeignObject) or derived pointer to a @a (Nucleus_Interpreter_FinalizeForeignObject) pointer.
#define NUCLEUS_INTERPRETER_FINALIZEFOREIGNOBJECT(pointer) ((Nucleus_Interpreter_FinalizeForeignObject *)(pointer))

/// @ingroup gc
/// @internal
/// @brief Type of a finalizer function of foreign object.
typedef void Nucleus_Interpreter_FinalizeForeignObject(Nucleus_Interpreter_Context *context, Nucleus_Interpreter_GC_Object *object);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
