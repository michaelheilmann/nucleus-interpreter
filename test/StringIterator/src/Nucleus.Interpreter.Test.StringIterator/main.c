#include "Nucleus/Interpreter/Context.h"
#include "Nucleus/Interpreter/String.h"
#include "Nucleus/Interpreter/StringIterator.h"
#include "Nucleus/Interpreter/UnitTesting.h"
#include <stdlib.h>

Nucleus_Interpreter_NonNull() static void
emptyString
    (
        Nucleus_Interpreter_Context *context
    )
{
    Nucleus_Interpreter_String *w = Nucleus_Interpreter_String_create(context, "", strlen(""));
    Nucleus_Interpreter_StringIterator *it = Nucleus_Interpreter_StringIterator_create(context, w);
    Nucleus_Interpreter_UnitTest_AssertTrue(context, Nucleus_Interpreter_Symbol_equalTo(context, Nucleus_Interpreter_Symbol_begin(context),
                                                                                        Nucleus_Interpreter_StringIterator_get(context, it)));
    Nucleus_Interpreter_StringIterator_increment(context, it);
    Nucleus_Interpreter_UnitTest_AssertTrue(context, Nucleus_Interpreter_Symbol_equalTo(context, Nucleus_Interpreter_Symbol_end(context),
                                                                                        Nucleus_Interpreter_StringIterator_get(context, it)));
}

int main(int argc, char **argv)
{
    if (Nucleus_Interpreter_UnitTest_run(&emptyString)) return EXIT_FAILURE;
    else return EXIT_SUCCESS;
}
