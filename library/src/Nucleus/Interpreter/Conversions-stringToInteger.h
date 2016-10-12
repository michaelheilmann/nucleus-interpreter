// Copyright (c) Michael Heilmann 2018
#pragma once

#include "Nucleus/Interpreter/Annotations.h"
#include "Nucleus/Interpreter/Integer.h"

// Forward declarations.
typedef struct Nucleus_Interpreter_Context Nucleus_Interpreter_Context;
typedef struct Nucleus_Interpreter_String Nucleus_Interpreter_String;

Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Integer
Nucleus_Interpreter_Conversions_stringToInteger
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_String *source
    );
