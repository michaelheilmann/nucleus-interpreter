// Copyright (c) Michael Heilmann 2018
#pragma once

#include "Nucleus/Interpreter/Conversions-stringToInteger.h"
#include "Nucleus/Interpreter/Context.h"
#include "Nucleus/Interpreter/Boolean.h"
#include "Nucleus/Interpreter/String.h"
#include "Nucleus/Interpreter/StringIterator.h"
#include "Nucleus/Interpreter/Symbol.h"
#include "Nucleus/Interpreter/PredefinedSymbols.h"

Nucleus_Interpreter_NonNull() static Nucleus_Interpreter_Boolean
isDigit
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_Symbol symbol
    );

Nucleus_Interpreter_NonNull() static bool
isDigitZero
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_Symbol symbol
    );

Nucleus_Interpreter_NonNull() static Nucleus_Interpreter_Integer
digitToInteger
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_Symbol symbol
    );

Nucleus_Interpreter_NoReturn() static void
conversionError
    (
        Nucleus_Interpreter_Context *context
    );
