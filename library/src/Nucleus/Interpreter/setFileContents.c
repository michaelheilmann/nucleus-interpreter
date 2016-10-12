// Copyright (c) Michael Heilmann 2018
// https://github.com/nucleus-interpreter/blob/master/documentation/Nucleus_Interpreter_setFileContents.md
#include "Nucleus/Interpreter/setFileContents.h"

#include "Nucleus/FileSystem.h"
#include "Nucleus/Memory.h"
#include "Nucleus/Interpreter/Context.h"
#include "Nucleus/Interpreter/String.h"
#include "Nucleus/Interpreter/StringBuffer.h"

Nucleus_Interpreter_NonNull() static void
setFileContents
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_String *pathname,
        const char *bytes,
        size_t numberOfBytes
    );

Nucleus_Interpreter_NonNull() static void
setFileContents
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_String *pathname,
        const char *bytes,
        size_t numberOfBytes
    )
{
    // (1) pathname in C-compatible format
    size_t n = Nucleus_Interpreter_String_getNumberOfBytes(context, pathname);
    char *p = Nucleus_Interpreter_Context_acquireScratchSpace(context, n + 1);
    Nucleus_copyMemory(p, Nucleus_Interpreter_String_getBytes(context, pathname), n);
    p[n] = '\0';
    // (2) set file contents
    Nucleus_Interpreter_Status status = (Nucleus_Interpreter_Status)Nucleus_setFileContents(p, bytes, numberOfBytes);
    if (status)
    {
        Nucleus_Interpreter_ProcessContext_setStatus(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context), status);
        Nucleus_Interpreter_ProcessContext_jump(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
    }
}

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_setFileContentsStringBuffer
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_String *pathname,
        Nucleus_Interpreter_StringBuffer *contents
    )
{
    Nucleus_Interpreter_Context_assertNotNull(context, pathname);
    Nucleus_Interpreter_Context_assertNotNull(context, contents);
    setFileContents(context, pathname, Nucleus_Interpreter_StringBuffer_getBytes(context, contents),
                                       Nucleus_Interpreter_StringBuffer_getSize(context, contents));
}

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_setFileContentsString
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_String *pathname,
        Nucleus_Interpreter_String *contents
    )
{
    Nucleus_Interpreter_Context_assertNotNull(context, pathname);
    Nucleus_Interpreter_Context_assertNotNull(context, contents);
    setFileContents(context, pathname, Nucleus_Interpreter_String_getBytes(context, contents),
                                       Nucleus_Interpreter_String_getNumberOfBytes(context, contents));
}
