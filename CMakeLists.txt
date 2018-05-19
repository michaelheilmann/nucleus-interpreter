# Copyright (c) Michael Heilmann 2017, 2018

# Assert minimum CMake version.
cmake_minimum_required(VERSION 3.8)

if (NOT NUCLEUS_PATH)
  set(NUCLEUS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/nucleus)
endif()
if (NUCLEUS_PATH)
  include(${NUCLEUS_PATH}/buildsystem/buildsystem.cmake)
endif()

# Define module.
define_module(Nucleus.Interpreter)

# Add module "Nucleus".
if (NOT NUCLEUS_PATH)
  set(NUCLEUS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/nucleus)
endif()
if (NOT NUCLEUS_INCLUDED)
  set(Nucleus-With-Optimizations ${Nucleus.Interpreter-With-Optimizations})
  set(Nucleus-With-Debug-Information ${Nucleus.Interpreter-With-Debug-Information})
  add_subdirectory(${NUCLEUS_PATH})
  set(NUCLEUS_INCLUDED YES)
endif()

# Add module "tools".
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/tools")

# Add module "library".
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/library")

# Add module "test".
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/test")
