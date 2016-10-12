// Copyright (c) Michael Heilmann 2018
// https://github.com/nucleus-interpreter/blob/master/documentation/Nucleus_Interpreter_TypeSystem.md
#pragma once

#include <limits.h>  // For INT_MIN and INT_MAX.

typedef int Nucleus_Interpreter_Integer;

#define Nucleus_Interpreter_Integer_LeastConstant() (INT_MIN)

#define Nucleus_Interpreter_Integer_GreatestConstant() (INT_MAX)
