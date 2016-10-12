// Copyright (c) Michael Heilmann 2018
// https://github.com/nucleus-interpreter/blob/master/documentation/Nucleus_Interpreter_TypeSystem.md
#include "Nucleus/Interpreter/Void.h"

Nucleus_Interpreter_Void
Nucleus_Interpreter_Void_VoidConstant
    (
    )
{ static const Nucleus_Interpreter_Void instance = { 0 };
  return instance; }
