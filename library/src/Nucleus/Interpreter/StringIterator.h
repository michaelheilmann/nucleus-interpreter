// Copyright (c) Michael Heilmann 2018
#pragma once

#include "Nucleus/Interpreter/Annotations.h"
#include "Nucleus/Interpreter/Symbol.h"
#include <stddef.h> /// @todo For size_t. Remove this.

// Forward declaration.
typedef struct Nucleus_Interpreter_String Nucleus_Interpreter_String;

/// @ingroup language
/// @brief A string iterator.
typedef struct Nucleus_Interpreter_StringIterator Nucleus_Interpreter_StringIterator;

/// @ingroup language
/// @brief Create a @a (Nucleus_Interpreter_StringIterator) object with the specifid input.
/// @param context a pointer to a @a (Nucleus_Interpreter_Context) object
/// @param string a pointer to a @a (Nucleus_Interpreter_String) input object
/// @return a pointer to a @a (Nucleus_Interpreter_StringIterator) object
Nucleus_Interpreter_ReturnNonNull() Nucleus_Interpreter_NonNull() Nucleus_Interpreter_StringIterator *
Nucleus_Interpreter_StringIterator_create
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_String *string
    );

/// @ingroup language
/// @brief Set the input of a @a (Nucleus_Lanuguage_StringIterator) object
/// @param context a pointer to a @a (Nucleus_Interpreter_Context) object
/// @param stringIterator a pointer to the @a (Nucleus_Lanuguage_StringIterator) object
/// @param string a pointer to the @a (Nucleus_Interpreter_String) input object
Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_StringIterator_setInput
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringIterator *stringIterator,
        Nucleus_Interpreter_String *string
    );

/// @ingroup language
/// @brief Get the input of a @a (Nucleus_Lanuguage_StringIterator) object
/// @param context a pointer to a @a (Nucleus_Interpreter_Context) object
/// @param stringIterator a pointer to the @a (Nucleus_Lanuguage_StringIterator) object
/// @return a pointer to the @a (Nucleus_Interpreter_String) input object
Nucleus_Interpreter_ReturnNonNull() Nucleus_Interpreter_NonNull() Nucleus_Interpreter_String *
Nucleus_Interpreter_StringIterator_getInput
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringIterator *stringIterator
    );

/// @ingroup language
/// @brief Get the offset of a @a (Nucleus_Lanuguage_StringIterator) object
/// @param context a pointer to a @a (Nucleus_Interpreter_Context) object
/// @param stringIterator a pointer to the @a (Nucleus_Lanuguage_StringIterator) object
/// @return the offset
Nucleus_Interpreter_NonNull() size_t
Nucleus_Interpreter_StringIterator_getOffset
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringIterator *stringIterator
    );

/// @ingroup language
/// @brief Get the symbol of a string iterator.
/// @param context a pointer to a @a (Nucleus_Interpreter_Context) object
/// @param stringIterator a pointer to the @a (Nucleus_Interpreter_StringIterator) object
/// @return a (Nucleus_Interpreter_Symbol) value
Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Symbol
Nucleus_Interpreter_StringIterator_get
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringIterator *stringIterator
    );

/// @ingroup language
/// @brief Increment a string iterator.
/// @param context a pointer to a @a (Nucleus_Interpreter_Context) object
/// @param stringIterator a pointer to the @a (Nucleus_Interpreter_StringIterator) object
Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_StringIterator_increment
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringIterator *stringIterator
    );

/// @ingroup language
/// @brief Decrement a string iterator.
/// @param context a pointer to a @a (Nucleus_Interpreter_Context)
/// @param stringIterator a pointer to the @a (Nucleus_Interpreter_StringIterator)
Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_StringIterator_decrement
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringIterator *stringIterator
    );
