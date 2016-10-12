// Copyright (c) Michael Heilmann 2018
#pragma once

/// @ingroup language
/// @internal
/// @brief Status codes of this library.
typedef enum Nucleus_Interpreter_Status Nucleus_Interpreter_Status;

enum Nucleus_Interpreter_Status
{
    /// @brief Status code indicating success.
    /// @invariant This is the only status code with the value @a 0.
    Nucleus_Interpreter_Status_Success = 0,

    /// @brief Status code indicating an invalid argument was passed.
    Nucleus_Interpreter_Status_InvalidArgument,

    /// @brief Status code indicating an allocation failed.
    Nucleus_Interpreter_Status_AllocationFailed,

    /// @brief Status code indicating unreachable code was reached.
    Nucleus_Interpreter_Status_UnreachableCodeReached,

    /// @brief Status code indicating an overflow.
    Nucleus_Interpreter_Status_Overflow,

    /// @brief Status code indicating a lexical error.
    Nucleus_Interpreter_Status_LexicalError,

    /// @brief Status code indicating a syntactical error.
    Nucleus_Interpreter_Status_SyntacticalError,

    /// @brief Status code indicating a semantical error.
    Nucleus_Interpreter_Status_SemanticalError,

    /// @brief Status code indicating a failure because an operation of the environment failed.
    Nucleus_Interpreter_Status_EnvironmentFailed,

    /// @brief Status code indicating a failure because a convresion failed.
    Nucleus_Interpreter_Status_ConversionFailed,

    /// @brief Status code indicating an internal error.
    Nucleus_Interpreter_Status_InternalError,

}; // enum Nucleus_Interpreter_Status
