# Copyright (c) Michael Heilmann 2017, 2018
# Assert minimum CMake version.
cmake_minimum_required (VERSION 3.8)
# Define the tool.
set(libraries Nucleus.Library)
define_executable(Nucleus.Interpreter Nucleus.Interpreter.Tools.Unicode ${libraries} ${NUCLEUS_LANGUAGE_ID_C})
