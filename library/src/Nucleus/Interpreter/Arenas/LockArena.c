// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/Interpreter/Arenas/LockArena-private.c.in"

#include "Nucleus/Interpreter/JumpTarget.h"

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_LockArena_initialize
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_LockArena *lockArena
    )
{
    Nucleus_Interpreter_GC_Arena_initialize(context, NUCLEUS_INTERPRETER_GC_ARENA(lockArena));
	lockArena->free = NULL;
    lockArena->size = 0;
    lockArena->capacity = 16;
    Nucleus_Interpreter_JumpTarget jt;
    Nucleus_Interpreter_ProcessContext_pushJumpTarget(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context), &jt);
    if (!setjmp(jt.environment))
    {
        lockArena->buckets = Nucleus_Interpreter_ProcessContext_allocateUnmanagedArrayMemory(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context),
                                                                                             16, sizeof(Nucleus_Interpreter_Lock *));
        Nucleus_Interpreter_ProcessContext_popJumpTarget(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
    }
    else
    {
        Nucleus_Interpreter_ProcessContext_popJumpTarget(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
        Nucleus_Interpreter_Context_raiseError(context, Nucleus_Interpreter_ProcessContext_getStatus(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context)));
    }
    for (size_t i = 0, n = 16; i < n; ++i)
    { lockArena->buckets[i] = NULL; }
    NUCLEUS_INTERPRETER_GC_ARENA(lockArena)->premark = NUCLEUS_INTERPRETER_GC_ARENA_PREMARK(&premark);
    NUCLEUS_INTERPRETER_GC_ARENA(lockArena)->sweep = NUCLEUS_INTERPRETER_GC_ARENA_SWEEP(&sweep);
    NUCLEUS_INTERPRETER_GC_ARENA(lockArena)->uninitialize = NUCLEUS_INTERPRETER_GC_ARENA_UNINITIALIZE(&uninitialize);
}

Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Lock *
Nucleus_Interpreter_LockArena_acquireLock
	(
		Nucleus_Interpreter_Context *context,
		Nucleus_Interpreter_LockArena *lockArena,
		Nucleus_Interpreter_GC_Tag *tag
	)
{
	Nucleus_HashValue hashValue = hash(context, tag);
	Nucleus_Size hashIndex = hashValue % lockArena->capacity;
	Nucleus_Interpreter_Lock *lock = allocateLock(context, lockArena);
	lock->hashValue = hashValue;
	lock->tag = tag;
	lock->arena = lockArena;
	lock->next = lockArena->buckets[hashIndex];
	lockArena->buckets[hashIndex] = lock;
	lockArena->size++;
	return lock;
}

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_Lock_release
	(
		Nucleus_Interpreter_Context *context,
		Nucleus_Interpreter_Lock *lock
	)
{
	Nucleus_Interpreter_LockArena *lockArena = lock->arena;
	Nucleus_Size hashIndex = lock->hashValue % lockArena->capacity;
	Nucleus_Interpreter_Lock **predecessor = &lockArena->buckets[hashIndex],
	                          *current = lockArena->buckets[hashIndex];
	while (current != lock)
	{
		predecessor = &current->next;
		current = current->next;
	}
	*predecessor = current->next;
	deallocateLock(context, lockArena, current);
	lockArena->size--;
}
