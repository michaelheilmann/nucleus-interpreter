#include "Nucleus/Interpreter/TS-private.c.in"

Nucleus_NonNull() Nucleus_Interpreter_Status
Nucleus_Interpreter_initializeTS
    (
        Nucleus_Interpreter_TS *ts
    )
{
    Nucleus_Status status;
    status = Nucleus_allocateArrayMemory((void **)&ts->buckets, 8, sizeof(Nucleus_Interpreter_Type *));
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
    ts->size = 0;
    ts->capacity = leastCapacity;
    for (size_t i = 0, n = leastCapacity; i < n; ++i)
    {
        ts->buckets[i] = NULL;
    }
    return Nucleus_Interpreter_Status_Success;
}

Nucleus_NonNull() void
Nucleus_Interpreter_uninitializeTS
    (
        Nucleus_Interpreter_TS *ts
    )
{
    for (size_t i = 0, n = ts->capacity; i < n; ++i)
    {
        Nucleus_Interpreter_Type **bucket = &(ts->buckets[i]);
        while (*bucket)
        {
            Nucleus_Interpreter_Type *node = *bucket; *bucket = node->next;
            if (node->finalizeType)
            {
                node->finalizeType();
            }
            Nucleus_deallocateMemory(node);
        }
    }
    Nucleus_deallocateMemory(ts->buckets);
    ts->buckets = NULL;
}

Nucleus_Interpreter_NonNull(1, 2, 3) Nucleus_Interpreter_Status
Nucleus_Interpreter_getOrCreateArrayTypeNoError
    (
        Nucleus_Interpreter_TS *ts,
        Nucleus_Interpreter_Type **type,
        Nucleus_Interpreter_Type *elementType,
        Nucleus_Interpreter_FinalizeType *finalizeType
    )
{
    if (Nucleus_Unlikely(!ts || !type || !elementType)) return Nucleus_Interpreter_Status_InvalidArgument;

    Nucleus_Natural8 flags = Nucleus_Interpreter_TypeFlags_Array;

    Nucleus_HashValue hashValue, hashValue1;
    Nucleus_hashNatural8(flags, &hashValue);
    hashValue1 = elementType->hashValue;
    Nucleus_combineHashValues(hashValue, hashValue1, &hashValue);

    Nucleus_Size hashIndex = (hashValue % ts->capacity);
    for (Nucleus_Interpreter_Type *t = ts->buckets[hashIndex]; NULL != t; t = t->next)
    {
        if (t->hashValue == hashValue && t->flags == flags && t->arrayType.elementType == elementType)
        {
            *type = t;
            return Nucleus_Interpreter_Status_Success;
        }
    }

    Nucleus_Interpreter_Type *t;

    Nucleus_Status status  = Nucleus_allocateMemory((void **)&t, sizeof(Nucleus_Interpreter_Type));
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

    t->flags = flags;
    t->finalizeType = finalizeType;
    t->hashValue = hashValue;

    t->arrayType.elementType = elementType;

    t->next = ts->buckets[hashIndex];
    ts->buckets[hashIndex] = t;
    ts->size++;

    maybeResize(ts);

    *type = t;

    return Nucleus_Interpreter_Status_Success;
}

