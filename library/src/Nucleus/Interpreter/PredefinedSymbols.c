// Copyright (c) Michael Heilmann 2018
#include "Nucleus/Interpreter/PredefinedSymbols.h"

#include "Nucleus/Interpreter/Context.h"
#include "Nucleus/Interpreter/UnicodeCodePoints.h"

#define DEFINE(CNAME, UNAME, VALUE) \
Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Symbol \
Nucleus_Interpreter_Symbol_##CNAME \
    ( \
        Nucleus_Interpreter_Context *context \
    ) \
{ return Nucleus_Interpreter_Symbol_create_uint32(context, Nucleus_Interpreter_##CNAME); }

#include "Nucleus/Interpreter/UnicodeCodePoints.i"

#undef DEFINE
