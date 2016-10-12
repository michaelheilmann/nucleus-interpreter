// Copyright (c) Michael Heilmann 2018
#include "Nucleus/Interpreter/Conversions-stringToInteger.h"

#include "Nucleus/Interpreter/Conversions-stringToInteger-private.c.i"

Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Integer
Nucleus_Interpreter_Conversions_stringToInteger
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_String *source
    )
{
    Nucleus_Interpreter_StringIterator *iterator = Nucleus_Interpreter_StringIterator_create(context, source);
    Nucleus_Interpreter_Symbol plusSign = Nucleus_Interpreter_Symbol_plusSign(context);
    Nucleus_Interpreter_Symbol hyphenMinus = Nucleus_Interpreter_Symbol_hyphenMinus(context);
    Nucleus_Interpreter_Symbol begin = Nucleus_Interpreter_Symbol_begin(context);
    Nucleus_Interpreter_Symbol end = Nucleus_Interpreter_Symbol_end(context);

    // begin
    if (!Nucleus_Interpreter_Symbol_equalTo(context, Nucleus_Interpreter_StringIterator_get(context, iterator), begin))
    { conversionError(context); }
    Nucleus_Interpreter_StringIterator_increment(context, iterator);

    // sign?
    bool isNegative = false;
    if (Nucleus_Interpreter_Symbol_equalTo(context, Nucleus_Interpreter_StringIterator_get(context, iterator), plusSign))
    { Nucleus_Interpreter_StringIterator_increment(context, iterator); }
    else if (Nucleus_Interpreter_Symbol_equalTo(context, Nucleus_Interpreter_StringIterator_get(context, iterator), hyphenMinus))
    { Nucleus_Interpreter_StringIterator_increment(context, iterator); isNegative = true; }

    Nucleus_Interpreter_Integer n = 0;

    // There must be one digit.
    if (!isDigit(context, Nucleus_Interpreter_StringIterator_get(context, iterator)))
    { conversionError(context); }

    // Leading zeroes are not relevant.
    if (isDigitZero(context, Nucleus_Interpreter_StringIterator_get(context, iterator)))
    { Nucleus_Interpreter_StringIterator_increment(context, iterator); }

    //
    while (isDigit(context, Nucleus_Interpreter_StringIterator_get(context, iterator)))
    {
        Nucleus_Interpreter_Integer i = digitToInteger(context, Nucleus_Interpreter_StringIterator_get(context, iterator));
        Nucleus_Interpreter_StringIterator_increment(context, iterator);

        if (n > Nucleus_Interpreter_Integer_GreatestConstant() / 10 || (n >= Nucleus_Interpreter_Integer_GreatestConstant() / 10 && i > 9 + (isNegative ? 1 : 0)))
        { conversionError(context); }

          n = n * 10 + i;
    }

    // Junk following the digits.
    if (!Nucleus_Interpreter_Symbol_equalTo(context, Nucleus_Interpreter_StringIterator_get(context, iterator), end))
    { conversionError(context); }

    if (isNegative) n *= -1;

    return n;
}