// Copyright (c) Michael Heilmann 2018
#include "Nucleus/Interpreter/GC/Object.h"
#include "Nucleus/Interpreter/GC.h"
#include "Nucleus/Interpreter/GC/Type.h"
#include "Nucleus/SafeArithmeticOperations.h"
#include <stdint.h> // For SIZE_MAX.

Nucleus_Interpreter_GC_Tag *
address2Tag
    (
        void *adr
    )
{
    return (Nucleus_Interpreter_GC_Tag *)(((char *)adr) - sizeof(Nucleus_Interpreter_GC_Tag));
}

void *
tag2Address
    (
        Nucleus_Interpreter_GC_Tag *tag
    )
{
    return (void *)(tag + 1);
}

Nucleus_Interpreter_GC_ArrayTag *
tag2ArrayTag
    (
        Nucleus_Interpreter_GC_Tag *tag
    )
{
    return (Nucleus_Interpreter_GC_ArrayTag *)(tag - 1);
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Nucleus_Interpreter_NoError() Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_GC_Tag_lock
    (
        Nucleus_Interpreter_GC_Tag *tag
    )
{ tag->lockCount++; }

Nucleus_Interpreter_NoError() Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_GC_Tag_unlock
    (
        Nucleus_Interpreter_GC_Tag *tag
    )
{ tag->lockCount--; }

Nucleus_Interpreter_NoError() Nucleus_Interpreter_NonNull() bool
Nucleus_Interpreter_GC_Tag_isLocked
    (
        Nucleus_Interpreter_GC_Tag *tag
    )
{ return 0 != tag->lockCount; }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Nucleus_Interpreter_NoError() Nucleus_Interpreter_NonNull() Nucleus_Interpreter_GC_Type *
Nucleus_Interpreter_GC_Tag_getType
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_GC_Tag *tag
    )
{ return tag->type; }

Nucleus_Interpreter_NoError() Nucleus_Interpreter_NonNull(1, 2) void
Nucleus_Interpreter_GC_Tag_setType
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_GC_Tag *tag,
        Nucleus_Interpreter_GC_Type *type
    )
{ tag->type = type; }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Nucleus_Interpreter_NonNull() bool
Nucleus_Interpreter_GC_Tag_isGray
    (
        const Nucleus_Interpreter_GC_Tag *tag
    )
{ return Nucleus_Interpreter_GC_Color_Gray == (tag->flags & Nucleus_Interpreter_GC_Color_Gray); }

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_GC_Tag_setGray
    (
        Nucleus_Interpreter_GC_Tag *tag
    )
{ tag->flags = Nucleus_Interpreter_GC_Color_Gray; }

Nucleus_Interpreter_NonNull() bool
Nucleus_Interpreter_GC_Tag_isBlack
    (
        const Nucleus_Interpreter_GC_Tag *tag
    )
{ return Nucleus_Interpreter_GC_Color_Black == (tag->flags & Nucleus_Interpreter_GC_Color_Black); }

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_GC_Tag_setBlack
    (
        Nucleus_Interpreter_GC_Tag *tag
    )
{ tag->flags = Nucleus_Interpreter_GC_Color_Black; }

Nucleus_Interpreter_NonNull() bool
Nucleus_Interpreter_GC_Tag_isWhite
    (
        const Nucleus_Interpreter_GC_Tag *tag
    )
{ return Nucleus_Interpreter_GC_Color_White == (tag->flags & Nucleus_Interpreter_GC_Color_White); }

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_GC_Tag_setWhite
    (
        Nucleus_Interpreter_GC_Tag *tag
    )
{ tag->flags = Nucleus_Interpreter_GC_Color_White; }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Status
Nucleus_Interpreter_GC_allocateManaged
    (
        Nucleus_Interpreter_GC *gc,
        Nucleus_Interpreter_GC_Tag **tag,
        size_t size,
        Nucleus_Interpreter_GC_Tag **list
    )
{
    if (!tag || !list) return Nucleus_Interpreter_Status_InvalidArgument;
    Nucleus_Interpreter_GC_Tag *tag1;
    if (SIZE_MAX - sizeof(Nucleus_Interpreter_GC_Tag) < size)
    {
        return Nucleus_Interpreter_Status_Overflow;
    }
    Nucleus_Interpreter_Status status = Nucleus_Interpreter_GC_allocate(gc,
                                                                        (void **)&tag1,
                                                                        sizeof(Nucleus_Interpreter_GC_Tag) + size);
    if (status)
    {
        return Nucleus_Interpreter_Status_AllocationFailed;
    }
    Nucleus_Interpreter_GC_Tag_setWhite(tag1);
    tag1->next = *list; *list = tag1;
    *tag = tag1;
    return Nucleus_Interpreter_Status_Success;
}

Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Status
Nucleus_Interpreter_GC_allocateManagedArray
    (
        Nucleus_Interpreter_GC *gc,
        Nucleus_Interpreter_GC_Tag **tag,
        size_t numberOfElements,
        Nucleus_Interpreter_GC_Type *arrayType,
        Nucleus_Interpreter_GC_Tag **list
    )
{
    if (Nucleus_Unlikely(!tag || !list || !arrayType || !Nucleus_Interpreter_GC_Type_isArray(arrayType)))
    { return Nucleus_Interpreter_Status_InvalidArgument; }
    Nucleus_Status nucleusStatus;
    // Compute the tag size in Bytes.
    size_t tagSizeInBytes = sizeof(Nucleus_Interpreter_GC_ArrayTag) + sizeof(Nucleus_Interpreter_GC_Tag);
    // Compute the element size in Bytes.
    Nucleus_Interpreter_GC_Type *elementType = arrayType->arrayType.elementType;
    size_t elementSizeInBytes;
    if (Nucleus_Interpreter_GC_Type_isArray(elementType) || Nucleus_Interpreter_GC_Type_isForeign(elementType))
    {
        elementSizeInBytes = sizeof(void *);
    }
    else if (Nucleus_Interpreter_GC_Type_isBasic(elementType))
    {
        elementSizeInBytes = elementType->basicType.size;
    }
    // Compute the array size in Bytes.
    size_t arraySizeInBytes;
    nucleusStatus = Nucleus_safeMul(elementSizeInBytes, numberOfElements, &arraySizeInBytes);
    if (nucleusStatus) 
    {
        switch (nucleusStatus)
        {
            case Nucleus_Status_Overflow:
                return Nucleus_Interpreter_Status_Overflow;
            default:
                return Nucleus_Interpreter_Status_InternalError;
        };
    };
    // Compute the allocation size in Bytes.
    size_t sizeInBytes;
    nucleusStatus = Nucleus_safeAdd(tagSizeInBytes, arraySizeInBytes, &sizeInBytes);
    if (nucleusStatus) 
    {
        switch (nucleusStatus)
        {
            case Nucleus_Status_Overflow:
                return Nucleus_Interpreter_Status_Overflow;
            default:
                return Nucleus_Interpreter_Status_InternalError;
        };
    };

    Nucleus_Interpreter_GC_Tag *tag1;
    Nucleus_Interpreter_Status status = Nucleus_Interpreter_GC_allocate(gc, (void **)&tag1, sizeInBytes);
    if (status) return status;
    Nucleus_Interpreter_GC_Tag_setWhite(tag1);
    tag1->next = *list; *list = tag1;
    *tag = tag1;

    return Nucleus_Interpreter_Status_Success;
}
