// Copyright (c) Michael Heilmann 2018
// Interned strings.
#pragma once

#include "Nucleus/Interpreter/Annotations.h"
#include <stdbool.h> /// @todo for bool. Remove this.
#include <stddef.h> /// @todo For size_t. Remove this.

// Forward declaration.
typedef struct Nucleus_Interpreter_Context Nucleus_Interpreter_Context;

/// @ingroup interpreter
/// @internal
/// @brief Unconditionally cast a @a (Nucleus_Interpreter_String) or derived pointer to a @a (Nucleus_Interpreter_String) pointer.
#define NUCLEUS_INTERPRETER_STRING(pointer) ((Nucleus_Interpreter_String *)(pointer))

/// @ingroup interpreter
/// @brief Type of a string.
/// @extends Nucleus_Interpreter_Object
typedef struct Nucleus_Interpreter_String Nucleus_Interpreter_String;

/// @internal
/// @brief Get or create an @a Nucleus_Interpreter_String object for a specified array of Bytes.
/// @param context a pointer to the environment
/// @param stringTable a pointer to the @a Nucleus_Interpreter_StringTable object the @a Nucleus_Interpreter_String object is get from or created in
/// @param bytes a pointer to an array of @a numberOfBytes Bytes
/// @param numberOfBytes the number of Bytes in the array pointed to by @a bytes
/// @return a pointer to @a Nucleus_Interpreter_String object
/// @failure @a *status is assigned a status code denoting the reason for the failure, then @a longjmp(*environment, -1) is invoked
Nucleus_Interpreter_NonNull() Nucleus_Interpreter_String *
Nucleus_Interpreter_String_create
    (
        Nucleus_Interpreter_Context *context,
        const char *bytes,
        size_t numberOfBytes
    );

Nucleus_Interpreter_NonNull() bool
Nucleus_Interpreter_String_equalTo
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_String *first,
        Nucleus_Interpreter_String *second
    );

Nucleus_Interpreter_ReturnNonNull() Nucleus_Interpreter_NonNull() Nucleus_Interpreter_String *
Nucleus_Interpreter_String_concatenate
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_String *first,
        Nucleus_Interpreter_String *second
    );

/// @internal
/// @brief Get the number of Bytes of a @a Nucleus_Interpreter_String object.
/// @param string a pointer to an @a Nucleus_Interpreter_String object
/// @return the number of Bytes of the atom
/// @failure @a *status is assigned a status code denoting the reason for the failure, then @a longjmp(*environment, -1) is invoked
Nucleus_Interpreter_NonNull() size_t
Nucleus_Interpreter_String_getNumberOfBytes
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_String *string
    );

/// @internal
/// @brief Get the Bytes of a @a Nucleus_Interpreter_String object.
/// @param string a pointer to an @a Nucleus_Interpreter_String object
/// @return a pointer to the Bytes of the @a Nucleus_Interpreter_String object
/// @failure @a *status is assigned a status code denoting the reason for the failure, then @a longjmp(*environment, -1) is invoked
Nucleus_Interpreter_ReturnNonNull() Nucleus_Interpreter_NonNull() const char *
Nucleus_Interpreter_String_getBytes
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_String *string
    );
