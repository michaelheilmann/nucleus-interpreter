// Copyright (c) Michael Heilmann 2018
#pragma once

#include "Nucleus/Interpreter/Annotations.h"
#include <stdint.h> // For uint8_t, uint16_t, uint32_t, ...
#include <stdbool.h> // For bool.

// Forward declarations.
typedef struct Nucleus_Interpreter_Context Nucleus_Interpreter_Context;

/// @ingroup interpreter
/// @brief A symbol (part of a string).
typedef struct Nucleus_Interpreter_Symbol Nucleus_Interpreter_Symbol;
struct Nucleus_Interpreter_Symbol
{
    uint32_t value;
}; // struct Nucleus_Interpreter_Symbol

Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Symbol
Nucleus_Interpreter_Symbol_create_uint8
    (
        Nucleus_Interpreter_Context *context,
        uint8_t value
    );

Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Symbol
Nucleus_Interpreter_Symbol_create_uint16
    (
        Nucleus_Interpreter_Context *context,
        uint16_t value
    );

Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Symbol
Nucleus_Interpreter_Symbol_create_uint32
    (
        Nucleus_Interpreter_Context *context,
        uint32_t value
    );

Nucleus_Interpreter_NonNull() bool
Nucleus_Interpreter_Symbol_equalTo
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_Symbol x,
        Nucleus_Interpreter_Symbol y
    );

Nucleus_Interpreter_NonNull() bool
Nucleus_Interpreter_Symbol_notEqualTo
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_Symbol x,
        Nucleus_Interpreter_Symbol y
    );

Nucleus_Interpreter_NonNull() bool
Nucleus_Interpreter_Symbol_lowerThan
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_Symbol x,
        Nucleus_Interpreter_Symbol y
    );

Nucleus_Interpreter_NonNull() bool
Nucleus_Interpreter_Symbol_lowerThanOrEqualTo
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_Symbol x,
        Nucleus_Interpreter_Symbol y
    );

Nucleus_Interpreter_NonNull() bool
Nucleus_Interpreter_Symbol_greaterThan
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_Symbol x,
        Nucleus_Interpreter_Symbol y
    );

Nucleus_Interpreter_NonNull() bool
Nucleus_Interpreter_Symbol_greaterThanOrEqualTo
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_Symbol x,
        Nucleus_Interpreter_Symbol y
    );

Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Symbol
Nucleus_Interpreter_Symbol_begin
    (
        Nucleus_Interpreter_Context *context
    );

Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Symbol
Nucleus_Interpreter_Symbol_end
    (
        Nucleus_Interpreter_Context *context
    );
