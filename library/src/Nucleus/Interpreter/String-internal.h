// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Interpreter/String.h"
#include "Nucleus/Interpreter/GC/Object.h"

struct Nucleus_Interpreter_String
{
    size_t hashValue;
    size_t numberOfBytes;
    char bytes[];
}; // struct Nucleus_Interpreter_String
