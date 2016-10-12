// Copyright (c) Michael Heilmann 2018
// https://github.com/nucleus-interpreter/blob/master/documentation/Nucleus_Interpreter_getFileContents.md
#pragma once

#include "Nucleus/Interpreter/Annotations.h"

// Forward declarations.
typedef struct Nucleus_Interpreter_Context Nucleus_Interpreter_Context;
typedef struct Nucleus_Interpreter_String Nucleus_Interpreter_String;
typedef struct Nucleus_Interpreter_StringBuffer Nucleus_Interpreter_StringBuffer;

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_getFileContentsStringBuffer
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_String *pathname,
        Nucleus_Interpreter_StringBuffer *stringBuffer
    );

Nucleus_Interpreter_NonNull() Nucleus_Interpreter_String *
Nucleus_Interpreter_getFileContentsString
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_String *pathname
    );
