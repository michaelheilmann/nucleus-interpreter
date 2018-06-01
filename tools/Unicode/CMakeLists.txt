# Copyright (c) 2017 - 2018 Michael Heilmann
# Assert minimum CMake version.
cmake_minimum_required (VERSION 3.8)
# Define the tool.
define_executable(Nucleus.Interpreter Nucleus.Interpreter.Tools.Unicode ${NUCLEUS_LANGUAGE_ID_C})
target_link_libraries(Nucleus.Interpreter.Tools.Unicode PRIVATE Nucleus.Library)
