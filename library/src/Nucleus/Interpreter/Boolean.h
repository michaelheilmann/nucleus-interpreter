// Copyright (c) Michael Heilmann 2018
// https://github.com/nucleus-interpreter/blob/master/documentation/Nucleus_Interpreter_TypeSystem.md
#pragma once

#include "Nucleus/Interpreter/Annotations.h"
#include <stdbool.h> // For bool.

typedef struct Nucleus_Interpreter_Context Nucleus_Interpreter_Context;
typedef struct Nucleus_Interpreter_String Nucleus_Interpreter_String;

typedef bool Nucleus_Interpreter_Boolean;

#define Nucleus_Interpreter_Boolean_TrueConstant() (true)

#define Nucleus_Interpreter_Boolean_FalseConstant() (false)
