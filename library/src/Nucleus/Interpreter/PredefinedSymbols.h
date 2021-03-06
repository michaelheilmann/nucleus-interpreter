// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Interpreter/Symbol.h"

#define DEFINE(CNAME, UNAME, VALUE) \
Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Symbol \
Nucleus_Interpreter_Symbol_##CNAME \
    ( \
        Nucleus_Interpreter_Context *context \
    );

#include "Nucleus/Interpreter/UnicodeCodePoints.i"

#undef DEFINE
