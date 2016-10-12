// Copyright (c) Michael Heilmann 2018
// https://github.com/nucleus-interpreter/blob/master/documentation/Nucleus_Interpreter_TypeSystem.md
#pragma once

#include "Nucleus/Interpreter/Annotations.h"
#include <limits.h>  // For FLT_MIN and FLT_MAX.

typedef struct Nucleus_Interpreter_Context Nucleus_Interpreter_Context;
typedef struct Nucleus_Interpreter_String Nucleus_Interpreter_String;

typedef float Nucleus_Interpreter_Real;

#define Nucleus_Interpreter_Real_LeastConstant() (FLT_MIN)

#define Nucleus_Interpreter_Real_GreatestConstant() (FLT_MAX)
