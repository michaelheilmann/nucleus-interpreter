#include "Nucleus/Interpreter/GC/Arena.h"

#include "Nucleus/Interpreter/Context.h"
#include "Nucleus/Interpreter/Status.h" // @todo Remove this.

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_GC_Arena_initialize
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_GC_Arena *arena
    )
{
    if (Nucleus_Interpreter_Unlikely(!arena)) Nucleus_Interpreter_Context_raiseError(context, Nucleus_Interpreter_Status_InvalidArgument);
    arena->premark = NULL;
    arena->sweep = NULL;
    arena->uninitialize = NULL;
}

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_GC_Arena_uninitialize
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_GC_Arena *arena
    )
{
    arena->uninitialize(context, arena);
}

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_GC_Arena_premark
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_GC_Arena *arena
    )
{
    arena->premark(context, arena);
}

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_GC_Arena_sweep
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_GC_Arena *arena
    )
{
    arena->sweep(context, arena);
}
