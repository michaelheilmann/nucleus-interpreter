#include "Nucleus/Interpreter/Context.h"
#include "Nucleus/Interpreter/Conversions.h"
#include "Nucleus/Interpreter/Integer.h"
#include "Nucleus/Interpreter/String.h"
#include "Nucleus/Interpreter/UnitTesting.h"
#include <stdlib.h>

Nucleus_Interpreter_NonNull() static void
test
    (
        Nucleus_Interpreter_Context *context
    )
{
    Nucleus_Interpreter_String *s = Nucleus_Interpreter_String_create(context, "3", sizeof("3") - 1);
    Nucleus_Interpreter_Integer i = Nucleus_Interpreter_stringToInteger(context, s);
    Nucleus_Interpreter_UnitTest_AssertTrue(context, i == 3);
}

int main(int argc, char **argv)
{
    
    if (Nucleus_Interpreter_UnitTest_run(&test)) return EXIT_FAILURE;
    else return EXIT_SUCCESS;
}
