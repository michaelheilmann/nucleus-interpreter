#include "Nucleus/Interpreter/Context.h"
#include "Nucleus/Interpreter/getFileContents.h"
#include "Nucleus/Interpreter/setFileContents.h"
#include "Nucleus/Interpreter/String.h"
#include "Nucleus/Interpreter/UnitTesting.h"
#include <stdlib.h>

Nucleus_Interpreter_NonNull() static void
test
    (
        Nucleus_Interpreter_Context *context
    )
{
    Nucleus_Interpreter_String *pathname = Nucleus_Interpreter_String_create(context,
                                                                             "data/helloworld.txt",
                                                                             strlen("data/helloworld.txt"));
    Nucleus_Interpreter_String *reference = Nucleus_Interpreter_String_create(context,
                                                                              "Hello, World!\r\n",
                                                                              strlen("Hello, World!\r\n"));
    Nucleus_Interpreter_setFileContentsString(context, pathname, reference);
    Nucleus_Interpreter_String *contents = Nucleus_Interpreter_getFileContentsString(context, pathname);
    Nucleus_Interpreter_UnitTest_AssertTrue(context, Nucleus_Interpreter_String_equalTo(context,
                                                                                        contents, reference));
}

int main(int argc, char **argv)
{
    if (Nucleus_Interpreter_UnitTest_run(&test)) return EXIT_FAILURE;
    else return EXIT_SUCCESS;
}
