#include "Nucleus/Interpreter/GC/Type.h"

#include "Nucleus/Interpreter/GC.h"
#include "Nucleus/Interpreter/GC/Object.h"

#include "Nucleus/Memory.h"
#include "Nucleus/Hash/Natural.h"
#include "Nucleus/Hash/Pointer.h"
#include "Nucleus/Hash/Size.h"
#include "Nucleus/Hash/combineHashValues.h"

static const Nucleus_Size greatestCapacity = Nucleus_Size_Greatest / sizeof(Nucleus_Interpreter_GC_Type);

static const Nucleus_Size leastCapacity = 8;

Nucleus_NonNull() static void
maybeResize
    (
        Nucleus_Interpreter_GC *gc
    );

Nucleus_NonNull() static void
maybeResize
    (
        Nucleus_Interpreter_GC *gc
    )
{
    if (gc->types.size >= gc->types.capacity/2 && gc->types.capacity < greatestCapacity)
    {
        Nucleus_Size oldCapacity = gc->types.capacity;
        Nucleus_Size newCapacity = oldCapacity;
        if (newCapacity < greatestCapacity / 2)
        {
            newCapacity *= 2;
        }
        else
        {
            newCapacity = greatestCapacity;
        }
        Nucleus_Interpreter_GC_Type **oldBuckets = gc->types.buckets;
        Nucleus_Interpreter_GC_Type **newBuckets;
        Nucleus_Status status = Nucleus_allocateArrayMemory((void **)&newBuckets, newCapacity,
                                                            sizeof(Nucleus_Interpreter_GC_Type *));
        if (status) return;
        for (size_t i = 0, n = newCapacity; i < n; ++i)
        {
            newBuckets[i] = NULL;
        }
        for (size_t i = 0, n = oldCapacity; i < n; ++i)
        {
            Nucleus_Interpreter_GC_Type **oldBucket = &(oldBuckets[i]);
            while (*oldBucket)
            {
                Nucleus_Interpreter_GC_Type *node = *oldBucket; *oldBucket = node->next;
                Nucleus_Size newHashIndex = node->hashValue % newCapacity;
                node->next = newBuckets[newHashIndex];
                newBuckets[newHashIndex] = node;
            }
        }
        Nucleus_deallocateMemory(oldBuckets);
        gc->types.buckets = newBuckets;
        gc->types.capacity = newCapacity;
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Nucleus_NonNull() Nucleus_Boolean
Nucleus_Interpreter_GC_Type_isArray
    (
        const Nucleus_Interpreter_GC_Type *type
    )
{ return Nucleus_Interpreter_GC_Type_Flags_Array == (type->flags & Nucleus_Interpreter_GC_Type_Flags_Array); }

Nucleus_NonNull() Nucleus_Boolean
Nucleus_Interpreter_GC_Type_isBasic
    (
        const Nucleus_Interpreter_GC_Type *type
    )
{ return Nucleus_Interpreter_GC_Type_Flags_Basic == (type->flags & Nucleus_Interpreter_GC_Type_Flags_Basic); }

Nucleus_NonNull() Nucleus_Boolean
Nucleus_Interpreter_GC_Type_isForeign
    (
        const Nucleus_Interpreter_GC_Type *type
    )
{ return Nucleus_Interpreter_GC_Type_Flags_Foreign == (type->flags & Nucleus_Interpreter_GC_Type_Flags_Foreign); }

Nucleus_NonNull() Nucleus_Interpreter_Status
Nucleus_Interpreter_GC_initializeTypes
    (
        Nucleus_Interpreter_GC *gc
    )
{
    Nucleus_Status status;
    status = Nucleus_allocateArrayMemory((void **)&gc->types.buckets, 8, sizeof(Nucleus_Interpreter_GC_Type *));
    if (status)
    {
        switch (status)
        {
        case Nucleus_Status_InvalidArgument:
            return Nucleus_Interpreter_Status_InvalidArgument;
        case Nucleus_Status_AllocationFailed:
            return Nucleus_Interpreter_Status_AllocationFailed;
        default:
            return Nucleus_Interpreter_Status_UnreachableCodeReached;
        };
    }
    gc->types.size = 0;
    gc->types.capacity = leastCapacity;
    for (size_t i = 0, n = leastCapacity; i < n; ++i)
    {
        gc->types.buckets[i] = NULL;
    }
    return Nucleus_Status_Success;
}

Nucleus_NonNull() void
Nucleus_Interpreter_GC_uninitializeTypes
    (
        Nucleus_Interpreter_GC *gc
    )
{
    for (size_t i = 0, n = gc->types.capacity; i < n; ++i)
    {
        Nucleus_Interpreter_GC_Type **bucket = &(gc->types.buckets[i]);
        while (*bucket)
        {
            Nucleus_Interpreter_GC_Type *node = *bucket; *bucket = node->next;
            if (node->finalizeType)
            {
                node->finalizeType(gc, node);
            }
            Nucleus_deallocateMemory(node);
        }
    }
    Nucleus_deallocateMemory(gc->types.buckets);
    gc->types.buckets = NULL;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Nucleus_Interpreter_NonNull(1, 2, 3) Nucleus_Interpreter_Status
Nucleus_Interpreter_GC_getOrCreateArrayType
    (
        Nucleus_Interpreter_GC *gc,
        Nucleus_Interpreter_GC_Type **type,
        Nucleus_Interpreter_GC_Type *elementType,
        Nucleus_Interpreter_GC_FinalizeType *finalizeType
    )
{
    if (Nucleus_Unlikely(!gc || !type || !elementType)) return Nucleus_Interpreter_Status_InvalidArgument;

    Nucleus_Natural8 flags = Nucleus_Interpreter_GC_Type_Flags_Array;

    Nucleus_HashValue hashValue, hashValue1;
    Nucleus_hashNatural8(flags, &hashValue);
    hashValue1 = elementType->hashValue;
    Nucleus_combineHashValues(hashValue, hashValue1, &hashValue);

    Nucleus_Size hashIndex = (hashValue % gc->types.capacity);
    for (Nucleus_Interpreter_GC_Type *t = gc->types.buckets[hashIndex]; NULL != t; t = t->next)
    {
        if (t->hashValue == hashValue && t->flags == flags && t->arrayType.elementType == elementType)
        {
            *type = t;
            return Nucleus_Status_Success;
        }
    }

    Nucleus_Interpreter_GC_Type *t;

    Nucleus_Status status  = Nucleus_allocateMemory((void **)&t, sizeof(Nucleus_Interpreter_GC_Type));
    if (status) return status;

    t->flags = flags;
    t->finalizeType = finalizeType;
    t->hashValue = hashValue;

    t->arrayType.elementType = elementType;

    t->next = gc->types.buckets[hashIndex];
    gc->types.buckets[hashIndex] = t;
    gc->types.size++;

    maybeResize(gc);

    *type = t;

    return Nucleus_Interpreter_Status_Success;
}

Nucleus_Interpreter_NonNull(1, 2) Nucleus_Interpreter_Status
Nucleus_Interpreter_GC_getOrCreateBasicType
    (
        Nucleus_Interpreter_GC *gc,
        Nucleus_Interpreter_GC_Type **type,
        Nucleus_Size size,
        Nucleus_Interpreter_GC_FinalizeType *finalizeType
    )
{
    if (Nucleus_Unlikely(!gc || !type)) return Nucleus_Interpreter_Status_InvalidArgument;

    Nucleus_Natural8 flags = Nucleus_Interpreter_GC_Type_Flags_Basic;

    Nucleus_HashValue hashValue, hashValue1;
    Nucleus_hashSize(size, &hashValue);
    Nucleus_hashNatural8(flags, &hashValue1);
    Nucleus_combineHashValues(hashValue, hashValue1, &hashValue);

    Nucleus_Size hashIndex = (hashValue % gc->types.capacity);
    for (Nucleus_Interpreter_GC_Type *t = gc->types.buckets[hashIndex]; NULL != t; t = t->next)
    {
        if (t->hashValue == hashValue && t->flags == flags && t->basicType.size == size)
        {
            *type = t;
            return Nucleus_Status_Success;
        }
    }

    Nucleus_Interpreter_GC_Type *t;

    Nucleus_Status status  = Nucleus_allocateMemory((void **)&t, sizeof(Nucleus_Interpreter_GC_Type));
    if (status) return status;

    t->flags = flags;
    t->finalizeType = finalizeType;
    t->hashValue = hashValue;

    t->basicType.size = size;

    t->next = gc->types.buckets[hashIndex];
    gc->types.buckets[hashIndex] = t;
    gc->types.size++;

    maybeResize(gc);

    *type = t;

    return Nucleus_Interpreter_Status_Success;
}

Nucleus_Interpreter_NonNull(1, 2) Nucleus_Interpreter_Status
Nucleus_Interpreter_GC_getOrCreateForeignType
    (
        Nucleus_Interpreter_GC *gc,
        Nucleus_Interpreter_GC_Type **type,
        Nucleus_Interpreter_GC_Type *parentType,
        Nucleus_Interpreter_GC_FinalizeForeignObject *finalizeForeignObject,
        Nucleus_Interpreter_GC_VisitForeignObject *visitForeignObject,
        Nucleus_Interpreter_GC_FinalizeType *finalizeType
    )
{
    if (Nucleus_Unlikely(!gc || !type)) return Nucleus_Interpreter_Status_InvalidArgument;

    Nucleus_Natural8 flags = Nucleus_Interpreter_GC_Type_Flags_Foreign;

    Nucleus_HashValue hashValue, hashValue1;
    Nucleus_hashPointer(finalizeForeignObject, &hashValue);
    Nucleus_hashPointer(visitForeignObject, &hashValue1);
    Nucleus_combineHashValues(hashValue, hashValue1, &hashValue);
    Nucleus_hashNatural8(flags, &hashValue1);
    Nucleus_combineHashValues(hashValue, hashValue1, &hashValue);
    if (parentType)
    {
        Nucleus_combineHashValues(hashValue, parentType->hashValue, &hashValue);
    }
    Nucleus_Size hashIndex = (hashValue % gc->types.capacity);
    for (Nucleus_Interpreter_GC_Type *t = gc->types.buckets[hashIndex]; NULL != t; t = t->next)
    {
        if (t->hashValue == hashValue &&
            t->flags == flags &&
            t->foreignType.parentType == parentType &&
            t->foreignType.finalizeForeignObject == finalizeForeignObject &&
            t->foreignType.visitForeignObject == visitForeignObject)
        {
            *type = t;
            return Nucleus_Status_Success;
        }
    }

    Nucleus_Interpreter_GC_Type *t;

    Nucleus_Status status  = Nucleus_allocateMemory((void **)&t, sizeof(Nucleus_Interpreter_GC_Type));
    if (status) return status;

    t->flags = flags;
    t->finalizeType = finalizeType;
    t->hashValue = hashValue;

    t->foreignType.parentType = parentType;
    t->foreignType.finalizeForeignObject = finalizeForeignObject;
    t->foreignType.visitForeignObject = visitForeignObject;

    t->next = gc->types.buckets[hashIndex];
    gc->types.buckets[hashIndex] = t;
    gc->types.size++;

    maybeResize(gc);

    *type = t;

    return Nucleus_Interpreter_Status_Success;
}
