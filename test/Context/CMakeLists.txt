# Copyright (c) Michael Heilmann 2017, 2018
# Assert minimum CMake version.
cmake_minimum_required (VERSION 3.8)
# Define the test.
set(libraries Nucleus.Interpreter.Library)
define_test(Nucleus.Interpreter Nucleus.Interpreter.Test.Context ${libraries} ${NUCLEUS_LANGUAGE_ID_C})
