/// @author Michael Heilmann
/// @copyright Copyright (c) Michael Heilmann 2017, 2018
#include "Nucleus/Interpreter/StringBuffer.h"

#include "Nucleus/Interpreter/Context.h"
#include "Nucleus/Memory.h"

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_StringBuffer_initialize
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringBuffer *stringBuffer,
        size_t initialCapacity
    )
{
    Nucleus_Interpreter_Context_assertNotNull(context, stringBuffer);
    stringBuffer->array = Nucleus_Interpreter_ProcessContext_allocateArray(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context),
                                                                        initialCapacity, sizeof(char));
    stringBuffer->size = 0;
    stringBuffer->capacity = initialCapacity;
}

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_StringBuffer_uninitialize
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringBuffer *stringBuffer
    )
{
    Nucleus_Interpreter_ProcessContext_deallocate(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context), stringBuffer->array);
    stringBuffer->array = NULL;
}

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_StringBuffer_ensureFreeCapacity
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringBuffer *stringBuffer,
        size_t requiredFreeCapacity
    )
{
    Nucleus_Interpreter_Context_assertNotNull(context, stringBuffer);
    size_t availableFreeCapacity = stringBuffer->capacity - stringBuffer->size;
    if (availableFreeCapacity < requiredFreeCapacity)
    {
        size_t additionalCapacity = requiredFreeCapacity - availableFreeCapacity;
        size_t oldCapacity = stringBuffer->capacity;
        size_t newCapacity = oldCapacity + additionalCapacity;
        char *oldArray = stringBuffer->array;
        char *newArray = Nucleus_Interpreter_ProcessContext_allocateArray(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context),
                                                                       newCapacity, sizeof(char));
        Nucleus_copyArrayMemory(newArray, oldArray, oldCapacity, sizeof(char));
        stringBuffer->array = newArray;
        Nucleus_Interpreter_ProcessContext_deallocate(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context), oldArray);
        stringBuffer->capacity = newCapacity;
    }
}

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_StringBuffer_append
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringBuffer *stringBuffer,
        const char *bytes,
        size_t numberOfBytes
    )
{
    Nucleus_Interpreter_Context_assertNotNull(context, stringBuffer);
    Nucleus_Interpreter_StringBuffer_insert(context, stringBuffer, bytes, numberOfBytes, stringBuffer->size);
}

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_StringBuffer_prepend
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringBuffer *stringBuffer,
        const char *bytes,
        size_t numberOfBytes
    )
{
    Nucleus_Interpreter_Context_assertNotNull(context, stringBuffer);
    Nucleus_Interpreter_StringBuffer_insert(context, stringBuffer, bytes, numberOfBytes, 0);
}

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_StringBuffer_insert
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringBuffer *stringBuffer,
        const char *bytes,
        size_t numberOfBytes,
        size_t index
    )
{
    Nucleus_Interpreter_Context_assertNotNull(context, stringBuffer);
    Nucleus_Interpreter_Context_assertNotNull(context, bytes);
    if (index > stringBuffer->size)
    {
        Nucleus_Interpreter_Context_raiseError(context, Nucleus_Interpreter_Status_InvalidArgument);
    }
    if (numberOfBytes == 0)
    {
        return;
    }
    Nucleus_Interpreter_StringBuffer_ensureFreeCapacity(context, stringBuffer, numberOfBytes);
    Nucleus_copyMemory(stringBuffer->array + index, stringBuffer->array + index + numberOfBytes, numberOfBytes);
    Nucleus_copyMemory(stringBuffer->array + index, bytes, numberOfBytes);
    stringBuffer->size += numberOfBytes;
}

Nucleus_Interpreter_NonNull() const char *
Nucleus_Interpreter_StringBuffer_getBytes
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringBuffer *stringBuffer
    )
{ return stringBuffer->array; }

Nucleus_Interpreter_NonNull() size_t
Nucleus_Interpreter_StringBuffer_getSize
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringBuffer *stringBuffer
    )
{ return stringBuffer->size; }

Nucleus_Interpreter_NonNull() size_t
Nucleus_Interpreter_StringBuffer_getCapacity
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringBuffer *stringBuffer
    )
{ return stringBuffer->capacity; }

Nucleus_Interpreter_NonNull() size_t
Nucleus_Interpreter_StringBuffer_getFreeCapacity
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringBuffer *stringBuffer
    )
{ return stringBuffer->capacity - stringBuffer->size; }

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_StringBuffer_clear
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringBuffer *stringBuffer
    )
{ stringBuffer->size = 0; }
