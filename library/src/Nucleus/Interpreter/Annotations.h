// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Types/Boolean.h"
#include "Nucleus/Types/HashValue.h"
#include "Nucleus/Types/Integer.h"
#include "Nucleus/Types/Natural.h"
#include "Nucleus/Types/Size.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

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

/// @ingroup interpreter
/// @internal
/// @brief Alias for Nucleus_Likely.
#define Nucleus_Interpreter_Likely(expression) Nucleus_Likely(expression)

/// @ingroup interpreter
/// @internal
/// @brief Alias for Nucleus_Unlikely.
#define Nucleus_Interpreter_Unlikely(expression) Nucleus_Unlikely(expression)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// https://github.com/nucleus-interpreter/blob/master/documentation/Nucleus_Interpreter_TypeSystem.md
// Alias for Nucleus_Size.
typedef Nucleus_Size Nucleus_Interpreter_Size;
// Alias for Nucleus_Size_Least.
#define Nucleus_Interpreter_Size_LeastConstant() (Nucleus_Size_Least
// Alias for Nucleus_Size_Greatest.
#define Nucleus_Interpreter_Size_GreatestConstant() (Nucleus_Size_Greatest)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// https://github.com/nucleus-interpreter/blob/master/documentation/Nucleus_Interpreter_TypeSystem.md
// Alias for Nucleus_Boolean.
typedef Nucleus_Boolean Nucleus_Interpreter_Boolean;
// Alias for Nucleus_Boolean_True.
#define Nucleus_Interpreter_Boolean_TrueConstant() (Nucleus_Boolean_True)
// Alias for Nucleus_Boolean_False.
#define Nucleus_Interpreter_Boolean_FalseConstant() (Nucleus_Boolean_False)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// https://github.com/nucleus-interpreter/blob/master/documentation/Nucleus_Interpreter_TypeSystem.md
// Alias for Nucleus_Boolean.
typedef Nucleus_Boolean Nucleus_Interpreter_Boolean;
// Alias for Nucleus_Boolean_True.
#define Nucleus_Interpreter_Boolean_TrueConstant() (Nucleus_Boolean_True)
// Alias for Nucleus_Boolean_False.
#define Nucleus_Interpreter_Boolean_FalseConstant() (Nucleus_Boolean_False)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// https://github.com/nucleus-interpreter/blob/master/documentation/Nucleus_Interpreter_TypeSystem.md
// Alias for Nucleus_Integer.
typedef Nucleus_Integer Nucleus_Interpreter_Integer;
// Alias for Nucleus_Integer_Least.
#define Nucleus_Interpreter_Integer_LeastConstant() (Nucleus_Integer_Least)
// Alias for Nucleus_Integer_Greatest.
#define Nucleus_Interpreter_Integer_GreatestConstant() (Nucleus_Integer_Greatest)
