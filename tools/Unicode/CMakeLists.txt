# Copyright (c) Michael Heilmann 2017, 2018

# Minimum required CMake version.
cmake_minimum_required (VERSION 3.8)

# Project.
set(PROJECT_NAME "Interpreter.Tools.Unicode")
project(${PROJECT_NAME} C)
message("building ${PROJECT_NAME}")

if (NUCLEUS_PATH)
  include(${NUCLEUS_PATH}/buildsystem/detect_compiler_and_platform.cmake)
  include(${NUCLEUS_PATH}/buildsystem/set_default_project_properties.cmake)
else()
  include(${CMAKE_CURRENT_SOURCE_DIR}/../buildsystem/detect_compiler_and_platform.cmake)
  include(${CMAKE_CURRENT_SOURCE_DIR}/../buildsystem/set_default_project_properties.cmake)
endif()

# Find and configure source files.
file(GLOB_RECURSE SOURCE_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "src/*.c")
# Find and configure header files.
file(GLOB_RECURSE HEADER_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "src/*.h")
set_source_files_properties(${HEADER_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)
# Find and configure inlay files.
file(GLOB_RECURSE INLAY_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "src/*.i")
set_source_files_properties(${INLAY_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)
# Add and configure executable.
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES} ${INLAY_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_link_libraries(${PROJECT_NAME} Nucleus.Library)
# Set its properties.
set_project_default_properties(${PROJECT_NAME})
