#pragma once

#include "Nucleus/Interpreter/Annotations.h"

// Forward declaration.
typedef struct Nucleus_Interpreter_Context Nucleus_Interpreter_Context;

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_GC_onRun
    (
        Nucleus_Interpreter_Context *context
    );
