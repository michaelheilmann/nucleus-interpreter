#include "Nucleus/Interpreter/Context.h"
#include "Nucleus/Interpreter/String.h"
#include "Nucleus/Interpreter/UnitTesting.h"
#include <stdlib.h>

Nucleus_Interpreter_NonNull() static void
test
    (
        Nucleus_Interpreter_Context *context
    )
{
    Nucleus_Interpreter_String *x = Nucleus_Interpreter_String_create(context,
                                                                      "Hello, World\n", strlen("Hello, World!\n"));
    Nucleus_Interpreter_UnitTest_AssertTrue(context, Nucleus_Interpreter_String_equalTo(context, x, x));
}

int main(int argc, char **argv)
{
    if (Nucleus_Interpreter_UnitTest_run(&test)) return EXIT_FAILURE;
    else return EXIT_SUCCESS;
}
