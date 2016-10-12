#pragma once

#include "Nucleus/Interpreter/Annotations.h"
#include "Nucleus/Interpreter/Status.h"
#include "Nucleus/Interpreter/GC/FinalizeForeignObject.h"
#include "Nucleus/Interpreter/GC/VisitForeignObject.h"
#include "Nucleus/Types/Boolean.h"
#include "Nucleus/Types/HashValue.h"
#include "Nucleus/Types/Natural.h"
#include "Nucleus/Types/Size.h"
#include "Nucleus/Interpreter/GC/FinalizeType.h"

// Forward declaration.
typedef struct Nucleus_Interpreter_GC Nucleus_Interpreter_GC;

/// @brief A GC type.
typedef struct Nucleus_Interpreter_GC_Type Nucleus_Interpreter_GC_Type;

typedef struct Nucleus_Interpreter_GC_Type Nucleus_Interpreter_GC_Type;
struct Nucleus_Interpreter_GC_Type
{
    Nucleus_Interpreter_GC_Type *next;
    Nucleus_HashValue hashValue;
    Nucleus_Natural8 flags;
    Nucleus_Interpreter_GC_FinalizeType *finalizeType;
    union
    {
        struct
        {
            Nucleus_Interpreter_GC_FinalizeForeignObject *finalizeForeignObject;
            Nucleus_Interpreter_GC_VisitForeignObject *visitForeignObject;
            Nucleus_Interpreter_GC_Type *parentType; ///< Pointer to the parent type or a null pointer.
        } foreignType;
        struct
        {
            Nucleus_Size size; ///< Type of the objects the reference objects refer to.
        } basicType;
        struct
        {
            Nucleus_Interpreter_GC_Type *elementType; ///< Type of the objects 
        } arrayType;
    };
}; // struct Nucleus_Interpreter_GC_Type

/// @brief If a type is an array type.
#define Nucleus_Interpreter_GC_Type_Flags_Array (1)

/// @brief If a type is a foreign type.
#define Nucleus_Interpreter_GC_Type_Flags_Foreign (2)

/// @brief Flag indicating a type is a basic type.
#define Nucleus_Interpreter_GC_Type_Flags_Basic (4)

/// @brief Get if a @a (Nucleus_Interpreter_GC_Type) object denotes an array type.
/// @param type a pointer to a @a (Nucleus_Interpreter_GC_Type) object
/// @return @a true if the @a (Nucleus_Interpreter_GC_Type) object pointed to by @a type denotes an array type, @a false otherwise
Nucleus_NonNull() Nucleus_Boolean
Nucleus_Interpreter_GC_Type_isArray
    (
        const Nucleus_Interpreter_GC_Type *type
    );

/// @brief Get if a @a (Nucleus_Interpreter_GC_Type) object denotes a basic type.
/// @param type a pointer to a @a (Nucleus_Interpreter_GC_Type) object
/// @return @a true if the @a (Nucleus_Interpreter_GC_Type) object pointed to by @a type denotes a basic type, @a false otherwise
Nucleus_NonNull() Nucleus_Boolean
Nucleus_Interpreter_GC_Type_isBasic
    (
        const Nucleus_Interpreter_GC_Type *type
    );

/// @brief Get if a @a (Nucleus_Interpreter_GC_Type) object denotes a foreign type.
/// @param type a pointer to a @a (Nucleus_Interpreter_GC_Type) object
/// @return @a true if the @a (Nucleus_Interpreter_GC_Type) object pointed to by @a type denotes a foreign type, @a false otherwise
Nucleus_NonNull() Nucleus_Boolean
Nucleus_Interpreter_GC_Type_isForeign
    (
        const Nucleus_Interpreter_GC_Type *type
    );

/// @internal
/// @brief Initialize the set of types.
/// @return #Nucleus_Interpreter_Status_Success on success, a non-zero status code on failure
Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Status
Nucleus_Interpreter_GC_initializeTypes
    (
        Nucleus_Interpreter_GC *gc
    );

/// @internal
/// @brief Uninitialize the set of types.
Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_GC_uninitializeTypes
    (
        Nucleus_Interpreter_GC *gc
    );

/// @internal
/// @brief Create an array type.
/// @param elementType the type of the element of the array
Nucleus_Interpreter_NonNull(1, 2, 3) Nucleus_Interpreter_Status
Nucleus_Interpreter_GC_getOrCreateArrayType
    (
        Nucleus_Interpreter_GC *gc,
        Nucleus_Interpreter_GC_Type **type,
        Nucleus_Interpreter_GC_Type *elementType,
        Nucleus_Interpreter_GC_FinalizeType *finalizeType
    );

/// @internal
/// @brief Create a basic type.
/// @param size the size, in Bytes, of the values of this scalar type
/// @param finalizeType a pointer to the Nucleus_Interpreter_GC_Type_Finalizer function or a null pointer
Nucleus_Interpreter_NonNull(1, 2) Nucleus_Interpreter_Status
Nucleus_Interpreter_GC_getOrCreateBasicType
    (
        Nucleus_Interpreter_GC *gc,
        Nucleus_Interpreter_GC_Type **type,
        Nucleus_Size size,
        Nucleus_Interpreter_GC_FinalizeType *finalizeType
    );

/// @internal
/// @brief Create a foreign type.
/// @param finalizeType a pointer to the Nucleus_Interpreter_GC_Type_Finalizer function or a null pointer
/// @param finalize a pointer to the Nucleus_Interpreter_GC_Finalize function or a null pointer
/// @param visit a pointer to the Nucleus_Interpreter_GC_Visit function or a null pointer
Nucleus_Interpreter_NonNull(1, 2) Nucleus_Interpreter_Status
Nucleus_Interpreter_GC_getOrCreateForeignType
    (
        Nucleus_Interpreter_GC *gc,
        Nucleus_Interpreter_GC_Type **type,
        Nucleus_Interpreter_GC_Type *parentType,
        Nucleus_Interpreter_GC_FinalizeForeignObject *finalizeForeignObject,
        Nucleus_Interpreter_GC_VisitForeignObject *visitForeignObject,
        Nucleus_Interpreter_GC_FinalizeType *finalizeType
    );
