#include "Nucleus/Interpreter/Context.h"
#include "Nucleus/Interpreter/JumpTarget.h"
#include "Nucleus/Interpreter/String.h"
#include "Nucleus/Interpreter/StringBuffer.h"
#include "Nucleus/Interpreter/UnitTesting.h"
#include <stdlib.h>

static Nucleus_Interpreter_Status
testBase
    (
        size_t initialCapacity,
        size_t requiredFreeCapacity
    )
{
    Nucleus_Interpreter_Context *context;
    Nucleus_Interpreter_Status status = Nucleus_Interpreter_Context_create(&context);
    if (status) {
        return status;
    }
    Nucleus_Interpreter_JumpTarget jt;
    Nucleus_Interpreter_StringBuffer stringBuffer;
    Nucleus_Interpreter_ProcessContext_pushJumpTarget(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context), &jt);
    if (!setjmp(jt.environment))
    {
        /// @remark Create a string buffer with initial capacity of @a initialCapacity.
        Nucleus_Interpreter_StringBuffer_initialize(context, &stringBuffer, initialCapacity);
        Nucleus_Interpreter_ProcessContext_popJumpTarget(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
    }
    else
    {
        status = Nucleus_Interpreter_ProcessContext_getStatus(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
        Nucleus_Interpreter_ProcessContext_popJumpTarget(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
        Nucleus_Interpreter_Context_destroy(context);
        return status;
    }
    
    Nucleus_Interpreter_ProcessContext_pushJumpTarget(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context), &jt);
    if (!setjmp(jt.environment))
    {
        /// @remark Assert the size is @a 0.
        Nucleus_Interpreter_UnitTest_AssertEqualTo(context,
                                                   Nucleus_Interpreter_StringBuffer_getSize(context, &stringBuffer), 0);
        /// @remark Assert the capacity is greater than or equal to @a initialCapacity.
        Nucleus_Interpreter_UnitTest_AssertGreaterThanOrEqualTo(context,
                                                                Nucleus_Interpreter_StringBuffer_getCapacity(context, &stringBuffer), initialCapacity);
        /// @remark Assert the free capacity is equal to <c>capacity - size</c>.
        Nucleus_Interpreter_UnitTest_AssertEqualTo(context,
                                                   Nucleus_Interpreter_StringBuffer_getFreeCapacity(context, &stringBuffer),
                                                   Nucleus_Interpreter_StringBuffer_getCapacity(context, &stringBuffer) -
                                                   Nucleus_Interpreter_StringBuffer_getSize(context, &stringBuffer));
        /// @remark Ensure the free capacity is greater than or equal to @a requiredFreeCapacity.
        Nucleus_Interpreter_StringBuffer_ensureFreeCapacity(context, &stringBuffer, requiredFreeCapacity);
        /// @remark Assert the size is @a 0.
        Nucleus_Interpreter_UnitTest_AssertEqualTo(context,
                                                   Nucleus_Interpreter_StringBuffer_getSize(context, &stringBuffer),
                                                   0);
        /// @remark Assert the capacity is greater than @a requiredFreeCapacity.
        Nucleus_Interpreter_UnitTest_AssertGreaterThanOrEqualTo(context,
                                                                Nucleus_Interpreter_StringBuffer_getCapacity(context, &stringBuffer),
                                                                requiredFreeCapacity);
        /// @remark Assert the free capacity is equal to <c>capacity - size</c>.
        Nucleus_Interpreter_UnitTest_AssertEqualTo(context,
                                                   Nucleus_Interpreter_StringBuffer_getFreeCapacity(context, &stringBuffer),
                                                   Nucleus_Interpreter_StringBuffer_getCapacity(context, &stringBuffer) -
                                                   Nucleus_Interpreter_StringBuffer_getSize(context, &stringBuffer));
        Nucleus_Interpreter_ProcessContext_popJumpTarget(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
    }
    else
    {
        Nucleus_Interpreter_ProcessContext_popJumpTarget(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
        Nucleus_Interpreter_StringBuffer_uninitialize(context, &stringBuffer);
        status = Nucleus_Interpreter_ProcessContext_getStatus(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
        Nucleus_Interpreter_Context_destroy(context);
        return status;
    }
    Nucleus_Interpreter_StringBuffer_uninitialize(context, &stringBuffer);
    status = Nucleus_Interpreter_ProcessContext_getStatus(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context));
    Nucleus_Interpreter_Context_destroy(context);
    return status;
}

int main(int argc, char **argv)
{
    if (//
        testBase(0, 0) ||
        testBase(0, 1) ||
        testBase(1, 0) ||
        testBase(1, 1) ||
        //
        /*
        testBase(0, 0) ||
        */
        testBase(0, 8) ||
        /*
        testBase(1, 0) ||
        */
        testBase(1, 8))
        return EXIT_FAILURE;
    else return EXIT_SUCCESS;
}
