// Copyright (c) Michael Heilmann 2018
#include "Nucleus/Interpreter/StringIterator-private.c.in"

Nucleus_Interpreter_ReturnNonNull() Nucleus_Interpreter_NonNull() Nucleus_Interpreter_StringIterator *
Nucleus_Interpreter_StringIterator_create
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_String *string
    )
{
    Nucleus_Interpreter_StringIterator *stringIterator = (Nucleus_Interpreter_StringIterator *)Nucleus_Interpreter_Context_allocateObject(context, sizeof(Nucleus_Interpreter_StringIterator));
    Nucleus_Interpreter_Type *type = getOrCreateType(context);
    Nucleus_Interpreter_Object_setType(context, NUCLEUS_INTERPRETER_OBJECT(stringIterator), type);
    stringIterator->string = string;
    stringIterator->offset = 0;
    stringIterator->symbol = Nucleus_Interpreter_Symbol_begin(context);
    return stringIterator;
}

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_StringIterator_setInput
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringIterator *stringIterator,
        Nucleus_Interpreter_String *string
    )
{
    stringIterator->string = string;
    stringIterator->offset = 0;
    stringIterator->symbol = Nucleus_Interpreter_Symbol_begin(context);
}

Nucleus_Interpreter_ReturnNonNull() Nucleus_Interpreter_NonNull() Nucleus_Interpreter_String *
Nucleus_Interpreter_StringIterator_getInput
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringIterator *stringIterator
    )
{ return stringIterator->string; }

Nucleus_Interpreter_NonNull() size_t
Nucleus_Interpreter_StringIterator_getOffset
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringIterator *stringIterator
    )
{ return stringIterator->offset; }

Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Symbol
Nucleus_Interpreter_StringIterator_get
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringIterator *stringIterator
    )
{ return stringIterator->symbol; }

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_StringIterator_increment
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringIterator *stringIterator
    )
{
    if (stringIterator->offset < endOffset(context, stringIterator))
    { stringIterator->offset++; updateSymbol(context, stringIterator); }
}

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_StringIterator_decrement
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringIterator *stringIterator
    )
{
    if (stringIterator->offset > beginOffset(context, stringIterator))
    { stringIterator->offset--; updateSymbol(context, stringIterator); }
}
