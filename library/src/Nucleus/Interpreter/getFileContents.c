// Copyright (c) 2018 Michael Heilmann
// https://github.com/nucleus-interpreter/blob/master/documentation/Nucleus_Interpreter_getFileContents.md
#include "Nucleus/Interpreter/getFileContents.h"

#include "Nucleus/FileSystem.h"
#include "Nucleus/Memory.h"
#include "Nucleus/Interpreter/Context.h"
#include "Nucleus/Interpreter/String.h"
#include "Nucleus/Interpreter/JumpTarget.h"
#include "Nucleus/Interpreter/StringBuffer.h"

typedef struct Context
{
    Nucleus_Interpreter_Context *context;
    Nucleus_Interpreter_StringBuffer *stringBuffer;
} Context;

Nucleus_NoError() Nucleus_NonNull() static Nucleus_Status
Callback
    (
        void *object,
        const char *bytes,
        size_t numberOfBytes
    );

Nucleus_NoError() Nucleus_NonNull() static Nucleus_Status
Callback
    (
        void *object,
        const char *bytes,
        size_t numberOfBytes
    )
{
    Context *context = (Context *)object;
    Nucleus_Interpreter_JumpTarget jt;
    Nucleus_Interpreter_ProcessContext_pushJumpTarget(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context->context), &jt);
    if (!setjmp(jt.environment))
    {
        Nucleus_Interpreter_StringBuffer_append(context->context, context->stringBuffer, bytes, numberOfBytes);
        Nucleus_Interpreter_ProcessContext_popJumpTarget(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context->context));
    }
    else
    {
        Nucleus_Interpreter_ProcessContext_popJumpTarget(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
        return Nucleus_Interpreter_ProcessContext_getStatus(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
    }
    return Nucleus_Interpreter_Status_Success;
}

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_getFileContentsStringBuffer
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_String *pathname,
        Nucleus_Interpreter_StringBuffer *stringBuffer
    )
{
    Nucleus_Interpreter_Context_assertNotNull(context, pathname);
    Nucleus_Interpreter_Context_assertNotNull(context, stringBuffer);

    // (1) pathname in C-compatible format
    size_t n = Nucleus_Interpreter_String_getNumberOfBytes(NUCLEUS_INTERPRETER_CONTEXT(context), pathname);
    char *p = Nucleus_Interpreter_Context_acquireScratchSpace(context, n + 1);
    Nucleus_copyMemory(p, Nucleus_Interpreter_String_getBytes(NUCLEUS_INTERPRETER_CONTEXT(context), pathname), n);
    p[n] = '\0';

    // (2) read file contents
    Context ctxt;
    ctxt.context = context;
    ctxt.stringBuffer = stringBuffer;
    Nucleus_getFileContentsExtendedCallbackFunction *cb = &Callback;
    Nucleus_Interpreter_Status status = (Nucleus_Interpreter_Status)Nucleus_getFileContentsExtended(p, &ctxt, cb);
    Nucleus_Interpreter_Context_relinquishScratchSpace(context, p);
    if (status)
    {
        Nucleus_Interpreter_ProcessContext_setStatus(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context), status);
        Nucleus_Interpreter_ProcessContext_jump(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
    }
}

Nucleus_Interpreter_NonNull() Nucleus_Interpreter_String *
Nucleus_Interpreter_getFileContentsString
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_String *pathname
    )
{
    Nucleus_Interpreter_Context_assertNotNull(context, pathname);

    Nucleus_Interpreter_JumpTarget eh;

    // (1) Provide a string buffer.
    Nucleus_Interpreter_StringBuffer stringBuffer;
    Nucleus_Interpreter_StringBuffer_initialize(context, &stringBuffer, 256);

    // (2) Read the file contents into the string buffer.
    Nucleus_Interpreter_ProcessContext_pushJumpTarget(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context), &eh);
    if (!setjmp(eh.environment))
    {
        Nucleus_Interpreter_getFileContentsStringBuffer(context, pathname, &stringBuffer);
        Nucleus_Interpreter_ProcessContext_popJumpTarget(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
    }
    else
    {
        Nucleus_Interpreter_ProcessContext_popJumpTarget(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
        Nucleus_Interpreter_StringBuffer_uninitialize(context, &stringBuffer);
        Nucleus_Interpreter_ProcessContext_jump(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
    }

    // (3) Convert string buffer to string.
    Nucleus_Interpreter_String *string = NULL;
    Nucleus_Interpreter_ProcessContext_pushJumpTarget(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context), &eh);
    if (!setjmp(eh.environment))
    {
        string = Nucleus_Interpreter_String_create(NUCLEUS_INTERPRETER_CONTEXT(context), Nucleus_Interpreter_StringBuffer_getBytes(context, &stringBuffer),
                                                   Nucleus_Interpreter_StringBuffer_getSize(context, &stringBuffer));
        Nucleus_Interpreter_ProcessContext_popJumpTarget(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
    }
    else
    {
        Nucleus_Interpreter_ProcessContext_popJumpTarget(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
        Nucleus_Interpreter_StringBuffer_uninitialize(context, &stringBuffer);
        Nucleus_Interpreter_ProcessContext_jump(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
    }
    Nucleus_Interpreter_StringBuffer_uninitialize(context, &stringBuffer);

    // Return the string.
    return string;
}
