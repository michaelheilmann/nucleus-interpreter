// Copyright (c) Michael Heilmann 2018
// https://github.com/nucleus-interpreter/blob/master/documentation/Nucleus_Interpreter_TypeSystem.md
#pragma once

#include "Nucleus/Interpreter/Boolean.h"
#include "Nucleus/Interpreter/Integer.h"
#include "Nucleus/Interpreter/Real.h"
#include "Nucleus/Interpreter/String.h"
#include "Nucleus/Interpreter/Void.h"

Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Boolean
Nucleus_Interpreter_stringToBoolean
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_String *source
    );

Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Integer
Nucleus_Interpreter_stringToInteger
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_String *source
    );

Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Real
Nucleus_Interpreter_stringToReal
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_String *source
    );

Nucleus_Interpreter_ReturnNonNull() Nucleus_Interpreter_NonNull() Nucleus_Interpreter_String *
Nucleus_Interpreter_stringToString
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_String *source
    );

Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Void
Nucleus_Interpreter_stringToVoid
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_String *source
    );
