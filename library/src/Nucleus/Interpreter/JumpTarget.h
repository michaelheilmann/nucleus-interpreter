// Copyright (c) Michael Heilmann 2018
#pragma once

#include <setjmp.h>

/// @ingroup interpreter
/// @internal
/// @brief An jump target.
typedef struct Nucleus_Interpreter_JumpTarget Nucleus_Interpreter_JumpTarget;

struct Nucleus_Interpreter_JumpTarget
{
    Nucleus_Interpreter_JumpTarget *previous;
    jmp_buf environment;
}; // struct Nucleus_Interpreter_JumpTarget
