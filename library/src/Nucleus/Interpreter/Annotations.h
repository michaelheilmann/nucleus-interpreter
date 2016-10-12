// Copyright (c) Michael Heilmann 2018
#pragma once

#include "Nucleus/Annotations.h"

/// @ingroup interpreter
/// @internal
/// @brief Alias for Nucleus_NonNull.
#define Nucleus_Interpreter_NonNull(...) Nucleus_NonNull(__VA_ARGS__)

/// @ingroup interpreter
/// @internal
/// @brief Alias for Nucleus_NoError.
#define Nucleus_Interpreter_NoError() Nucleus_NoError()

/// @ingroup interpreter
/// @internal
/// @brief Alias for Nucleus_NoReturn.
#define Nucleus_Interpreter_NoReturn() Nucleus_NoReturn()

/// @ingroup interpreter
/// @internal
/// @brief Alias for Nucleus_ReturnNonNull.
#define Nucleus_Interpreter_ReturnNonNull() Nucleus_ReturnNonNull()

/// @ingroup interpreter
/// @internal
/// @brief Alias for Nucleus_Restrict.
#define Nucleus_Interpreter_Restrict() Nucleus_Restrict()