Nucleus_Interpreter_NonNull(1, 2) Nucleus_Interpreter_Status
Nucleus_Interpreter_getOrCreateBasicTypeNoError
    (
        Nucleus_Interpreter_TS *ts,
        Nucleus_Interpreter_Type **type,
        Nucleus_Size size,
        Nucleus_Interpreter_FinalizeType *finalizeType
    )
{
    if (Nucleus_Unlikely(!ts || !type)) return Nucleus_Interpreter_Status_InvalidArgument;

    Nucleus_Natural8 flags = Nucleus_Interpreter_TypeFlags_Basic;

    Nucleus_HashValue hashValue, hashValue1;
    Nucleus_hashSize(size, &hashValue);
    Nucleus_hashNatural8(flags, &hashValue1);
    Nucleus_combineHashValues(hashValue, hashValue1, &hashValue);

    Nucleus_Size hashIndex = (hashValue % ts->capacity);
    for (Nucleus_Interpreter_Type *t = ts->buckets[hashIndex]; NULL != t; t = t->next)
    {
        if (t->hashValue == hashValue && t->flags == flags && t->basicType.size == size)
        {
            *type = t;
            return Nucleus_Interpreter_Status_Success;
        }
    }

    Nucleus_Interpreter_Type *t;

    Nucleus_Status status  = Nucleus_allocateMemory((void **)&t, sizeof(Nucleus_Interpreter_Type));
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

    t->flags = flags;
    t->finalizeType = finalizeType;
    t->hashValue = hashValue;

    t->basicType.size = size;

    t->next = ts->buckets[hashIndex];
    ts->buckets[hashIndex] = t;
    ts->size++;

    maybeResize(ts);

    *type = t;

    return Nucleus_Interpreter_Status_Success;
}

Nucleus_Interpreter_NonNull(1, 2) Nucleus_Interpreter_Status
Nucleus_Interpreter_getOrCreateForeignTypeNoError
    (
        Nucleus_Interpreter_TS *ts,
        Nucleus_Interpreter_Type **type,
        Nucleus_Interpreter_Type *parentType,
        Nucleus_Interpreter_FinalizeForeignObject *finalizeForeignObject,
        Nucleus_Interpreter_VisitForeignObject *visitForeignObject,
        Nucleus_Interpreter_FinalizeType *finalizeType
    )
{
    if (Nucleus_Unlikely(!ts || !type)) return Nucleus_Interpreter_Status_InvalidArgument;

    Nucleus_Natural8 flags = Nucleus_Interpreter_TypeFlags_Foreign;

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
    Nucleus_Size hashIndex = (hashValue % ts->capacity);
    for (Nucleus_Interpreter_Type *t = ts->buckets[hashIndex]; NULL != t; t = t->next)
    {
        if (t->hashValue == hashValue &&
            t->flags == flags &&
            t->foreignType.parentType == parentType &&
            t->foreignType.finalizeForeignObject == finalizeForeignObject &&
            t->foreignType.visitForeignObject == visitForeignObject)
        {
            *type = t;
            return Nucleus_Interpreter_Status_Success;
        }
    }

    Nucleus_Interpreter_Type *t;

    Nucleus_Status status  = Nucleus_allocateMemory((void **)&t, sizeof(Nucleus_Interpreter_Type));
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

    t->flags = flags;
    t->finalizeType = finalizeType;
    t->hashValue = hashValue;

    t->foreignType.parentType = parentType;
    t->foreignType.finalizeForeignObject = finalizeForeignObject;
    t->foreignType.visitForeignObject = visitForeignObject;

    t->next = ts->buckets[hashIndex];
    ts->buckets[hashIndex] = t;
    ts->size++;

    maybeResize(ts);

    *type = t;

    return Nucleus_Interpreter_Status_Success;
}

Nucleus_NonNull() Nucleus_Boolean
Nucleus_Interpreter_isArrayType
    (
        const Nucleus_Interpreter_Type *type
    )
{ return Nucleus_Interpreter_TypeFlags_Array == (type->flags & Nucleus_Interpreter_TypeFlags_Array); }

Nucleus_NonNull() Nucleus_Boolean
Nucleus_Interpreter_isBasicType
    (
        const Nucleus_Interpreter_Type *type
    )
{ return Nucleus_Interpreter_TypeFlags_Basic == (type->flags & Nucleus_Interpreter_TypeFlags_Basic); }

Nucleus_NonNull() Nucleus_Boolean
Nucleus_Interpreter_isForeignType
    (
        const Nucleus_Interpreter_Type *type
    )
{ return Nucleus_Interpreter_TypeFlags_Foreign == (type->flags & Nucleus_Interpreter_TypeFlags_Foreign); }
