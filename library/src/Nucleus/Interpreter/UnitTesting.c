// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/Interpreter/UnitTesting.h"
#include "Nucleus/Interpreter/JumpTarget.h"

Nucleus_Interpreter_NoError() Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Status
Nucleus_Interpreter_UnitTest_run
    (
        void (*test)(Nucleus_Interpreter_Context *)
    )
{
    Nucleus_Interpreter_Context *context;
    Nucleus_Interpreter_Status status = Nucleus_Interpreter_Context_create(&context);
    if (status)
    { return status; }
    Nucleus_Interpreter_JumpTarget jt;
    Nucleus_Interpreter_ProcessContext_pushJumpTarget(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context), &jt);
    if (!setjmp(jt.environment))
    { (*test)(context); }
    Nucleus_Interpreter_ProcessContext_popJumpTarget(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
    status = Nucleus_Interpreter_ProcessContext_getStatus(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
    Nucleus_Interpreter_Context_destroy(context);
    return status;
}
