#include "Nucleus/Interpreter/GC/Heap.h"

#include "Nucleus/Interpreter/Context.h"
#include "Nucleus/Interpreter/Status.h" // @todo Remove this.

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_GC_Heap_initialize
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_GC_Heap *heap
    )
{
    if (!heap) Nucleus_Interpreter_Context_raiseError(context, Nucleus_Interpreter_Status_InvalidArgument);
    heap->premark = NULL;
    heap->sweep = NULL;
    heap->uninitialize = NULL;
}

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_GC_Heap_uninitialize
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_GC_Heap *heap
    )
{
    heap->uninitialize(context, heap);
}

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_GC_Heap_premark
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_GC_Heap *heap
    )
{
    heap->premark(context, heap);
}

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_GC_Heap_sweep
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_GC_Heap *heap
    )
{
    heap->sweep(context, heap);
}
