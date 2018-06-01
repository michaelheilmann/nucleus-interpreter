# Copyright (c) 2017 - 2018 Michael Heilmann
# Assert minimum CMake version.
cmake_minimum_required (VERSION 3.8)
# Define the static library.
set(Nucleus.Interpreter.Library_HEADER_FILES)
list(APPEND Nucleus.Interpreter.Library_HEADER_FILES
            "${CMAKE_CURRENT_SOURCE_DIR}/src/Nucleus/Interpreter/TaggedValue.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/Nucleus/Interpreter/Value.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/Nucleus/Interpreter/Tag.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/Nucleus/Interpreter/UnicodeCodePoints.h")
set_source_files_properties(${Nucleus.Interpreter.Library_HEADER_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)

set(Nucleus.Interpreter.Library_INLAY_FILES)
list(APPEND Nucleus.Interpreter.Library_INLAY_FILES
            "${CMAKE_CURRENT_SOURCE_DIR}/src/Nucleus/Interpreter/UnicodeCodePoints.i")
set_source_files_properties(${Nucleus.Interpreter.Library_INLAY_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)


define_static_library(Nucleus.Interpreter Nucleus.Interpreter.Library ${NUCLEUS_LANGUAGE_ID_C})
target_link_libraries(Nucleus.Interpreter.Library PUBLIC Nucleus.Library)

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
        ${SOURCE_FILENAME} Nucleus.Interpreter.Tools.Generator
    COMMAND
        Nucleus.Interpreter.Tools.Generator --generator=${TAG_GENERATOR} --prefix=Nucleus_Interpreter_ ${SOURCE_FILENAME} "${CMAKE_CURRENT_SOURCE_DIR}/src/Nucleus/Interpreter/Tag"
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
        ${SOURCE_FILENAME} Nucleus.Interpreter.Tools.Generator
    COMMAND
        Nucleus.Interpreter.Tools.Generator --generator=${VALUE_GENERATOR} --prefix=Nucleus_Interpreter_ ${SOURCE_FILENAME} "${CMAKE_CURRENT_SOURCE_DIR}/src/Nucleus/Interpreter/Value"
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
        ${SOURCE_FILENAME} Nucleus.Interpreter.Tools.Generator
    COMMAND
        Nucleus.Interpreter.Tools.Generator --generator=${TAGGEDVALUE_GENERATOR} --prefix=Nucleus_Interpreter_ ${SOURCE_FILENAME} "${CMAKE_CURRENT_SOURCE_DIR}/src/Nucleus/Interpreter/TaggedValue"
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
        ${SOURCE_FILENAME} Nucleus.Interpreter.Tools.Unicode
    COMMAND
        Nucleus.Interpreter.Tools.Unicode --generator=Header --prefix=Nucleus_Interpreter_ ${SOURCE_FILENAME} ${TARGET_HEADER_FILENAME}
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
        ${SOURCE_FILENAME} Nucleus.Interpreter.Tools.Unicode
    COMMAND
        Nucleus.Interpreter.Tools.Unicode --generator=Inlay --prefix= ${SOURCE_FILENAME} ${TARGET_INLAY_FILENAME}
    COMMENT
        "Generating ${TARGET_INLAY_FILENAME} from ${SOURCE_FILENAME}"
    VERBATIM
)
