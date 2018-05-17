// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/Interpreter/Arenas/GeneralArena-private.c.in"

#include "Nucleus/Interpreter/GC/Object.h"
#include "Nucleus/Interpreter/TS.h"

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_GeneralArena_initialize
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_GeneralArena *generalArena
    )
{
    Nucleus_Interpreter_GC_Arena_initialize(context, NUCLEUS_INTERPRETER_GC_ARENA(generalArena));
    generalArena->objects = NULL;
    NUCLEUS_INTERPRETER_GC_ARENA(generalArena)->premark = NUCLEUS_INTERPRETER_GC_ARENA_PREMARK(&premark);
    NUCLEUS_INTERPRETER_GC_ARENA(generalArena)->sweep = NUCLEUS_INTERPRETER_GC_ARENA_SWEEP(&sweep);
    NUCLEUS_INTERPRETER_GC_ARENA(generalArena)->uninitialize = NUCLEUS_INTERPRETER_GC_ARENA_UNINITIALIZE(&uninitialize);
}
