#pragma once

#include "Nucleus/Interpreter/Annotations.h"
#include "Nucleus/Interpreter/Status.h"
//
#include "Nucleus/Types/Boolean.h"
#include "Nucleus/Types/HashValue.h"
#include "Nucleus/Types/Natural.h"
#include "Nucleus/Types/Size.h"
//
#include "Nucleus/Interpreter/GC/FinalizeForeignObject.h"
#include "Nucleus/Interpreter/GC/FinalizeType.h"
#include "Nucleus/Interpreter/GC/VisitForeignObject.h"


/// @brief If a type is an array type.
#define Nucleus_Interpreter_TypeFlags_Array (1)

/// @brief If a type is a foreign type.
#define Nucleus_Interpreter_TypeFlags_Foreign (2)

/// @brief Flag indicating a type is a basic type.
#define Nucleus_Interpreter_TypeFlags_Basic (4)


/// @brief A type.
typedef struct Nucleus_Interpreter_Type Nucleus_Interpreter_Type;

struct Nucleus_Interpreter_Type
{
    Nucleus_Interpreter_Type *next;
    Nucleus_HashValue hashValue;
    Nucleus_Natural8 flags;
    Nucleus_Interpreter_FinalizeType *finalizeType;
    union
    {
        struct
        {
            Nucleus_Interpreter_FinalizeForeignObject *finalizeForeignObject;
            Nucleus_Interpreter_VisitForeignObject *visitForeignObject;
            Nucleus_Interpreter_Type *parentType; ///< Pointer to the parent type or a null pointer.
        } foreignType;
        struct
        {
            Nucleus_Size size; ///< Type of the objects the reference objects refer to.
        } basicType;
        struct
        {
            Nucleus_Interpreter_Type *elementType; ///< Type of the objects 
        } arrayType;
    };
}; // struct Nucleus_Interpreter_Type

/// @brief A type.
typedef struct Nucleus_Interpreter_TS Nucleus_Interpreter_TS;

struct Nucleus_Interpreter_TS
{
    Nucleus_Interpreter_Type **buckets;
    size_t size;
    size_t capacity;
}; // struct Nucleus_Interpreter_TS

/// @internal
/// @brief Initialize the set of types.
/// @return #Nucleus_Interpreter_Status_Success on success, a non-zero status code on failure
Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Status
Nucleus_Interpreter_initializeTS
    (
        Nucleus_Interpreter_TS *ts
    );

/// @internal
/// @brief Uninitialize the set of types.
Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_uninitializeTS
    (
        Nucleus_Interpreter_TS *ts
    );

/// @internal
/// @brief Create an array type.
/// @param elementType the type of the element of the array
Nucleus_Interpreter_NonNull(1, 2, 3) Nucleus_Interpreter_Status
Nucleus_Interpreter_getOrCreateArrayTypeNoError
    (
        Nucleus_Interpreter_TS *ts,
        Nucleus_Interpreter_Type **type,
        Nucleus_Interpreter_Type *elementType,
        Nucleus_Interpreter_FinalizeType *finalizeType
    );

/// @internal
/// @brief Create a basic type.
/// @param size the size, in Bytes, of the values of this scalar type
/// @param finalizeType a pointer to the Nucleus_Interpreter_Type_Finalizer function or a null pointer
Nucleus_Interpreter_NonNull(1, 2) Nucleus_Interpreter_Status
Nucleus_Interpreter_getOrCreateBasicTypeNoError
    (
        Nucleus_Interpreter_TS *ts,
        Nucleus_Interpreter_Type **type,
        Nucleus_Size size,
        Nucleus_Interpreter_FinalizeType *finalizeType
    );

/// @internal
/// @brief Create a foreign type.
/// @param finalizeType a pointer to the Nucleus_Interpreter_Type_Finalizer function or a null pointer
/// @param finalize a pointer to the Nucleus_Interpreter_GC_Finalize function or a null pointer
/// @param visit a pointer to the Nucleus_Interpreter_GC_Visit function or a null pointer
Nucleus_Interpreter_NonNull(1, 2) Nucleus_Interpreter_Status
Nucleus_Interpreter_getOrCreateForeignTypeNoError
    (
        Nucleus_Interpreter_TS *ts,
        Nucleus_Interpreter_Type **type,
        Nucleus_Interpreter_Type *parentType,
        Nucleus_Interpreter_FinalizeForeignObject *finalizeForeignObject,
        Nucleus_Interpreter_VisitForeignObject *visitForeignObject,
        Nucleus_Interpreter_FinalizeType *finalizeType
    );

/// @brief Get if a @a (Nucleus_Interpreter_Type) object denotes an array type.
/// @param type a pointer to a @a (Nucleus_Interpreter_Type) object
/// @return @a true if the @a (Nucleus_Interpreter_Type) object pointed to by @a type denotes an array type, @a false otherwise
Nucleus_NonNull() Nucleus_Boolean
Nucleus_Interpreter_isArrayType
    (
        const Nucleus_Interpreter_Type *type
    );

/// @brief Get if a @a (Nucleus_Interpreter_Type) object denotes a basic type.
/// @param type a pointer to a @a (Nucleus_Interpreter_Type) object
/// @return @a true if the @a (Nucleus_Interpreter_Type) object pointed to by @a type denotes a basic type, @a false otherwise
Nucleus_NonNull() Nucleus_Boolean
Nucleus_Interpreter_isBasicType
    (
        const Nucleus_Interpreter_Type *type
    );

/// @brief Get if a @a (Nucleus_Interpreter_Type) object denotes a foreign type.
/// @param type a pointer to a @a (Nucleus_Interpreter_Type) object
/// @return @a true if the @a (Nucleus_Interpreter_Type) object pointed to by @a type denotes a foreign type, @a false otherwise
Nucleus_NonNull() Nucleus_Boolean
Nucleus_Interpreter_isForeignType
    (
        const Nucleus_Interpreter_Type *type
    );
