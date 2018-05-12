// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Interpreter/GC/Arena.h"
#include "Nucleus/Types/HashValue.h"
#include "Nucleus/Types/Size.h"

// Forward declaration.
//typedef struct Nucleus_Interpreter_String Nucleus_Interpreter_String;
typedef struct Nucleus_Interpreter_GC_Tag Nucleus_Interpreter_GC_Tag;

typedef struct Nucleus_Interpreter_LockArena Nucleus_Interpreter_LockArena;

typedef struct Nucleus_Interpreter_Lock Nucleus_Interpreter_Lock;

struct Nucleus_Interpreter_LockArena
{
    Nucleus_Interpreter_GC_Arena __parent;
    Nucleus_Interpreter_Lock **buckets;
    Nucleus_Size size;
    Nucleus_Size capacity;
	Nucleus_Interpreter_Lock *free;
}; // struct Nucleus_Interpreter_LockArena

/// @ingroup interpreter
/// @internal
/// @brief Initialize a @a (Nucleus_Interpreter_LockArena) object.
/// @param context a pointer to a @a (Nucleus_Interpreter_Context) object
/// @param locksArena a pointer to an uninitialized @a (Nucleus_Interpreter_LockArena) object
/// @post The @a (Nucleus_Interpreter_LockArena) object was initialized on success, otherwise not.
Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_LockArena_initialize
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_LockArena *lockArena
    );

Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Lock *
Nucleus_Interpreter_LockArena_acquireLock
	(
		Nucleus_Interpreter_Context *context,
		Nucleus_Interpreter_LockArena *lockArena,
		Nucleus_Interpreter_GC_Tag *tag
	);

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_Lock_release
	(
		Nucleus_Interpreter_Context *context,
		Nucleus_Interpreter_Lock *lock
	);
