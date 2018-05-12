# Copyright (c) 2017, 2018 Michael Heilmann

# Minimum required CMake version.
cmake_minimum_required (VERSION 3.8)

# Project.
project (Nucleus.Interpreter.Library C)

if (NUCLEUS_PATH)
  include(${NUCLEUS_PATH}/buildsystem/detect_compiler_and_platform.cmake)
  include(${NUCLEUS_PATH}/buildsystem/set_default_project_properties.cmake)
else()
  include(${CMAKE_CURRENT_SOURCE_DIR}/../buildsystem/detect_compiler_and_platform.cmake)
  include(${CMAKE_CURRENT_SOURCE_DIR}/../buildsystem/set_default_project_properties.cmake)
endif()

# The interpreter types file.
set(SOURCE_FILENAME "${CMAKE_CURRENT_SOURCE_DIR}/src/Nucleus/Interpreter/Types.l")

# Define, configure, and invoke tool to generate
# "${CMAKE_CURRENT_SOURCE_DIR}/Nucleus/Interpreter/Value.c"
# and
# "${CMAKE_CURRENT_SOURCE_DIR}/Nucleus/Interpreter/Value.h"
# from
# "${CMAKE_CURRENT_SOURCE_DIR}/Nucleus/Interpreter/Types.l"
set(TAG_GENERATOR "Tag")
add_custom_command(
    OUTPUT
        "${CMAKE_CURRENT_SOURCE_DIR}/src/Nucleus/Interpreter/Tag.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/Nucleus/Interpreter/Tag.c"
    DEPENDS
        ${SOURCE_FILENAME} Interpreter.Tools.Generator
    COMMAND
        Interpreter.Tools.Generator --generator=${TAG_GENERATOR} --prefix=Nucleus_Interpreter_ ${SOURCE_FILENAME} "${CMAKE_CURRENT_SOURCE_DIR}/src/Nucleus/Interpreter/Tag"
    COMMENT
        "Generating ${CMAKE_CURRENT_SOURCE_DIR}/src/Nucleus/Interpreter/Tag.c and ${CMAKE_CURRENT_SOURCE_DIR}/src/Nucleus/Interpreter/Tag.h from ${SOURCE_FILENAME}"
    VERBATIM
)

# Define, configure, and invoke tool to generate
# "${CMAKE_CURRENT_SOURCE_DIR}/Nucleus/Interpreter/Value.c"
# and
# "${CMAKE_CURRENT_SOURCE_DIR}/Nucleus/Interpreter/Value.h"
# from
# "${CMAKE_CURRENT_SOURCE_DIR}/Nucleus/Interpreter/Types.l"
set(VALUE_GENERATOR "Value")
add_custom_command(
    OUTPUT
        "${CMAKE_CURRENT_SOURCE_DIR}/src/Nucleus/Interpreter/Value.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/Nucleus/Interpreter/Value.h"
    DEPENDS
        ${SOURCE_FILENAME} Interpreter.Tools.Generator
    COMMAND
        Interpreter.Tools.Generator --generator=${VALUE_GENERATOR} --prefix=Nucleus_Interpreter_ ${SOURCE_FILENAME} "${CMAKE_CURRENT_SOURCE_DIR}/src/Nucleus/Interpreter/Value"
    COMMENT
        "Generating ${CMAKE_CURRENT_SOURCE_DIR}/src/Nucleus/Interpreter/Value.c and ${CMAKE_CURRENT_SOURCE_DIR}/src/Nucleus/Interpreter/Value.h from ${SOURCE_FILENAME}"
    VERBATIM
)

# Define, configure, and invoke tool to generate
# "${CMAKE_CURRENT_SOURCE_DIR}/Nucleus/Interpreter/TaggedValue.c"
# and
# "${CMAKE_CURRENT_SOURCE_DIR}/Nucleus/Interpreter/TaggedValue.h"
# from
# "${CMAKE_CURRENT_SOURCE_DIR}/Nucleus/Interpreter/Types.l"
set(TAGGEDVALUE_GENERATOR "Tagged Value")
add_custom_command(
    OUTPUT
        "${CMAKE_CURRENT_SOURCE_DIR}/src/Nucleus/Interpreter/TaggedValue.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/Nucleus/Interpreter/TaggedValue.h"
    DEPENDS
        ${SOURCE_FILENAME} Interpreter.Tools.Generator
    COMMAND
        Interpreter.Tools.Generator --generator=${TAGGEDVALUE_GENERATOR} --prefix=Nucleus_Interpreter_ ${SOURCE_FILENAME} "${CMAKE_CURRENT_SOURCE_DIR}/src/Nucleus/Interpreter/TaggedValue"
    COMMENT
        "Generating ${CMAKE_CURRENT_SOURCE_DIR}/src/Nucleus/Interpreter/TaggedValue.c and ${CMAKE_CURRENT_SOURCE_DIR}/src/Nucleus/Interpreter/TaggedValue.h from ${SOURCE_FILENAME}"
    VERBATIM
)

