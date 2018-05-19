# Copyright (c) Michael Heilmann 2017, 2018
# Assert minimum CMake version.
cmake_minimum_required (VERSION 3.8)
# Define the test.
set(libraries Machine.Library)
define_test(Machine Machine.Test.getFileContents ${libraries} ${NUCLEUS_LANGUAGE_ID_C})
