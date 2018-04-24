// Copyright (c) Michael Heilmann 2018
#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @ingroup gc
/// @internal
/// @brief Unconditionally cast a @a (Nucleus_Interpreter_FinalizeType) or derived pointer to a @a (Nucleus_Interpreter_FinalizeType) pointer.
#define NUCLEUS_INTERPRETER_FINALIZETYPE(pointer) ((Nucleus_Interpreter_FinalizeType *)(pointer))

/// @ingroup gc
/// @internal
/// @brief Type of a finalizer function of a type.
typedef void (Nucleus_Interpreter_FinalizeType)();

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
