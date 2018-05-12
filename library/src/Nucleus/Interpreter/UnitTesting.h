// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Interpreter/Context.h"
#include <string.h>
#include <setjmp.h>
#include <stdio.h>

#define Nucleus_Interpreter_UnitTest_Status_AssertionFailed (1000)

#define Nucleus_Interpreter_UnitTest_AssertTrue(c, e) \
    if (!(e)) { \
        fprintf(stderr, "assertion %s == true failed\n", #e); \
        Nucleus_Interpreter_ProcessContext_setStatus(NUCLEUS_INTERPRETER_PROCESSCONTEXT(c), Nucleus_Interpreter_UnitTest_Status_AssertionFailed); \
        Nucleus_Interpreter_ProcessContext_jump(NUCLEUS_INTERPRETER_PROCESSCONTEXT(c)); \
    }

#define Nucleus_Interpreter_UnitTest_AssertEqualTo(c, x, y) \
    if (!((x) == (y))) { \
        fprintf(stderr, "assertion %s == %s failed\n", #x, #y); \
        Nucleus_Interpreter_ProcessContext_setStatus(NUCLEUS_INTERPRETER_PROCESSCONTEXT(c), Nucleus_Interpreter_UnitTest_Status_AssertionFailed); \
        Nucleus_Interpreter_ProcessContext_jump(NUCLEUS_INTERPRETER_PROCESSCONTEXT(c)); \
    }

#define Nucleus_Interpreter_UnitTest_AssertNotEqualTo(c, x, y) \
    if (!((x) != (y))) { \
        fprintf(stderr, "assertion %s != %s failed\n", #x, #y); \
        Nucleus_Interpreter_ProcessContext_setStatus(NUCLEUS_INTERPRETER_PROCESSCONTEXT(c), Nucleus_Interpreter_UnitTest_Status_AssertionFailed); \
        Nucleus_Interpreter_ProcessContext_jump(NUCLEUS_INTERPRETER_PROCESSCONTEXT(c)); \
    }

#define Nucleus_Interpreter_UnitTest_AssertGreaterThanOrEqualTo(c, x, y) \
    if (!((x) >= (y))) { \
        fprintf(stderr, "assertion %s >= %s failed\n", #x, #y); \
        Nucleus_Interpreter_ProcessContext_setStatus(NUCLEUS_INTERPRETER_PROCESSCONTEXT(c), Nucleus_Interpreter_UnitTest_Status_AssertionFailed); \
        Nucleus_Interpreter_ProcessContext_jump(NUCLEUS_INTERPRETER_PROCESSCONTEXT(c)); \
    }

Nucleus_Interpreter_NoError() Nucleus_Interpreter_NonNull() Nucleus_Interpreter_Status
Nucleus_Interpreter_UnitTest_run
    (
        void (*test)(Nucleus_Interpreter_Context *)
    );