# The Unicode codepoints file.
set(SOURCE_FILENAME "${CMAKE_CURRENT_SOURCE_DIR}/src/Nucleus/Interpreter/UnicodeCodePoints.l")

# Define, configure, and invoke tool to generate
# "${CMAKE_CURRENT_SOURCE_DIR}/Nucleus/Interpreter/UnicodeSymbols.h"
# from
# "${CMAKE_CURRENT_SOURCE_DIR}/Nucleus/Interpreter/UnicodeSymbols.l"
set(TARGET_HEADER_FILENAME "${CMAKE_CURRENT_SOURCE_DIR}/src/Nucleus/Interpreter/UnicodeCodePoints.h")
add_custom_command(
    OUTPUT
        ${TARGET_HEADER_FILENAME}
    DEPENDS
        ${SOURCE_FILENAME} Interpreter.Tools.Unicode
    COMMAND
        Interpreter.Tools.Unicode --generator=Header --prefix=Nucleus_Interpreter_ ${SOURCE_FILENAME} ${TARGET_HEADER_FILENAME}
    COMMENT
        "Generating ${TARGET_HEADER_FILENAME} from ${SOURCE_FILENAME}"
    VERBATIM
)

# Define, configure, and invoke tool to generate
# "${CMAKE_CURRENT_SOURCE_DIR}/Nucleus/Interpreter/UnicodeSymbols.i"
# from
# "${CMAKE_CURRENT_SOURCE_DIR}/Nucleus/Interpreter/UnicodeSymbols.l"
set(TARGET_INLAY_FILENAME "${CMAKE_CURRENT_SOURCE_DIR}/src/Nucleus/Interpreter/UnicodeCodePoints.i")
add_custom_command(
    OUTPUT
        ${TARGET_INLAY_FILENAME}
    DEPENDS
        ${SOURCE_FILENAME} Interpreter.Tools.Unicode
    COMMAND
        Interpreter.Tools.Unicode --generator=Inlay --prefix= ${SOURCE_FILENAME} ${TARGET_INLAY_FILENAME}
    COMMENT
        "Generating ${TARGET_INLAY_FILENAME} from ${SOURCE_FILENAME}"
    VERBATIM
)

# Find and configure source files.
file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}" "src/*.c")
# Find and configure header files.
file(GLOB_RECURSE HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}" "src/*.h")
list(APPEND HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/Nucleus/Interpreter/TaggedValue.h"
                         "${CMAKE_CURRENT_SOURCE_DIR}/src/Nucleus/Interpreter/Value.h"
                         "${CMAKE_CURRENT_SOURCE_DIR}/src/Nucleus/Interpreter/Tag.h"
                         "${CMAKE_CURRENT_SOURCE_DIR}/src/Nucleus/Interpreter/UnicodeCodePoints.h"
                         "${CMAKE_CURRENT_SOURCE_DIR}/src/Nucleus/Interpreter/UnicodeCodePoints.i")
set_source_files_properties(${HEADER_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)
# Define and configure the library.
add_library(Nucleus.Interpreter.Library STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(Nucleus.Interpreter.Library Nucleus.Library)
target_include_directories(Nucleus.Interpreter.Library PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories(Nucleus.Interpreter.Library INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/src")
# Set its properties.
set_project_default_properties(Nucleus.Interpreter.Library)

IF(DOXYGEN_FOUND)
    ADD_CUSTOM_TARGET(Nucleus.Interpreter.Library.Documentation ${DOXYGEN_EXECUTABLE} COMMENT "Building documentation")
ELSE(DOXYGEN_FOUND)
    MESSAGE(STATUS "Doxygen not found. You won't be able to build documentation.")
ENDIF(DOXYGEN_FOUND)
