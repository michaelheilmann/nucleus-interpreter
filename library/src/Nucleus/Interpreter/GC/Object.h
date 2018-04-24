// Copyright (c) Michael Heilmann 2018
#pragma once

#include "Nucleus/Interpreter/Annotations.h"
#include "Nucleus/Interpreter/Status.h"
#include "Nucleus/Interpreter/GC/FinalizeForeignObject.h"
#include "Nucleus/Interpreter/GC/VisitForeignObject.h"
#include "Nucleus/Types/Boolean.h"
#include "Nucleus/Types/Size.h"
#include "Nucleus/Types/Natural.h"
#include "Nucleus/Types/HashValue.h"

#define Nucleus_Interpreter_GC_Version_Major (0)
#define Nucleus_Interpreter_GC_Version_Minor (1)

#define Nucleus_Interpreter_GC_Version_GreaterThanOrEqualTo(major, minor) \
    ((Nucleus_Interpreter_GC_Version_Major > (major)) || \
        ((Nucleus_Interpreter_GC_Version_Major == (major)) && (Nucleus_Interpreter_GC_Version_Minor >= (minor))))

// Forward declarations.
typedef struct Nucleus_Interpreter_GC Nucleus_Interpreter_GC;
typedef struct Nucleus_Interpreter_Type Nucleus_Interpreter_Type;
typedef struct Nucleus_Interpreter_Context Nucleus_Interpreter_Context;


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @ingroup gc
/// @internal
/// @brief Unconditionally cast a @a (Nucleus_Interpreter_GC_Object) or derived pointer to a @a (Nucleus_Interpreter_GC_Object) pointer.
#define NUCLEUS_INTERPRETER_GC_OBJECT(pointer) ((Nucleus_Interpreter_GC_Object *)(pointer))

/// @ingroup gc
/// @internal
/// @brief Base type of all GC objects.
typedef struct Nucleus_Interpreter_GC_Object Nucleus_Interpreter_GC_Object;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define Nucleus_Interpreter_GC_Color_Black (1)

#define Nucleus_Interpreter_GC_Color_White (2)

#define Nucleus_Interpreter_GC_Color_Gray (Nucleus_Interpreter_GC_Color_Black | Nucleus_Interpreter_GC_Color_White)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// The tag with which the GC prefixes allocated memory.
typedef struct Nucleus_Interpreter_GC_Tag Nucleus_Interpreter_GC_Tag;

struct Nucleus_Interpreter_GC_Tag
{
    Nucleus_Interpreter_GC_Tag *next;
    char flags;
    Nucleus_Size lockCount;
    Nucleus_Interpreter_GC_Tag *gray;
    Nucleus_Interpreter_Type *type;
}; // struct Nucleus_Interpreter_GC_Tag

// The tag with which the GC prefixes allocated array memory.
// This tag preceeds the Nucleus_Interpreter_GC_Tag.
typedef struct Nucleus_Interpreter_GC_ArrayTag Nucleus_Interpreter_GC_ArrayTag;

struct Nucleus_Interpreter_GC_ArrayTag
{
    Nucleus_Size length; ///< The length of the array i.e. its number of elements. @a 0 is a valid length.
}; // struct Nucleus_Interpreter_GC_ArrayTag

// TODO: Rename to Nucleus_Interpreter_GC_adrToTag
Nucleus_Interpreter_GC_Tag *
address2Tag
    (
        void *adr
    );

// TODO: Rename to Nucleus_Interpreter_GC_tag2Adr
void *
tag2Address
    (
        Nucleus_Interpreter_GC_Tag *tag
    );

Nucleus_Interpreter_GC_ArrayTag *
tag2ArrayTag
    (
        Nucleus_Interpreter_GC_Tag *tag
    );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// TODO Remove this.
struct Nucleus_Interpreter_GC_Object
{
    int dummy;
}; // struct Nucleus_Interpreter_GC_Object

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Nucleus_Interpreter_NoError() Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_GC_Tag_lock
    (
        Nucleus_Interpreter_GC_Tag *tag
    );

Nucleus_Interpreter_NoError() Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_GC_Tag_unlock
    (
        Nucleus_Interpreter_GC_Tag *tag
    );

Nucleus_Interpreter_NoError() Nucleus_Interpreter_NonNull() bool
Nucleus_Interpreter_GC_Tag_isLocked
    (
        Nucleus_Interpreter_GC_Tag *tag
    );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Nucleus_Interpreter_NoError() Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Type *
Nucleus_Interpreter_GC_Tag_getType
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_GC_Tag *tag
    );

Nucleus_Interpreter_NoError() Nucleus_Interpreter_NonNull(1, 2) void
Nucleus_Interpreter_GC_Tag_setType
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_GC_Tag *tag,
        Nucleus_Interpreter_Type *type
    );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Nucleus_Interpreter_NonNull() bool
Nucleus_Interpreter_GC_Tag_isGray
    (
        const Nucleus_Interpreter_GC_Tag *tag
    );

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_GC_Tag_setGray
    (
        Nucleus_Interpreter_GC_Tag *tag
    );

Nucleus_Interpreter_NonNull() bool
Nucleus_Interpreter_GC_Tag_isBlack
    (
        const Nucleus_Interpreter_GC_Tag *tag
    );

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_GC_Tag_setBlack
    (
        Nucleus_Interpreter_GC_Tag *tag
    );

Nucleus_Interpreter_NonNull() bool
Nucleus_Interpreter_GC_Tag_isWhite
    (
        const Nucleus_Interpreter_GC_Tag *tag
    );

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_GC_Tag_setWhite
    (
        Nucleus_Interpreter_GC_Tag *tag
    );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Status
Nucleus_Interpreter_GC_allocateManaged
    (
        Nucleus_Interpreter_GC *gc,
        Nucleus_Interpreter_GC_Tag **tag,
        Nucleus_Size size,
        Nucleus_Interpreter_GC_Tag **list
    );

Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Status
Nucleus_Interpreter_GC_allocateManagedArray
    (
        Nucleus_Interpreter_GC *gc,
        Nucleus_Interpreter_GC_Tag **tag,
        Nucleus_Size numberOfElements,
        Nucleus_Interpreter_Type *arrayType,
        Nucleus_Interpreter_GC_Tag **list
    );
