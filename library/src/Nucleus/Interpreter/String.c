// Copyright (c) Michael Heilmann 2018
// Interned strings.
#include "Nucleus/Interpreter/String-private.c.in"

#include "Nucleus/Interpreter/Context.h"
#include "Nucleus/Interpreter/JumpTarget.h"

#include "Nucleus/Hash/Memory.h"
#include "Nucleus/Memory.h"

Nucleus_Interpreter_NonNull() static unsigned int
Nucleus_Interpreter_hashMemory
    (
        Nucleus_Interpreter_Context *context,
        const void *p,
        size_t n
    );

Nucleus_Interpreter_NonNull() static unsigned int
Nucleus_Interpreter_hashMemory
    (
        Nucleus_Interpreter_Context *context,
        const void *p,
        size_t n
    )
{
    unsigned int hv;
    Nucleus_hashMemory(p, n, &hv);
    return hv;
}

typedef struct LookupResult
{
    Nucleus_Interpreter_String *string;
    size_t hashValue;
    size_t hashIndex;
} LookupResult;

Nucleus_Interpreter_NonNull() static LookupResult
lookup
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringHeap *stringHeap,
        const char *bytes,
        size_t numberOfBytes
    )
{
    unsigned int hashValue = Nucleus_Interpreter_hashMemory(context, bytes, numberOfBytes);
    unsigned int hashIndex = hashValue % stringHeap->capacity;
    for (Nucleus_Interpreter_GC_Tag *tag = stringHeap->buckets[hashIndex]; NULL != tag; tag = tag->next)
    {
        Nucleus_Interpreter_String *string = tag2Address(tag);
        if (hashValue == string->hashValue && numberOfBytes == string->numberOfBytes)
        {
            bool result = false;
            Nucleus_compareMemory(bytes, string->bytes, numberOfBytes, &result);
            if (result)
            {
                return (LookupResult) { .string = string, .hashValue = hashValue, .hashIndex = hashIndex };
            }
        }
    }
    return (LookupResult) { .string = NULL, .hashValue = hashValue, .hashIndex = hashIndex };
}

Nucleus_Interpreter_NonNull() static void
create
    (
        Nucleus_Interpreter_Context *context,
        const char *bytes,
        size_t numberOfBytes,
        LookupResult *lookupResult
    );

Nucleus_Interpreter_NonNull() static void
create
    (
        Nucleus_Interpreter_Context *context,
        const char *bytes,
        size_t numberOfBytes,
        LookupResult *lookupResult
    )
{
    Nucleus_Interpreter_GC_Tag *tag;
    Nucleus_Interpreter_Status status;
    status = Nucleus_Interpreter_GC_allocateManaged(&NUCLEUS_INTERPRETER_PROCESSCONTEXT(context)->gc,
                                                    &tag,
                                                    sizeof(Nucleus_Interpreter_String) + numberOfBytes,
                                                    &context->stringHeap.buckets[lookupResult->hashIndex]);
    Nucleus_Interpreter_String *string = tag2Address(tag);
    string->numberOfBytes = numberOfBytes;
    string->hashValue = lookupResult->hashValue;
    Nucleus_copyMemory(string->bytes, bytes, numberOfBytes);
    context->stringHeap.size++;
    lookupResult->string = string;
}

Nucleus_Interpreter_NonNull() Nucleus_Interpreter_String *
Nucleus_Interpreter_String_create
    (
        Nucleus_Interpreter_Context *context,
        const char *bytes,
        size_t numberOfBytes
    )
{
    Nucleus_Interpreter_Context_assertNotNull(context, bytes);
    LookupResult lookupResult = lookup(NUCLEUS_INTERPRETER_CONTEXT(context),
                                       &NUCLEUS_INTERPRETER_CONTEXT(context)->stringHeap,
                                       bytes, numberOfBytes);
    if (lookupResult.string) return lookupResult.string;
    create(NUCLEUS_INTERPRETER_CONTEXT(context), bytes, numberOfBytes, &lookupResult);
    return lookupResult.string;
}

Nucleus_Interpreter_NonNull() bool
Nucleus_Interpreter_String_equalTo
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_String *first,
        Nucleus_Interpreter_String *second
    )
{
    Nucleus_Interpreter_Context_assertNotNull(context, first);
    Nucleus_Interpreter_Context_assertNotNull(context, second);
    return first == second;
}

Nucleus_Interpreter_ReturnNonNull() Nucleus_Interpreter_NonNull() Nucleus_Interpreter_String *
Nucleus_Interpreter_String_concatenate
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_String *first,
        Nucleus_Interpreter_String *second
    )
{
    Nucleus_Interpreter_Context_assertNotNull(context, first);
    Nucleus_Interpreter_Context_assertNotNull(context, second);
    size_t numberOfBytes = first->numberOfBytes + second->numberOfBytes;
    char *bytes = Nucleus_Interpreter_Context_acquireScratchSpace(context, numberOfBytes);
    Nucleus_copyMemory(bytes + 0, first->bytes, first->numberOfBytes);
    Nucleus_copyMemory(bytes + first->numberOfBytes, second->bytes, second->numberOfBytes);
    LookupResult lookupResult = lookup(NUCLEUS_INTERPRETER_CONTEXT(context),
                                       &NUCLEUS_INTERPRETER_CONTEXT(context)->stringHeap, bytes, numberOfBytes);
    if (lookupResult.string) return lookupResult.string;
    Nucleus_Interpreter_JumpTarget jt;
    Nucleus_Interpreter_ProcessContext_pushJumpTarget(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context), &jt);
    if (!setjmp(jt.environment))
    {
        create(NUCLEUS_INTERPRETER_CONTEXT(context), bytes, numberOfBytes, &lookupResult);
        Nucleus_Interpreter_ProcessContext_popJumpTarget(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
    }
    else
    {
        Nucleus_Interpreter_ProcessContext_popJumpTarget(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
        Nucleus_Interpreter_Context_relinquishScratchSpace(context, bytes);
        Nucleus_Interpreter_ProcessContext_jump(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
    }
    Nucleus_Interpreter_Context_relinquishScratchSpace(context, bytes);
    return lookupResult.string;
}

Nucleus_Interpreter_NonNull() size_t
Nucleus_Interpreter_String_getNumberOfBytes
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_String *string
    )
{ return string->numberOfBytes; }

Nucleus_Interpreter_ReturnNonNull() Nucleus_Interpreter_NonNull() const char *
Nucleus_Interpreter_String_getBytes
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_String *string
    )
{ return string->bytes; }
