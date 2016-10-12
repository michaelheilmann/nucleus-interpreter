/// @author Michael Heilmann
/// @copyright Copyright (c) Michael Heilmann 2017, 2018
#pragma once

#include "Nucleus/Interpreter/Annotations.h"
#include <stdlib.h>

// Forward declaration.
typedef struct Nucleus_Interpreter_Context Nucleus_Interpreter_Context;

/// @ingroup interpreter
/// @brief A string buffer.
typedef struct Nucleus_Interpreter_StringBuffer Nucleus_Interpreter_StringBuffer;


struct Nucleus_Interpreter_StringBuffer
{
    /// @brief A pointer to an array of @a capacity Bytes.
    char *array;
    /// @brief The size, in Bytes, of the array pointed to by @a elements.
    size_t capacity;
    /// @brief The number of Bytes in this string buffer. 
    size_t size;
}; // struct Nucleus_Interpreter_StringBuffer

/// @ingroup interpreter
/// @brief Initialize a Nucleus_Interpreter_StringBuffer object.
/// @param stringBuffer a pointer to a Nucleus_Interpreter_StringBuffer object
/// @success The Nucleus_Interpreter_StringBuffer objec was initialzed with a capacity greater than or equal to @a capacity.
Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_StringBuffer_initialize
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringBuffer *stringBuffer,
        size_t initialCapacity
    );

/// @ingroup interpreter
/// @brief Uninitialize a Nucleus_Interpreter_StringBuffer object.
/// @param stringBuffer a pointer to the Nucleus_Interpreter_StringBuffer object
Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_StringBuffer_uninitialize
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringBuffer *stringBuffer
    );

/// @ingroup interpreter
/// @brief Ensure the free capacity of a Nucleus_Interpreter_StringBuffer is greater than or equal a required free capacity.
/// @param stringBuffer a pointer to the Nucleus_Interpreter_StringBuffer object
/// @param requiredFreeCapacity the required free capacity
/// @post
/// - on success: @a status was not dereferenced. The free capacity of the Nucleus_Interpreter_StringBuffer object pointed to by @a stringBuffer is greater than or equal to @a freeCapacity.
/// - on failure: @a (*status) wsa assigned a non-zero status code.
Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_StringBuffer_ensureFreeCapacity
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringBuffer *stringBuffer,
        size_t requiredFreeCapacity
    );

/// @ingroup interpreter
/// @brief Append Bytes to a Nucleus_Interpreter_StringBuffer object.
/// @param stringBuffer a pointer to the Nucleus_Interpreter_StringBuffer object
/// @param bytes a pointer to the array of Bytes to append
/// @param numberOfBytes the number of Bytes to append
Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_StringBuffer_append
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringBuffer *stringBuffer,
        const char *bytes,
        size_t numberOfBytes
    );

/// @ingroup interpreter
/// @brief Prepend Bytes to a Nucleus_Interpreter_StringBuffer object.
/// @param stringBuffer a pointer to the Nucleus_Interpreter_StringBuffer object
/// @param bytes a pointer to the array of Bytes to prepend
/// @param numberOfBytes the number of Bytes to prepend
Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_StringBuffer_prepend
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringBuffer *stringBuffer,
        const char *bytes,
        size_t numberOfBytes
    );

/// @ingroup interpreter
/// @brief Insert Bytes to a Nucleus_Interpreter_StringBuffer object.
/// @param stringBuffer a pointer to the Nucleus_Interpreter_StringBuffer object
/// @param bytes a pointer to the array of Bytes to prepend
/// @param numberOfBytes the number of Bytes to prepend
/// @param index the index at which to insert the Bytes
/// @remark
/// A call
/// @code
/// Nucleus_Interpreter_StringBuffer_insert(environment, status, stringBuffer, bytes, numberOfBytes, 0) 
/// @endcode
/// is equivalent to a call
/// @code
/// Nucleus_Interpreter_StringBuffer_prepend(environment, status, stringBuffer, bytes, numberOfBytes) 
/// @endcode
/// @remark
/// A call
/// @code
/// Nucleus_Interpreter_StringBuffer_insert(environment, status, stringBuffer, bytes, numberOfBytes, Nucleus_Interpreter_StringBuffer_getSize(environment, status, stringBuffer)) 
/// @endcode
/// is equivalent to a call
/// @code
/// Nucleus_Interpreter_StringBuffer_append(environment, status, stringBuffer, bytes, numberOfBytes) 
/// @endcode
Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_StringBuffer_insert
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringBuffer *stringBuffer,
        const char *bytes,
        size_t numberOfBytes,
        size_t index
    );

/// @ingroup interpreter
Nucleus_Interpreter_NonNull() const char *
Nucleus_Interpreter_StringBuffer_getBytes
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringBuffer *stringBuffer
    );

/// @ingroup interpreter
/// @brief Get the size of a Nucleus_Interpreter_StringBuffer object.
/// @param stringBuffer a pointer to the Nucleus_Interpreter_StringBuffer object
/// @return the size of the Nucleus_Interpreter_StringBuffer object
Nucleus_Interpreter_NonNull() size_t
Nucleus_Interpreter_StringBuffer_getSize
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringBuffer *stringBuffer
    );

/// @ingroup interpreter
/// @brief Get the capacity of a Nucleus_Interpreter_StringBuffer object.
/// @param stringBuffer a pointer to the Nucleus_Interpreter_StringBuffer object
/// @return the capacity of the Nucleus_Interpreter_StringBuffer object
Nucleus_Interpreter_NonNull() size_t
Nucleus_Interpreter_StringBuffer_getCapacity
    (
        Nucleus_Interpreter_Context *contet,
        Nucleus_Interpreter_StringBuffer *stringBuffer
    );

/// @ingroup interpreter
/// @brief Get the free capacity of a Nucleus_Interpreter_StringBuffer object.
/// @param stringBuffer a pointer to the Nucleus_Interpreter_StringBuffer object
/// @return the free capacity of the Nucleus_Interpreter_StringBuffer object
Nucleus_Interpreter_NonNull() size_t
Nucleus_Interpreter_StringBuffer_getFreeCapacity
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringBuffer *stringBuffer
    );

/// @ingroup interpreter
/// @brief Clear a Nucleus_Interpreter_StringBuffer object.
/// @param stringBuffer a pointer to the Nucleus_Interpreter_StringBuffer object
Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_StringBuffer_clear
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_StringBuffer *stringBuffer
    );
