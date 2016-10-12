// Copyright (c) Michael Heilmann 2018
#include "Nucleus/Interpreter/Symbol.h"

Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Symbol
Nucleus_Interpreter_Symbol_create_uint8
    (
        Nucleus_Interpreter_Context *context,
        uint8_t value
    )
{
    Nucleus_Interpreter_Symbol symbol = { .value = value };
    return symbol;
}

Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Symbol
Nucleus_Interpreter_Symbol_create_uint16
    (
        Nucleus_Interpreter_Context *context,
        uint16_t value
    )
{
    Nucleus_Interpreter_Symbol symbol = { .value = value };
    return symbol;
}

Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Symbol
Nucleus_Interpreter_Symbol_create_uint32
    (
        Nucleus_Interpreter_Context *context,
        uint32_t value
    )
{
    Nucleus_Interpreter_Symbol symbol = { .value = value };
    return symbol;
}

Nucleus_Interpreter_NonNull() bool
Nucleus_Interpreter_Symbol_equalTo
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_Symbol x,
        Nucleus_Interpreter_Symbol y
    )
{ return x.value == y.value; }

Nucleus_Interpreter_NonNull() bool
Nucleus_Interpreter_Symbol_notEqualTo
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_Symbol x,
        Nucleus_Interpreter_Symbol y
    )
{ return x.value != y.value; }

Nucleus_Interpreter_NonNull() bool
Nucleus_Interpreter_Symbol_lowerThan
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_Symbol x,
        Nucleus_Interpreter_Symbol y
    )
{ return x.value < y.value; }

Nucleus_Interpreter_NonNull() bool
Nucleus_Interpreter_Symbol_lowerThanOrEqualTo
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_Symbol x,
        Nucleus_Interpreter_Symbol y
    )
{ return x.value <= y.value; }

Nucleus_Interpreter_NonNull() bool
Nucleus_Interpreter_Symbol_greaterThan
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_Symbol x,
        Nucleus_Interpreter_Symbol y
    )
{ return x.value > y.value; }

Nucleus_Interpreter_NonNull() bool
Nucleus_Interpreter_Symbol_greaterThanOrEqualTo
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_Symbol x,
        Nucleus_Interpreter_Symbol y
    )
{ return x.value >= y.value; }

Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Symbol
Nucleus_Interpreter_Symbol_begin
    (
        Nucleus_Interpreter_Context *context
    )
{ return Nucleus_Interpreter_Symbol_create_uint16(context, 255+1); }

Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Symbol
Nucleus_Interpreter_Symbol_end
    (
        Nucleus_Interpreter_Context *context
    )
{ return Nucleus_Interpreter_Symbol_create_uint16(context, 255+2); }
