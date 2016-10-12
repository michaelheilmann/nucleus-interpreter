// Copyright (c) Michael Heilmann 2018
#pragma once

// Forward declaration.
typedef struct Nucleus_Interpreter_GC_Object Nucleus_Interpreter_GC_Object;
typedef struct Nucleus_Interpreter_Context Nucleus_Interpreter_Context;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @ingroup gc
/// @internal
/// @brief Unconditionally cast a @a (Nucleus_Interpreter_GC_FinalizeForeignObject) or derived pointer to a @a (Nucleus_Interpreter_GC_FinalizeForeignObject) pointer.
#define NUCLEUS_INTERPRETER_GC_FINALIZEFOREIGNOBJECT(pointer) ((Nucleus_Interpreter_GC_Finalize *)(pointer))

/// @ingroup gc
/// @internal
/// @brief Type of a finalizer function of foreign object.
typedef void Nucleus_Interpreter_GC_FinalizeForeignObject(Nucleus_Interpreter_Context *context, Nucleus_Interpreter_GC_Object *object);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
