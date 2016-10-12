#include "Nucleus/Interpreter/Context.h"
#include <stdlib.h>

static Nucleus_Interpreter_Status
test
    (
    )
{
    Nucleus_Interpreter_Context *context;
    Nucleus_Interpreter_Status status = Nucleus_Interpreter_Context_create(&context);
    if (status) return status;
    Nucleus_Interpreter_Context_destroy(context);
    return Nucleus_Interpreter_Status_Success;
}

int
main
    (
        int argc,
        char **argv
    )
{
    if (test()) return EXIT_FAILURE;
    else return EXIT_SUCCESS;
}
