# Copyright (c) Michael Heilmann 2017, 2018
# Assert minimum CMake version.
cmake_minimum_required (VERSION 3.8)
# Define the test.
set(libraries Nucleus.Interpreter.Library)
# Use short names for the crappy msbuild as it has pathname/filename length limitations.
if (MSVC)
  set(target_name Nucleus.Interpreter.Test.stringToInteger)
else()
  set(target_name Nucleus.Interpreter.Test.stringToInteger)
endif()
define_test(Machine ${target_name} ${libraries} ${NUCLEUS_LANGUAGE_ID_C})
