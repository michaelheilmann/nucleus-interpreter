// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Interpreter/Annotations.h"

// Forward declarations.
typedef struct Nucleus_Interpreter_Context Nucleus_Interpreter_Context;
typedef struct Nucleus_Interpreter_String Nucleus_Interpreter_String;

Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Integer
Nucleus_Interpreter_Conversions_stringToInteger
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_String *source
    );
