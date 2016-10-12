// Copyright (c) Michael Heilmann 2018
#include "Nucleus/Interpreter/Conversions-stringToInteger-private.h.i"
#include "Nucleus/Interpreter/PredefinedSymbols.h"

Nucleus_Interpreter_NonNull() static bool
isDigit
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_Symbol symbol
    )
{
    // The Unicode Codepoints are consecutively layed out from 0, 1, ..., through 9.
    return Nucleus_Interpreter_Symbol_lowerThanOrEqualTo(context, Nucleus_Interpreter_Symbol_digitZero(context), symbol)
        && Nucleus_Interpreter_Symbol_lowerThanOrEqualTo(context, symbol, Nucleus_Interpreter_Symbol_digitNine(context));
}

Nucleus_Interpreter_NonNull() static Nucleus_Interpreter_Boolean
isDigitZero
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_Symbol symbol
    )
{
    return Nucleus_Interpreter_Symbol_equalTo(context, Nucleus_Interpreter_Symbol_digitZero(context), symbol);
}

Nucleus_Interpreter_NonNull() static Nucleus_Interpreter_Integer
digitToInteger
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_Symbol symbol
    )
{
    return symbol.value - Nucleus_Interpreter_Symbol_digitZero(context).value;
}

Nucleus_Interpreter_NoReturn() static void
conversionError
    (
        Nucleus_Interpreter_Context *context
    )
{
    Nucleus_Interpreter_ProcessContext_setStatus(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context), Nucleus_Interpreter_Status_ConversionFailed);
    Nucleus_Interpreter_ProcessContext_jump(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
}
