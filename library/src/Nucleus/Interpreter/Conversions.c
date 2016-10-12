// Copyright (c) Michael Heilmann 2018
// https://github.com/nucleus-interpreter/blob/master/documentation/Nucleus_Interpreter_TypeSystem.md
#include "Nucleus/Interpreter/Conversions.h"

#include "Nucleus/Interpreter/Context.h"
#include "Nucleus/Interpreter/String.h"
#include <stdio.h>
#include "Nucleus/Interpreter/Conversions-stringToInteger.h"

Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Boolean
Nucleus_Interpreter_stringToBoolean
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_String *source
    )
{
    Nucleus_Interpreter_String *trueString = Nucleus_Interpreter_String_create(context, "true", sizeof("true") - 1),
                               *falseString = Nucleus_Interpreter_String_create(context, "false", sizeof("false") - 1);
    if (Nucleus_Interpreter_String_equalTo(context, trueString, source))
    { return Nucleus_Interpreter_Boolean_TrueConstant(); }
    else if (Nucleus_Interpreter_String_equalTo(context, falseString, source))
    { return Nucleus_Interpreter_Boolean_FalseConstant(); }
    else
    { Nucleus_Interpreter_ProcessContext_setStatus(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context), Nucleus_Interpreter_Status_ConversionFailed);
      Nucleus_Interpreter_ProcessContext_jump(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context)); }
}

Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Integer
Nucleus_Interpreter_stringToInteger
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_String *source
    )
{ return Nucleus_Interpreter_Conversions_stringToInteger(context, source); }

Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Real
Nucleus_Interpreter_stringToReal
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_String *source
    )
{
    Nucleus_Interpreter_Real target;
    const char *p = Nucleus_Interpreter_String_getBytes(context, source);
    size_t n = Nucleus_Interpreter_String_getNumberOfBytes(context, source);
    char *t = Nucleus_Interpreter_Context_acquireScratchSpace(context, n + 1);
    t[n] = '\0';
    int result = sscanf(t, "%f", &target);
    Nucleus_Interpreter_Context_relinquishScratchSpace(context, t);
    if (result != 1)
    { Nucleus_Interpreter_ProcessContext_setStatus(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context),
                                                Nucleus_Interpreter_Status_ConversionFailed);
      Nucleus_Interpreter_ProcessContext_jump(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context)); }
    return target;
}

Nucleus_Interpreter_ReturnNonNull() Nucleus_Interpreter_NonNull() Nucleus_Interpreter_String *
Nucleus_Interpreter_stringToString
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_String *source
    )
{ return source; }

Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Void
Nucleus_Interpreter_stringToVoid
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_String *source
    )
{
    Nucleus_Interpreter_String *voidString = Nucleus_Interpreter_String_create(context, "void", sizeof("void") - 1);
    if (Nucleus_Interpreter_String_equalTo(context, voidString, source))
    { return Nucleus_Interpreter_Void_VoidConstant(); }
    else
    { Nucleus_Interpreter_ProcessContext_setStatus(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context), Nucleus_Interpreter_Status_ConversionFailed);
      Nucleus_Interpreter_ProcessContext_jump(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context)); }
}