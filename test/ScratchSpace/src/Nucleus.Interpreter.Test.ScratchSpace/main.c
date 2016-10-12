#include "Nucleus/Interpreter/Context.h"
#include "Nucleus/Interpreter/UnitTesting.h"
#include <stdlib.h>

Nucleus_Interpreter_NonNull() static void
test
    (
        Nucleus_Interpreter_Context *context
    )
{
    char *p = Nucleus_Interpreter_Context_acquireScratchSpace(context, 16);
    memcpy(p, "Hello, World!\r\n", strlen("Hello, World!\r\n"));
    Nucleus_Interpreter_Context_relinquishScratchSpace(context, p);
}

int main(int argc, char **argv)
{
    
    if (Nucleus_Interpreter_UnitTest_run(&test)) return EXIT_FAILURE;
    else return EXIT_SUCCESS;
}
