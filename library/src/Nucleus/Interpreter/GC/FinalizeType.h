// Copyright (c) Michael Heilmann 2018
#pragma once

// Forward declaration.
typedef struct Nucleus_Interpreter_GC_Type Nucleus_Interpreter_GC_Type;
typedef struct Nucleus_Interpreter_GC Nucleus_Interpreter_GC;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @ingroup gc
/// @internal
/// @brief Unconditionally cast a @a (Nucleus_Interpreter_GC_FinalizeType) or derived pointer to a @a (Nucleus_Interpreter_GC_FinalizeType) pointer.
#define NUCLEUS_INTERPRETER_GC_FINALIZETYPE(pointer) ((Nucleus_Interpreter_GC_FinalizeType *)(pointer))

/// @ingroup gc
/// @internal
/// @brief Type of a finalizer function of a type.
typedef void (Nucleus_Interpreter_GC_FinalizeType)(Nucleus_Interpreter_GC *gc, Nucleus_Interpreter_GC_Type *type);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
